#ifndef MOVES_H
#define MOVES_H
extern char board[8][8][4];
extern int i, j, r, c;
extern int counterW;
extern int counterB;
extern int invalid_move;
extern int colour;
extern char killed_arrW[15][4];
extern char killed_arrB[15][4];
extern char whiteKing[4];
extern char whiteRook[4];
extern char blackKing[4];
extern char blackRook[4];
extern int moved[8][8];

int isWhite(char piece[4]);

int isBlack(char piece[4]);

int piece_colour(char piece[4]);

void change( int i, int j);

void knight(int i, int j, int r, int c, int colour);

void queen(int i, int j, int r, int c, int colour);

void white_pawn(int i, int j, int r, int c);

void black_pawn(int i, int j, int r, int c);

void bishop(int i, int j, int r, int c, int colour);

void rook(int i, int j, int r, int c, int colour);

void king(int i, int j, int r, int c, int colour);
#endif
