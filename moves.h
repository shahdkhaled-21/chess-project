#ifndef MOVES_H
#define MOVES_H
extern char board[8][8][4];
extern int i, j, r, c;
extern int counterW;
extern int counterB;
extern char killed_arrW[15][4];
extern char killed_arrB[15][4];
extern char opponent_piece[4], friendly_piece[4];
extern char whiteKing[4];
extern char whiteRook[4];
extern char blackKing[4];
extern char blackRook[4];
extern char whitePawn[4];
extern char blackPawn[4];
extern int moved[8][8];
void knight(int i, int j, int r, int c);
void queen(int i, int j, int r, int c);
void pawn(int i, int j, int r, int c);
void bishop(int i, int j, int r, int c);
void rook(int i, int j, int r, int c);
void king(int i, int j, int r, int c);
void castling(int i, int j, int r, int c);
int haveMovedAt(int r, int c);
int kingInCheck(char current_king_piece[4]);
int isSquareAttacked(int i, int j);
int must_promote(int i, int j, int r, int c);
void promotion(int i, int j, int r, int c, char promotion_piece[4]);
#endif
