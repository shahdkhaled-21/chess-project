#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moves.h"

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
extern int checking_stalemate;

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

int haveMovedAt(int r, int c){
    return moved[r][c];
}

int isSquareAttacked(int r, int c, int myCurruntColour){
    int i, j;
    // checking knight attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(piece_colour(board[i][j]) != myCurruntColour){
                if((abs(r - i) == 1 && abs(c - j) == 2) || (abs(r - i) == 2 && abs(c - j) == 1)){
                    return 1;
                }
            }
        }
    }
    // checking king attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(piece_colour(board[i][j]) != myCurruntColour){
                if(abs(r - i) <= 1 && abs(c - j) <= 1){
                    return 1;
                }
            }
        }
    }
    // checking pawn attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(piece_colour(board[i][j]) != myCurruntColour){
                if((r - i == 1 && abs(c - j) == 1) || (r - i == -1 && abs(c - j) == 1)){
                    return 1;
                }
            }
        }
    }
    // checking rock & queen attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(piece_colour(board[i][j]) != myCurruntColour){
                if(i == r){
                    int clear = 1;
                    int step = (j < c) ? 1 : -1;
                    for(int k = j + step; k != c; k += step){
                        if(board[i][k][0] != '.' && board[i][k][0] != '-'){
                            clear = 0;
                            break;
                        }
                    }
                    if(clear) return 1;
                }
                if(j == c){
                    int clear = 1;
                    int step = (i < r) ? 1 : -1;
                    for(int k = i + step; k != r; k += step){
                        if(board[k][j][0] != '.' && board[k][j][0] != '-'){
                            clear = 0;
                            break;
                        }
                    }
                    if(clear) return 1;
                }
            }
        }
    }
    // checking bishop & queen attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(piece_colour(board[i][j]) != myCurruntColour){
                if(abs(r - i) == abs(c - j)){
                    int clear = 1;
                    int dr = (r > i) ? 1 : -1;
                    int dc = (c > j) ? 1 : -1;
                    int x = i + dr;
                    int y = j + dc;
                    while(x != r && y != c){
                        if(board[x][y][0] != '.' && board[x][y][0] != '-'){
                            clear = 0;
                            break;
                        }
                        x += dr;
                        y += dc;
                    }
                    if(clear) return 1;
                }
            }
        }
    }
    return 0;
}

void castling(int i, int j, int r, int c){
   if((u8) board[i][j][2] == WhiteKing){
    if(haveMovedAt(7,4) == 0){
        if(r == 7 && c == 6 && strcmp(board[7][7], whiteRook) == 0 && haveMovedAt(7, 7) == 0 && board[7][5][0] == '-' 
        && board[7][6][0] == '.' && isSquareAttacked(7, 4, 0) == 0 && isSquareAttacked(7, 5, 0) == 0 && isSquareAttacked(7, 6, 0) == 0){
            strcpy(board[7][6], whiteKing);
            strcpy(board[7][5], whiteRook);
            strcpy(board[7][4], ".");
            strcpy(board[7][7], "-");
            moved[7][6] = 1;
            moved[7][5] = 1;
            moved[7][4] = 0;
            moved[7][7] = 0;
        }
        if(r == 7 && c == 2 && strcmp(board[7][0], whiteRook) == 0 && haveMovedAt(7,0) == 0 && board[7][3][0] == '-' && board[7][2][0] == '.' 
        && board[7][1][0] == '-' && isSquareAttacked(7, 4, 0) == 0 && isSquareAttacked(7, 3, 0) == 0 && isSquareAttacked(7, 2, 0) == 0){
            strcpy(board[7][2], whiteKing);
            strcpy(board[7][3], whiteRook);
            strcpy(board[7][4], ".");
            strcpy(board[7][0], ".");
            moved[7][2] = 1;
            moved[7][3] = 1;
            moved[7][4] = 0;
            moved[7][0] = 0;
        }
    }
}
    if(board[i][j][2] == BlackKing){
        if(haveMovedAt(0,4) == 0){
            if(r == 0 && c == 6 && strcmp(board[0][7], blackRook) == 0 && haveMovedAt(0,7) == 0 && board[0][5][0] == '.' && board[0][6][0] == '-'
            && isSquareAttacked(0, 4, 1) == 0 && isSquareAttacked(0, 5, 1) == 0 && isSquareAttacked(0, 6, 1) == 0){
                strcpy(board[0][6], blackKing);
                strcpy(board[0][5], blackRook);
                strcpy(board[0][4], "-");
                strcpy(board[0][7], ".");
                moved[0][6] = 1;
                moved[0][5] = 1;
                moved[0][4] = 0;
                moved[0][7] = 0;
            }
            if(r == 0 && c == 2 && strcmp(board[0][0], blackRook) == 0 && haveMovedAt(0,0) == 0 && board[0][3][0] == '.' && board[0][2][0] == '-'
            && board[0][1][0] == '.' && isSquareAttacked(0, 4, 1) == 0 && isSquareAttacked(0, 3, 1) == 0 && isSquareAttacked(0, 2, 1) == 0){
                strcpy(board[0][2], blackKing);
                strcpy(board[0][3], blackRook);
                strcpy(board[0][4], "-");
                strcpy(board[0][0], ".");
                moved[0][2] = 1;
                moved[0][3] = 1;
                moved[0][4] = 0;
                moved[0][0] = 0;
            }
        }
    }
}

int kingInCheck(char current_king_piece[4]){
    int i, j;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            if(strcmp(board[i][j], current_king_piece) == 0) {
                return isSquareAttacked(i, j, piece_colour(current_king_piece));
            }
        }
    }
    return 0;
}

int isCheckmate(int colour){
    int i; int j; int r; int c;
    char king_piece[4];
    int king_i = -1; int king_j = -1;

    if(colour == 0) memcpy(king_piece, whiteKing, 4);
    else memcpy(king_piece, blackKing, 4);
    
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(memcmp(board[i][j], king_piece, 4) == 0){
                king_i = i;
                king_j = j;
                break;
            }
        }
        if(king_i != -1) break;
    }
    if(king_i == -1) return 0;
    if(!kingInCheck(king_piece)) return 0;
    checking_checkmate = 1;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(board[i][j][0] == '.' || board[i][j][0] == '-') continue;
            if(piece_colour(board[i][j]) != colour) continue;
            for(r = 0; r < 8; r++){
                for(c = 0; c < 8; c++){
                    char save_src[4]; char save_dest[4];
                    int save_moved_src; int save_moved_dest;
                    memcpy(save_src, board[i][j], 4);
                    memcpy(save_dest, board[r][c], 4);
                    save_moved_src = moved[i][j];
                    save_moved_dest = moved[r][c];
                    u8 piece_type = (u8)board[i][j][2];
                    if(piece_type == WhitePawn){
                        white_pawn(i, j, r, c);
                    } else if(piece_type == BlackPawn){
                        black_pawn(i, j, r, c);
                    }else if(piece_type == WhiteRook || piece_type == BlackRook){
                        rook(i, j, r, c, colour);
                    } else if(piece_type == WhiteKnight || piece_type == BlackKnight){
                        knight(i, j, r, c, colour);
                    } else if(piece_type == WhiteBishop || piece_type == BlackBishop){
                        bishop(i, j, r, c, colour);
                    } else if(piece_type == WhiteQueen || piece_type == BlackQueen){
                        queen(i, j, r, c, colour);
                    } else if(piece_type == WhiteKing || piece_type == BlackKing){
                        king(i, j, r, c, colour);
                    }
                    int move_happened = 0;
                    if(memcmp(board[i][j], save_src, 4) != 0 || memcmp(board[r][c], save_dest, 4) != 0){
                        move_happened = 1;
                    }
                    int escaped = 0;
                    if(move_happened){
                        if(!kingInCheck(king_piece)){
                            escaped = 1;
                        }
                    }
                    memcmp(board[i][j], save_src, 4);
                    memcmp(board[r][c], save_dest, 4);
                    moved[i][j] = save_moved_src;
                    moved[r][c] = save_moved_dest;
                    if(escaped){
                        checking_checkmate = 0;
                        return 0;
                    }
                }
            }
        }
    }
    checking_checkmate = 0;
    return 1;
}

int isStalemate(int colour){
    int i; int j; int r; int c;
    char king_piece[4];
    int king_i = -1; int king_j = -1;

    if(colour == 0) memcpy(king_piece, whiteKing, 4);
    else memcpy(king_piece, blackKing, 4); 

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(memcmp(board[i][j], king_piece, 4) == 0){
                king_i = i;
                king_j = j;
                break;
            }
        }
        if(king_i != -1) break;
    }
    if(king_i == -1) return 0;
    if(kingInCheck(king_piece)) return 0;
    checking_stalemate = 1;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(board[i][j][0] == '.' || board[i][j][0] == '-') continue;
            if(piece_colour(board[i][j]) != colour) continue;    
            for(r = 0; r < 8; r++){
                for(c = 0; c < 8; c++){
                    char save_src[4]; char save_dest[4];
                    int save_moved_src; int save_moved_dest;
                    memcpy(save_src, board[i][j], 4);
                    memcpy(save_dest, board[r][c], 4);
                    save_moved_src = moved[i][j];
                    save_moved_dest = moved[r][c];
                    u8 piece_type = (u8)board[i][j][2];

                    if(piece_type == WhitePawn){
                        white_pawn(i, j, r, c);
                    } else if(piece_type == BlackPawn){
                        black_pawn(i, j, r, c);
                    } else if(piece_type == WhiteRook || piece_type == BlackRook){
                        rook(i, j, r, c, colour);
                    } else if(piece_type == WhiteKnight || piece_type == BlackKnight){
                        knight(i, j, r, c, colour);
                    } else if(piece_type == WhiteBishop || piece_type == BlackBishop){
                        bishop(i, j, r, c, colour);
                    } else if(piece_type == WhiteQueen || piece_type == BlackQueen){
                        queen(i, j, r, c, colour);
                    } else if(piece_type == WhiteKing || piece_type == BlackKing){
                        king(i, j, r, c, colour);
                    }
                    int move_happened = 0;
                    if(memcmp(board[i][j], save_src, 4) != 0 || memcmp(board[r][c], save_dest, 4) != 0){
                        move_happened = 1;
                    }
                    int legal_move = 0;
                    if(move_happened){
                        if(!kingInCheck(king_piece)){
                            legal_move = 1;
                        }
                    }
                    memcpy(board[i][j], save_src, 4);
                    memcpy(board[r][c], save_dest, 4);
                    moved[i][j] = save_moved_src;
                    moved[r][c] = save_moved_dest;
                    if(legal_move){
                        checking_stalemate = 0;
                        return 0;
                    }
                }
            }
        }
    }
    checking_stalemate = 0;
    return 1;
}

int isDeadPosition(){}

int must_promote(int i, int j, int r, int c){
    if((u8) board[i][j][2] == BlackPawn && i==6 && r-i==1 && c==j &&  (board[r][c][0] == '-' || board[r][c][0] == '.')){
        return 1;
    }
    if((u8) board[i][j][2] == BlackPawn && i==6 && r-i == 1 && abs(c-j)==1 && isWhite(board[r][c])==1){
        return 1;
    }
    if((u8) board[i][j][2] == WhitePawn && i==1 && i-r==1 && c==j && (board[r][c][0] == '-' || board[r][c][0] == '.')){
        return 1;
    }
    if((u8) board[i][j][2] == WhitePawn && i==1 && i-r == 1 && abs(c-j)==1 && isBlack(board[r][c])==1){
        return 1;
    }
    return 0;
}

void promotion(int i, int j, int r, int c, char promotion_piece[4]){
    int possible_promotion=0;
    invalid_move=0;
    if((u8) board[i][j][2] == BlackPawn && i==6 && r-i==1 ){
        if((c==j && (board[r][c][0] == '-' || board[r][c][0] == '.')) || (abs(c-j)==1 && isWhite(board[r][c])==1)){
            possible_promotion=1;
            if(possible_promotion){
                if((u8) promotion_piece[2] >= BlackQueen && (u8) promotion_piece[2] <= BlackKnight){
                    if(abs(c-j)==1 && isWhite(board[r][c])){
                        memcpy(killed_arrW[counterW],board[r][c],4);
                        counterW++;
                    }
                    memcpy(board[r][c],promotion_piece,4);
                    memcpy(killed_arrB[counterB], board[i][j],4);
                    counterB++;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                    change( i, j);
                }
                else{
                    invalid_move=1;
                    printf("Cannot promote the Black pawn\n");
                }
            }
            else{
                invalid_move=1;
                printf("Cannot promote the Black pawn\n");
            }
        }
    }     
    else if((u8) board[i][j][2] == WhitePawn && i==1 && i-r==1 ){
        if((c==j && (board[r][c][0] == '-' || board[r][c][0] == '.')) || (abs(c-j)==1 && isBlack(board[r][c])==1)){
            possible_promotion=1;
            if(possible_promotion){
                if((u8) promotion_piece[2] >= WhiteQueen && (u8) promotion_piece[2] <= WhiteKnight){
                    if(abs(c-j)==1 && isBlack(board[r][c])){
                        memcpy(killed_arrB[counterB],board[r][c],4);
                        counterB++;
                    }
                    memcpy(board[r][c],promotion_piece,4);
                    memcpy(killed_arrW[counterW], board[i][j],4);
                    counterW++;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                    change( i, j);
                }
                else{
                    invalid_move=1;
                    printf("Cannot promote the White pawn\n");
                }
            }
            else{
                invalid_move=1;
                printf("Cannot promote the White pawn\n");
            }
        }
    }       
}

void escapingKingInCheck(int i, int j, int r, int c, int colour){
    char kPiece[4];
    if(colour == 1) memcpy(kPiece, whiteKing, 4);
    else memcpy(kPiece, blackKing, 4);
    if(kingInCheck(kPiece) == 1){
        printf("King in check, Enter a valid place to escape: ");
        if(board[i][j][2] == BlackKing || board[i][j][2] == WhiteKing){
            king(i, j, r, c, colour);
        }else if(board[i][j][2] == BlackRook || board[i][j][2] == WhiteRook){
            rook(i, j, r, c, colour);
        }else if(board[i][j][2] == BlackQueen || board[i][j][2] == WhiteQueen){
            queen(i, j, r, c, colour);
        }else if(board[i][j][2] == BlackBishop || board[i][j][2] == WhiteBishop){
            bishop(i, j, r, c, colour);
        }else if(board[i][j][2] == BlackKnight || board[i][j][2] == WhiteKnight){
            knight(i, j, r, c, colour);
        }else if(board[i][j][2] == BlackPawn){
            black_pawn(i, j, r, c);
        }else if(board[i][j][2] == WhitePawn){
            white_pawn(i, j, r, c);
        }
        if(kingInCheck(kPiece) == 1){
            printf("Invalid move, King still in check\n");
        }
    }
}