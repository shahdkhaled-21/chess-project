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
extern opponent_piece[4];

void change( int i, int j);
void knight(int i, int j, int r, int c);
void queen(int i, int j, int r, int c);
void pawn(int i, int j, int r, int c);
void bishop(int i, int j, int r, int c);
void rook(int i, int j, int r, int c);
void king(int i, int j, int r, int c);
#endif
