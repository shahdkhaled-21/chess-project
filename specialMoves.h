#ifndef SPEECIALMOVES_H
#define SPEECIALMOVES_H
extern char board[8][8][4];
extern char killed_arrW[15][4];
extern char killed_arrB[15][4];
extern int i, j, r, c;
extern int counterW;
extern int counterB;
extern int invalid_move;
extern int colour;
extern char whiteKing[4];
extern char whiteRook[4];
extern char blackKing[4];
extern char blackRook[4];
extern int moved[8][8];
extern int checking_checkmate;
extern char opponent_piece[4];

void castling(int i, int j, int r, int c);
int haveMovedAt(int r, int c);
int isSquareAttacked(int i, int j);
int must_promote(int i, int j, int r, int c);
void promotion(int i, int j, int r, int c, char promotion_piece[4]);
int kingInCheck(char current_king_piece[4]);
int isCheckmate(int colour);
#endif