#include <gtk/gtk.h>

// Unicode chess pieces
#define WHITE_KING   "♔"
#define WHITE_QUEEN  "♕"
#define WHITE_ROOK   "♖"
#define WHITE_BISHOP "♗"
#define WHITE_KNIGHT "♘"
#define WHITE_PAWN   "♙"

#define BLACK_KING   "♚"
#define BLACK_QUEEN  "♛"
#define BLACK_ROOK   "♜"
#define BLACK_BISHOP "♝"
#define BLACK_KNIGHT "♞"
#define BLACK_PAWN   "♟"

// Move history structure
typedef struct {
    int from_row;
    int from_col;
    int to_row;
    int to_col;
    char *piece_moved;
    char *piece_captured;  // NULL if no capture
} Move;

// Captured pieces lists
typedef struct {
    char *white_captured[16];  // Max 16 pieces per side
    char *black_captured[16];
    int white_count;
    int black_count;
} CapturedPieces;

// Game state
typedef struct {
    GtkBuilder *builder;
    gboolean piece_selected;
    int selected_row;
    int selected_col;
    GtkWidget *selected_cell;
    Move *move_history[100];  // Store up to 100 moves
    int move_count;
    CapturedPieces captured;
    GtkWidget *white_captured_box;
    GtkWidget *black_captured_box;
} GameState;

GameState game_state = {NULL, FALSE, -1, -1, NULL, {NULL}, 0, {{NULL}, {NULL}, 0, 0}, NULL, NULL};

void apply_inline_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    const gchar *css_data = 
        ".white-square { background-color: #eeeed2; } "
        ".black-square { background-color: #769656; } "
        ".selected { background-color: #f6f669; } "  // Yellow highlight for selected
        ".chess-piece { font-size: 48px; } "
        ".captured-piece { font-size: 32px; margin: 2px; } "
        ".captured-box { "
        "  background-color: #f0f0f0; "
        "  padding: 10px; "
        "  border: 2px solid #999; "
        "}";
    
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void color_chessboard(GtkBuilder *builder) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char cell_name[20];
            sprintf(cell_name, "cell%d%d", row, col);
            
            GtkWidget *cell = GTK_WIDGET(gtk_builder_get_object(builder, cell_name));
            if (cell) {
                GtkStyleContext *context = gtk_widget_get_style_context(cell);
                
                if ((row + col) % 2 == 0) {
                    gtk_style_context_add_class(context, "white-square");
                } else {
                    gtk_style_context_add_class(context, "black-square");
                }
            }
        }
    }
}

void setup_piece(GtkBuilder *builder, int row, int col, const char *piece_symbol) {
    char cell_name[20];
    sprintf(cell_name, "cell%d%d", row, col);
    
    GtkWidget *event_box = GTK_WIDGET(gtk_builder_get_object(builder, cell_name));
    if (event_box) {
        GtkWidget *label = gtk_label_new(piece_symbol);
        GtkStyleContext *context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context, "chess-piece");
        gtk_container_add(GTK_CONTAINER(event_box), label);
    }
}

void setup_chess_pieces(GtkBuilder *builder) {
    // Black pieces (row 0)
    setup_piece(builder, 0, 0, BLACK_ROOK);
    setup_piece(builder, 0, 1, BLACK_KNIGHT);
    setup_piece(builder, 0, 2, BLACK_BISHOP);
    setup_piece(builder, 0, 3, BLACK_QUEEN);
    setup_piece(builder, 0, 4, BLACK_KING);
    setup_piece(builder, 0, 5, BLACK_BISHOP);
    setup_piece(builder, 0, 6, BLACK_KNIGHT);
    setup_piece(builder, 0, 7, BLACK_ROOK);
    
    // Black pawns (row 1)
    for (int col = 0; col < 8; col++) {
        setup_piece(builder, 1, col, BLACK_PAWN);
    }
    
    // White pawns (row 6)
    for (int col = 0; col < 8; col++) {
        setup_piece(builder, 6, col, WHITE_PAWN);
    }
    
    // White pieces (row 7)
    setup_piece(builder, 7, 0, WHITE_ROOK);
    setup_piece(builder, 7, 1, WHITE_KNIGHT);
    setup_piece(builder, 7, 2, WHITE_BISHOP);
    setup_piece(builder, 7, 3, WHITE_QUEEN);
    setup_piece(builder, 7, 4, WHITE_KING);
    setup_piece(builder, 7, 5, WHITE_BISHOP);
    setup_piece(builder, 7, 6, WHITE_KNIGHT);
    setup_piece(builder, 7, 7, WHITE_ROOK);
}

void remove_highlight() {
    if (game_state.selected_cell) {
        GtkStyleContext *context = gtk_widget_get_style_context(game_state.selected_cell);
        gtk_style_context_remove_class(context, "selected");
    }
}

gboolean is_white_piece(const char *piece) {
    return (strcmp(piece, WHITE_KING) == 0 ||
            strcmp(piece, WHITE_QUEEN) == 0 ||
            strcmp(piece, WHITE_ROOK) == 0 ||
            strcmp(piece, WHITE_BISHOP) == 0 ||
            strcmp(piece, WHITE_KNIGHT) == 0 ||
            strcmp(piece, WHITE_PAWN) == 0);
}

void update_captured_display() {
    // Clear existing displays
    gtk_container_foreach(GTK_CONTAINER(game_state.white_captured_box),
                         (GtkCallback)gtk_widget_destroy, NULL);
    gtk_container_foreach(GTK_CONTAINER(game_state.black_captured_box),
                         (GtkCallback)gtk_widget_destroy, NULL);
    
    // Display white's captured pieces (black pieces)
    for (int i = 0; i < game_state.captured.white_count; i++) {
        GtkWidget *label = gtk_label_new(game_state.captured.white_captured[i]);
        GtkStyleContext *context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context, "captured-piece");
        gtk_box_pack_start(GTK_BOX(game_state.white_captured_box), label, FALSE, FALSE, 0);
        gtk_widget_show(label);
    }
    
    // Display black's captured pieces (white pieces)
    for (int i = 0; i < game_state.captured.black_count; i++) {
        GtkWidget *label = gtk_label_new(game_state.captured.black_captured[i]);
        GtkStyleContext *context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context, "captured-piece");
        gtk_box_pack_start(GTK_BOX(game_state.black_captured_box), label, FALSE, FALSE, 0);
        gtk_widget_show(label);
    }
}

void move_piece(GtkWidget *from_box, GtkWidget *to_box, int from_row, int from_col, int to_row, int to_col) {
    // Get the piece from source
    GtkWidget *piece = gtk_bin_get_child(GTK_BIN(from_box));
    
    if (piece) {
        const gchar *piece_text = gtk_label_get_text(GTK_LABEL(piece));
        
        // Save move to history
        Move *move = g_malloc(sizeof(Move));
        move->from_row = from_row;
        move->from_col = from_col;
        move->to_row = to_row;
        move->to_col = to_col;
        move->piece_moved = g_strdup(piece_text);
        
        // Check for capture
        GtkWidget *old_piece = gtk_bin_get_child(GTK_BIN(to_box));
        if (old_piece) {
            const gchar *captured_text = gtk_label_get_text(GTK_LABEL(old_piece));
            move->piece_captured = g_strdup(captured_text);
            
            // Add to captured pieces list
            if (is_white_piece(captured_text)) {
                // Black captured a white piece
                game_state.captured.black_captured[game_state.captured.black_count] = g_strdup(captured_text);
                game_state.captured.black_count++;
            } else {
                // White captured a black piece
                game_state.captured.white_captured[game_state.captured.white_count] = g_strdup(captured_text);
                game_state.captured.white_count++;
            }
            
            gtk_widget_destroy(old_piece);
            update_captured_display();
        } else {
            move->piece_captured = NULL;
        }
        
        // Add move to history
        game_state.move_history[game_state.move_count] = move;
        game_state.move_count++;
        
        // Remove from source
        gtk_widget_destroy(piece);
        
        // Add to destination
        GtkWidget *new_label = gtk_label_new(piece_text);
        GtkStyleContext *context = gtk_widget_get_style_context(new_label);
        gtk_style_context_add_class(context, "chess-piece");
        gtk_container_add(GTK_CONTAINER(to_box), new_label);
        gtk_widget_show(new_label);
    }
}

gboolean on_cell_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    int *pos = (int *)data;
    int row = pos[0];
    int col = pos[1];
    
    if (!game_state.piece_selected) {
        // First click - select a piece
        GtkWidget *piece = gtk_bin_get_child(GTK_BIN(widget));
        if (piece) {
            game_state.piece_selected = TRUE;
            game_state.selected_row = row;
            game_state.selected_col = col;
            game_state.selected_cell = widget;
            
            // Highlight selected square
            GtkStyleContext *context = gtk_widget_get_style_context(widget);
            gtk_style_context_add_class(context, "selected");
            
            g_print("Selected piece at [%d,%d]\n", row, col);
        }
    } else {
        // Second click - move the piece
        char from_cell[20], to_cell[20];
        sprintf(from_cell, "cell%d%d", game_state.selected_row, game_state.selected_col);
        sprintf(to_cell, "cell%d%d", row, col);
        
        GtkWidget *from_box = GTK_WIDGET(gtk_builder_get_object(game_state.builder, from_cell));
        GtkWidget *to_box = GTK_WIDGET(gtk_builder_get_object(game_state.builder, to_cell));
        
        // Move the piece with history tracking
        move_piece(from_box, to_box, game_state.selected_row, game_state.selected_col, row, col);
        
        // Remove highlight
        remove_highlight();
        
        // Reset selection
        game_state.piece_selected = FALSE;
        game_state.selected_cell = NULL;
        
        g_print("Moved piece from [%d,%d] to [%d,%d]\n", 
                game_state.selected_row, game_state.selected_col, row, col);
    }
    
    return TRUE;
}

void make_board_interactive(GtkBuilder *builder) {
    game_state.builder = builder;
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char cell_name[20];
            sprintf(cell_name, "cell%d%d", row, col);
            
            GtkWidget *cell = GTK_WIDGET(gtk_builder_get_object(builder, cell_name));
            if (cell) {
                int *pos = g_malloc(2 * sizeof(int));
                pos[0] = row;
                pos[1] = col;
                
                g_signal_connect(cell, "button-press-event", 
                               G_CALLBACK(on_cell_clicked), pos);
            }
        }
    }
}

void undo_last_move() {
    if (game_state.move_count == 0) {
        g_print("No moves to undo!\n");
        return;
    }
    
    // Get the last move
    game_state.move_count--;
    Move *last_move = game_state.move_history[game_state.move_count];
    
    char from_cell[20], to_cell[20];
    sprintf(from_cell, "cell%d%d", last_move->from_row, last_move->from_col);
    sprintf(to_cell, "cell%d%d", last_move->to_row, last_move->to_col);
    
    GtkWidget *from_box = GTK_WIDGET(gtk_builder_get_object(game_state.builder, from_cell));
    GtkWidget *to_box = GTK_WIDGET(gtk_builder_get_object(game_state.builder, to_cell));
    
    // Remove piece from destination
    GtkWidget *piece_at_dest = gtk_bin_get_child(GTK_BIN(to_box));
    if (piece_at_dest) {
        gtk_widget_destroy(piece_at_dest);
    }
    
    // Restore captured piece if there was one
    if (last_move->piece_captured) {
        GtkWidget *captured_label = gtk_label_new(last_move->piece_captured);
        GtkStyleContext *context = gtk_widget_get_style_context(captured_label);
        gtk_style_context_add_class(context, "chess-piece");
        gtk_container_add(GTK_CONTAINER(to_box), captured_label);
        gtk_widget_show(captured_label);
        
        // Remove from captured pieces display
        if (is_white_piece(last_move->piece_captured)) {
            // Remove from black's captured list
            game_state.captured.black_count--;
            g_free(game_state.captured.black_captured[game_state.captured.black_count]);
        } else {
            // Remove from white's captured list
            game_state.captured.white_count--;
            g_free(game_state.captured.white_captured[game_state.captured.white_count]);
        }
        
        update_captured_display();
    }
    
    // Move piece back to original position
    GtkWidget *piece_label = gtk_label_new(last_move->piece_moved);
    GtkStyleContext *context = gtk_widget_get_style_context(piece_label);
    gtk_style_context_add_class(context, "chess-piece");
    gtk_container_add(GTK_CONTAINER(from_box), piece_label);
    gtk_widget_show(piece_label);
    
    g_print("Undone: [%d,%d] to [%d,%d]\n", 
            last_move->from_row, last_move->from_col,
            last_move->to_row, last_move->to_col);
    
    // Free memory
    g_free(last_move->piece_moved);
    g_free(last_move->piece_captured);
    g_free(last_move);
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    // Ctrl+Z or just 'u' for undo
    if ((event->state & GDK_CONTROL_MASK && event->keyval == GDK_KEY_z) ||
        event->keyval == GDK_KEY_u) {
        undo_last_move();
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkBuilder *builder = gtk_builder_new_from_file("chessWindow.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    
    // Get the board from Glade
    GtkWidget *board = GTK_WIDGET(gtk_builder_get_object(builder, "chessBoard"));
    if (!board) {
        board = GTK_WIDGET(gtk_builder_get_object(builder, "grid1"));
    }
    
    // Only add side panels if board exists and has a parent
    if (board) {
        GtkWidget *board_parent = gtk_widget_get_parent(board);
        
        if (board_parent && GTK_IS_CONTAINER(board_parent)) {
            // Create main layout
            GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
            
            // Left side - White's captured pieces
            GtkWidget *left_frame = gtk_frame_new("White Captured");
            game_state.white_captured_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            GtkStyleContext *left_context = gtk_widget_get_style_context(game_state.white_captured_box);
            gtk_style_context_add_class(left_context, "captured-box");
            gtk_container_add(GTK_CONTAINER(left_frame), game_state.white_captured_box);
            gtk_box_pack_start(GTK_BOX(main_box), left_frame, FALSE, FALSE, 5);
            
            // Reparent the board properly
            g_object_ref(board);
            gtk_container_remove(GTK_CONTAINER(board_parent), board);
            gtk_box_pack_start(GTK_BOX(main_box), board, TRUE, TRUE, 0);
            g_object_unref(board);
            
            // Right side - Black's captured pieces
            GtkWidget *right_frame = gtk_frame_new("Black Captured");
            game_state.black_captured_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            GtkStyleContext *right_context = gtk_widget_get_style_context(game_state.black_captured_box);
            gtk_style_context_add_class(right_context, "captured-box");
            gtk_container_add(GTK_CONTAINER(right_frame), game_state.black_captured_box);
            gtk_box_pack_start(GTK_BOX(main_box), right_frame, FALSE, FALSE, 5);
            
            // Add to window
            gtk_container_add(GTK_CONTAINER(window), main_box);
        }
    }
    
    apply_inline_css();
    color_chessboard(builder);
    setup_chess_pieces(builder);
    make_board_interactive(builder);
    
    // Connect keyboard shortcut for undo
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}