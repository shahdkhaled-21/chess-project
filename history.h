#ifndef HISTORY_H
#define HISTORY_H
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

extern char board[8][8][4];
extern char initialBoard[8][8][4];
extern int moved[8][8];
extern int counterW;
extern int counterB;
extern int invalid_move;
extern char killed_arrW[15][4];
extern char killed_arrB[15][4];

void addToHistory(char original[3], char newPlace[3], char piece[4], char captured[4], int i, int j, int r, int c);

void markCastling(int rook_si, int rook_sj, int rook_di, int rook_dj);

void markEnPassant(int captured_col);

void markPromotion(char original_pawn[4]);

void undo(void);

void redo(void);

void resetGame(void);

void clearHistory(void);

void saveGame(char *filename);

int loadGame(char *filename);

void displaySavedGames(void);

void getFilename(char *filename, int maxLen);
#endif