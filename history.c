#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moves.h"
#include  "specialMoves.h"

typedef unsigned char u8;

//third byte in white pieces
#define WhiteKing 0x94
#define WhiteQueen 0x95
#define WhiteRook 0x96
#define WhiteBishop 0x97
#define WhiteKnight 0x98
#define WhitePawn 0x99

//third byte in black pieces
#define BlackKing 0x9A
#define BlackQueen 0x9B
#define BlackRook 0x9C
#define BlackBishop 0x9D
#define BlackKnight 0x9E
#define BlackPawn 0x9F
typedef struct {
    char original_place[3];
    char new_place[3];
    char moved_piece[4];
    char captured_piece[4];
    
    int moved_flag_src;
    int moved_flag_dest;
    int was_castling;
    int was_en_passant;
    int was_promotion;
    int en_passant_col;
    int counterW_before;
    int counterB_before;
    int counterW_after;
    int counterB_after;
    int rook_src_row;
    int rook_src_col;
    int rook_dest_row;
    int rook_dest_col;
    int rook_moved_src;
    int rook_moved_dest;
    char original_pawn[4];
} History;

extern int i, j, r, c;
extern char board[8][8][4];
extern int moved[8][8];
extern int counterW;
extern int counterB;
extern int invalid_move;
extern char killed_arrW[15][4];
extern char killed_arrB[15][4];
extern int enPassantDone;

History history[6000] = {};
int historyCount = 0;
int historyPosition = 0;

char initialBoard[8][8][4] = {{"\u265C","\u265E","\u265D","\u265B","\u265A","\u265D","\u265E","\u265C"},
                              {"\u265F","\u265F","\u265F","\u265F","\u265F","\u265F","\u265F","\u265F"},
                              {"-", ".", "-", ".", "-", ".", "-", "."},
                              {".", "-", ".", "-", ".", "-", ".", "-"},
                              {"-", ".", "-", ".", "-", ".", "-", "."},
                              {".", "-", ".", "-", ".", "-", ".", "-"},
                              {"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"},
                              {"\u2656","\u2658","\u2657","\u2655","\u2654","\u2657","\u2658","\u2656"}};

void addToHistory(char original[3], char newPlace[3], char piece[4], char captured[4], int i, int j, int r, int c){
    if(historyPosition < historyCount){
        historyCount = historyPosition;
    }
    if(historyCount >= 6000){
    printf("History limit reached\n");
    return;
    }
    History *h = &history[historyCount];
    strcpy(h -> original_place, original);
    strcpy(h -> new_place, newPlace);
    memcpy(h -> moved_piece, piece, 4);
    memcpy(h -> captured_piece, captured, 4);
    h -> moved_flag_src = moved[i][j];
    h -> moved_flag_dest = moved[r][c];
    h -> counterW_before = counterW;
    h -> counterB_before = counterB;
    h -> was_castling = 0;
    h -> was_en_passant = 0;
    h -> was_promotion = 0;
    h -> en_passant_col = -1;
    h -> rook_src_row = -1;
    h -> rook_src_col = -1;
    h -> rook_dest_row = -1;
    h -> rook_dest_col = -1;
    h -> rook_moved_dest = 0;
    h -> rook_moved_src = 0;
    historyCount++;
    historyPosition = historyCount;
    h -> counterW_after = counterW;
    h -> counterB_after = counterB;
    printf("Saved to History: %s to %s, Count: %d\n", h->original_place, h->new_place, historyCount);
}

void markCastling(int rook_si, int rook_sj, int rook_di, int rook_dj){
    if(historyCount == 0) return;
    History *h = &history[historyCount - 1];
    h -> was_castling = 1;
    h -> rook_src_row = rook_si;
    h -> rook_src_col = rook_sj;
    h -> rook_dest_row = rook_di;
    h -> rook_dest_col = rook_dj;
    h -> rook_moved_src  = moved[rook_si][rook_sj];
    h -> rook_moved_dest = moved[rook_di][rook_dj];
}

void markEnPassant(int captured_col){
    if(historyCount == 0) return;
    History *h = &history[historyCount - 1];
    h -> was_en_passant = 1;
    h -> en_passant_col = captured_col;
}

void markPromotion(char original_pawn[4]){
    if(historyCount == 0) return;
    History *h = &history[historyCount - 1];
    h -> was_promotion = 1;
    memcpy(h -> original_pawn, original_pawn, 4);
}

void moveFromCoords(char from[3], char to[3]){
    j = from[0] - 'A';
    i = 8 - (from[1] - '0');
    c = to[0] - 'A';
    r = 8 - (to[1] - '0');
    invalid_move = 0;
    char piece[4];
    memcpy(piece, board[i][j], 4);
    
    if(piece[0] == '.' || piece[0] == '-'){
        invalid_move = 1;
        return;
    }
    
    if(isWhite(piece)) colour = 1;
    else colour = 0;
    
    u8 piece_type = (u8)piece[2];
    
    if(piece_type == WhiteKing || piece_type == BlackKing) {
        if(i == r && abs(j - c) == 2) {
            castling(i, j, r, c);
            if(invalid_move == 0) {
                addToHistory(from, to, piece, board[r][c], i, j, r, c);
            }
            return;
        }
        else {
            king(i, j, r, c, colour);
        }
    }
    else if(piece_type == WhiteRook || piece_type == BlackRook) {
        rook(i, j, r, c, colour);
    }
    else if(piece_type == WhitePawn || piece_type == BlackPawn) {
        (colour == 1) ? white_pawn(i, j, r, c) : black_pawn(i, j, r, c);
        if(invalid_move == 0 && enPassantDone == 1) {
            addToHistory(from, to, piece, board[r][c], i, j, r, c);
            markEnPassant(c);
            return;
        }
    }
    else if(piece_type == WhiteKnight || piece_type == BlackKnight) {
        knight(i, j, r, c, colour);
    }
    else if(piece_type == WhiteBishop || piece_type == BlackBishop) {
        bishop(i, j, r, c, colour);
    }
    else if(piece_type == WhiteQueen || piece_type == BlackQueen) {
        queen(i, j, r, c, colour);
    }
    
    if(invalid_move == 0){
        addToHistory(from, to, piece, board[r][c], i, j, r, c);
    }
}

void historyInitialization(){
    if(historyCount==0){
        History*h = &history[historyCount];
        memset(h->original_place, 0, sizeof(h->original_place));
        memset(h->new_place, 0, sizeof(h->new_place));
        memset(h->moved_piece, 0, sizeof(h->moved_piece));
        memset(h->captured_piece, 0, sizeof(h->captured_piece));
        h->moved_flag_src = 0;
        h->moved_flag_dest = 0;
        h->was_castling = 0;
        h->was_en_passant = 0;
        h->was_promotion = 0;
        memset(h->original_pawn, 0, sizeof(h->original_pawn));
        h->en_passant_col = -1;
        h->rook_src_row = -1;
        h->rook_src_col = -1;
        h->rook_dest_row = -1;
        h->rook_dest_col = -1;
        h->rook_moved_src = 0;
        h->rook_moved_dest = 0;
        h->counterB_before = 0;
        h->counterB_after = 0;
        h->counterW_after = 0;
        h->counterW_before = 0;
    }
}

void clearHistory(){
    historyCount = 0;
    historyPosition = 0;
}

void undo(){ //under modification****************
    if(historyPosition <= 0){
        printf("No moves to undo!\n");
        return;
    }
    historyPosition--;
    History *h = &history[historyPosition];
    int i = 8 - (h -> original_place[1] - '0');
    int j = h -> original_place[0] - 'A';
    int r = 8 - (h->new_place[1] - '0');
    int c = h -> new_place[0] - 'A';
    memcpy(board[i][j], h -> moved_piece, 4);
    h -> counterB_after = h -> counterB_before; 
    h -> counterW_after = h -> counterW_before;
    counterB = h -> counterB_before;
    counterW = h -> counterW_before;
    strcpy(killed_arrB[counterB] , "\0");
    strcpy(killed_arrW[counterW] , "\0");
    if(h -> captured_piece[0] == '-' || h->captured_piece[0] == '.'){
        memcpy(board[r][c], h -> captured_piece, 4);
    }
    else{
        memcpy(board[r][c], h -> captured_piece, 4);
    }
    moved[i][j] = h -> moved_flag_src;
    moved[r][c] = h -> moved_flag_dest;
    counterW = h -> counterW_before;
    counterB = h -> counterB_before;
    if(h -> was_castling){
        if(h -> rook_src_row >= 0){
            memcpy(board[h -> rook_src_row][h -> rook_src_col], board[h -> rook_dest_row][h -> rook_dest_col], 4);
            change(h -> rook_dest_row, h -> rook_dest_col);
            moved[h -> rook_src_row][h -> rook_src_col] = h -> rook_moved_src;
            moved[h -> rook_dest_row][h -> rook_dest_col] = h -> rook_moved_dest;

        }
    }
    if(h -> was_en_passant){
        int pawn_row = (isWhite(h -> moved_piece)) ? r + 1 : r - 1;
        memcpy(board[pawn_row][h -> en_passant_col], h -> captured_piece, 4);
        change(r, c);
    }
    if(h->was_promotion){
        memcpy(board[i][j], h -> original_pawn, 4);
    }
}

void redo(){
    if(historyPosition >= historyCount){
        printf("No moves to redo!\n");
        return;
    }
    History *h = &history[historyPosition];
    int i = 8 - (h -> original_place[1] - '0');
    int j = h -> original_place[0] - 'A';
    int r = 8 - (h -> new_place[1] - '0');
    int c = h -> new_place[0] - 'A';
    memcpy(board[r][c], h -> moved_piece, 4);
    if(h -> captured_piece[0] != '-' && h -> captured_piece[0] != '.'){
        if(isWhite(h -> captured_piece)){
            memcpy(killed_arrW[counterW], h -> captured_piece, 4);
            counterW++;
        }
        else{
            memcpy(killed_arrB[counterB], h -> captured_piece, 4);
            counterB++;
        }
    }
    change(i, j);
    moved[r][c] = 1;
    moved[i][j] = 0;
    if(h -> was_castling){
        if(h -> rook_dest_row >= 0){
            memcpy(board[h -> rook_dest_row][h -> rook_dest_col], board[h -> rook_src_row][h -> rook_src_col], 4);
            change(h -> rook_src_row, h -> rook_src_col);
            moved[h -> rook_dest_row][h -> rook_dest_col] = 1;
        }
    }
    if(h -> was_en_passant){
        int pawn_row = (isWhite(h -> moved_piece)) ? r + 1 : r - 1;
        change(pawn_row, h -> en_passant_col);
        if(isWhite(h -> captured_piece)){
            memcpy(killed_arrW[counterW], h -> captured_piece, 4);
            counterW++;
        }
        else{
            memcpy(killed_arrB[counterB], h -> captured_piece, 4);
            counterB++;
        }
    }
    if(h->was_promotion){
    memcpy(board[r][c], h->moved_piece, 4);
    }
    counterW = h -> counterW_after;
    counterB = h -> counterB_after;
    historyPosition++;
}

void resetGame(){
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            memcpy(board[i][j], initialBoard[i][j], 4);
    clearHistory();
    counterW = 0;
    counterB = 0;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            moved[i][j] = 0;
}

void saveGame(char filename[255]){
    FILE *file = fopen(filename, "w");
    if(!file){
        printf("Error: Cannot create save file\n");
        return;
    }

    fprintf(file, "%d\n", historyPosition);

    for(int i = 0; i < historyPosition; i++){
        History *h = &history[i];
        fprintf(file, "%s %s\n", h->original_place, h->new_place);
    }

    fclose(file);
    printf("Game saved\n");
}

int loadGame(char filename[255]){
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Error: Cannot open file\n");
        return 0;
    }

    int move_count;
    if(fscanf(file, "%d", &move_count) != 1){
        printf("Invalid save file\n");
        fclose(file);
        return 0;
    }

    resetGame();

    char from[3], to[3];

    for(int k = 0; k < move_count; k++){
        if(fscanf(file, "%2s %2s", from, to) != 2){
            printf("Error reading move %d\n", k+1);
            fclose(file);
            return 0;
        }

        moveFromCoords(from, to);

        if(invalid_move){
            printf("Invalid move in save: %s %s\n", from, to);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    printf("Game loaded successfully!\n\n");
    return 1;
}

void displaySavedGames(){
    printf("\n--- Saved Games ---\n");
    printf("Looking for .txt files in current directory...\n\n");
    
    #ifdef _WIN32
        system("dir *.txt /b");
    #else
        system("ls *.txt 2>/dev/null");
    #endif
    
    printf("\n-------------------\n\n");
}

void getFilename(char filename[255], int maxLen) {
    printf("Enter filename (without .txt) or 0 to cancel: ");
    scanf("%255s", filename);
    if(filename[0] != '0'){
        if(strstr(filename, ".txt") == NULL) {
            strcat(filename, ".txt");
        } 
    }
}
