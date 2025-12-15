#ifndef MOVES_H
#define MOVES_H
extern char board[8][8][4];
extern int counter;
extern char killed_arr[32][4];
extern char opponent_piece[4], friendly_piece[4];
extern char whiteKing[4];
extern char whiteRock[4];
extern char blackKing[4];
extern char blackRock[4];
void knight(int i, int j, int r, int c);
void queen(int i, int j, int r, int c);
void pawn(int i, int j, int r, int c);
void bishop(int i, int j, int r, int c);
void rock(int i, int j, int r, int c);
void king(int i, int j, int r, int c);
void castling(int i, int j, int r, int c);
int haveMoved(char piece[4]);
int inCheck();
int isSquareAttacked(int i, int j);
#endif