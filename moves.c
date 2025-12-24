#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
extern int moved_pawnW[8][8];
extern int moved_pawnB[8][8];
extern int enPassantDone;
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
extern int checking_checkmate;

int isWhite(char piece[4]){
    u8 val = (u8)piece[2];
    if(val >= WhiteKing && val <= WhitePawn){
        return 1;
    }
    return 0;
}

int isBlack(char piece[4]){
    u8 val = (u8)piece[2];
    if(val >= BlackKing && val <= BlackPawn){
        return 1;
    }
    return 0;
}

int piece_colour(char piece[4]){
    if(isWhite(piece)){
        return 1;
    }
    else{
        return 0;
    }  
}

void change(int i, int j){
    if(i % 2 == 0 && j % 2 == 0){
        memcpy(board[i][j], "-", 2);
    }
    if(i % 2 == 1 && j % 2 == 1){
        memcpy(board[i][j], "-", 2);
    }
    if(i % 2 == 1 && j % 2 == 0){
        memcpy(board[i][j], ".", 2);
    }
    if(i % 2 == 0 && j % 2 == 1){
        memcpy(board[i][j], ".", 2);
    }
}

void knight(int i, int j, int r, int c, int colour){
    invalid_move = 0;
    if(abs(r-i)==1 && abs(c-j)==2 || abs(r-i)==2 && abs(c-j)==1){
        if(board[r][c][0] == '-' || board[r][c][0] == '.'){
            char temp[4];
            memcpy(temp, board[r][c], 4);
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
            if(temp[0] == '-'){
                memcpy(board[i][j], ".", 2);
            }
            else{
                memcpy(board[i][j], "-", 2);
            }
        }
        else if(piece_colour(board[r][c]) != colour){
            if(isWhite(board[r][c])){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++;
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++;
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
            change( i, j);
        }
        else if(piece_colour(board[r][c]) == colour){
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece\n");
        }
    }
    else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
    }
}

void queen(int i, int j, int r, int c, int colour){
    invalid_move = 0;
    int k; int p; int emptyPath=1;
    if(abs(r - i) == abs(c - j)){
        if(i>r && j>c){
            k = i-1; p = j-1;
            while(k>r && p>c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k--;
                p--;
            }
        }
        else if(i<r && j<c){
            k = i+1; p = j+1;
            while(k<r && p<c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k++;
                p++;
            }
        }
        else if(i<r && j>c){
            k = i+1; p = j-1;
            while(k<r && p>c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k++;
                p--;
            }
        }
        else if(i>r && j<c){
            k = i-1; p = j+1;
            while(k>r && p<c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k--;
                p++;
            }
        }
    }
    else if((r == i && (c > j || c < j)) || (c == j && (r > i || r < i))){
        if(r==i){
            if(j>c){
                p = j-1;
                while(p>c){
                    if(board[r][p][0] == '.' || board[r][p][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    p--;
                }
            }
            else if(j<c){
                p = j+1;
                while(p<c){
                    if(board[r][p][0] == '.' || board[r][p][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    p++;
                }
            }
        }
        else if(c==j){
            if(i>r){
                k = i-1;
                while(k>r){
                    if(board[k][c][0] == '.' || board[k][c][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    k--;
                }
            }
            else if(i<r){
                k = i+1;
                while(k<r){
                    if(board[k][c][0] == '.' || board[k][c][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    if(emptyPath == 1){
        if(board[r][c][0] == '-' && abs(r-i) == abs(c-j) || board[r][c][0] == '.' && abs(r-i) == abs(c-j)){
            char temp[4];
            memcpy(temp, board[r][c], 4);
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], temp, 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(board[r][c][0] == '-' && i == r && r&1==1 || board[r][c][0] == '-'  && j == c && c&1 == 1){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], ".", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(board[r][c][0] == '-' && i == r && r&1==0 || board[r][c][0] == '-' && j == c && c&1 == 0){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], "-", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(board[r][c][0] == '.' && i == r && r&1 == 0 || board[r][c][0] == '.' && j == c && c&1 == 0){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], ".", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(board[r][c][0] == '.' && i == r && r&1 == 1 || board[r][c][0] == '.' && j == c && c&1 == 1){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], "-", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(piece_colour(board[r][c]) != colour && (abs(r-i) == abs(c-j) || i==r || j==c)){
            if(isWhite(board[r][c])){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++;
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++;
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
            change( i ,j);
        }
        else if(piece_colour(board[r][c]) == colour && (abs(r-i) == abs(c-j) || i==r || j==c)){
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat friendly piece\n");
        }
        else{
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
        }
    }
    else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
    }
}

void white_pawn(int i, int j, int r, int c){
    invalid_move = 0;
    int firstMove=0;
    int possible_en_passant=0;   enPassantDone=0;
    if(isWhite(board[i][j])){
        if(i==6){
            firstMove = 1;
            if(firstMove == 1 && i-r == 2 && j==c && (board[r+1][c][0] == '.' || board[r+1][c][0] == '-')){
                if(board[r][c][0] == '-' || board[r][c][0] == '.'){
                    char temp[4];
                    memcpy(temp, board[r][c], 4);
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], temp, 4);
                    moved_pawnW[r][c] = 2;
                    moved_pawnW[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else{
                    invalid_move = 1;
                    if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                }
            }
            else if(firstMove == 1 && i-r == 1 && j==c){
                if(board[r][c][0] == '-'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], ".", 2);
                    moved_pawnW[r][c] = 1;
                    moved_pawnW[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else if(board[r][c][0] == '.'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], "-", 2);
                    moved_pawnW[r][c] = 1;
                    moved_pawnW[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else{
                    invalid_move = 1;
                    if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                }           
            }
            else if(i-r == 1 && c-j == 1 && isBlack(board[r][c]) || i-r == 1 && j-c == 1 && isBlack(board[r][c])){
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++;
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                change( i, j);
            }
            else{
                invalid_move = 1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
            }
        }
        else if(i != 6){
            if(i-r==1 && j==c){
                if(board[r][c][0] == '-'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], ".", 2);
                    moved_pawnW[r][c] = 1;
                    moved_pawnW[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else if(board[r][c][0] == '.'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], "-", 2);
                    moved_pawnW[r][c] = 1;
                    moved_pawnW[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else{
                    invalid_move = 1;
                    if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                }
            }
            else if(i-r == 1 && c-j == 1 && isBlack(board[r][c]) || i-r == 1 && j-c == 1 && isBlack(board[r][c])){
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++;
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                change( i, j);
            }
            else if(abs(c-j)==1 && i-r==1 && i==3 && (board[r][c][0] == '-' || board[r][c][0] == '.')){
                possible_en_passant=1;
                if(possible_en_passant){
                    if((u8) board[i][c][2] == BlackPawn && moved_pawnB[i][c] == 2){
                        memcpy(killed_arrB[counterB],board[i][c],4);
                        counterB++;
                        memcpy(board[r][c],board[i][j],4);
                        moved[r][c] = 1;
                        moved[i][j] = 0;
                        if(i % 2 == 0 && j % 2 == 0){
                            memcpy(board[i][j], "-", 2);
                            memcpy(board[i][c],".",2);
                        }
                        if(i % 2 == 1 && j % 2 == 1){
                            memcpy(board[i][j], "-", 2);
                            memcpy(board[i][c],".",2);
                        }
                        if(i % 2 == 1 && j % 2 == 0){
                            memcpy(board[i][j], ".", 2);
                            memcpy(board[i][c],"-",2);
                        }
                        if(i % 2 == 0 && j % 2 == 1){
                            memcpy(board[i][j], ".", 2);
                            memcpy(board[i][c],"-",2);
                        }
                        enPassantDone=1;
                    }
                    else{
                        invalid_move = 1;
                        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                    }
                }
            }
            else{
                invalid_move = 1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
            }
        }
    }
}

void black_pawn( int i, int j, int r, int c){
    invalid_move = 0;
    int firstMove=0;
    int possible_en_passant=0;    enPassantDone=0;
    if(isBlack(board[i][j])){
        if(i==1){
            firstMove = 1;
            if(firstMove == 1 && r-i == 2 && j==c && (board[r-1][c][0] == '.' || board[r-1][c][0] == '-')){
                if(board[r][c][0] == '-' || board[r][c][0] == '.'){
                    char temp[4];
                    memcpy(temp, board[r][c], 4);
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], temp, 4);
                    moved_pawnB[r][c] = 2;
                    moved_pawnB[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else{
                    invalid_move=1;
                    if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                }
            }
            else if(firstMove == 1 && r-i == 1 && j==c){
                if(board[r][c][0] == '-'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], ".", 2);
                    moved_pawnB[r][c] = 1;
                    moved_pawnB[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else if(board[r][c][0] == '.'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], "-", 2);
                    moved_pawnB[r][c] = 1;
                    moved_pawnB[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else if(isWhite(board[r][c]) || isBlack(board[r][c])){
                    invalid_move=1;
                    if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                }
            }
            else if(r-i == 1 && c-j == 1 && isWhite(board[r][c]) || r-i == 1 && j-c == 1 && isWhite(board[r][c])){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++;
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                change( i, j);
            }
            else{
                invalid_move = 1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
            }
        }
        else if(i != 1){
            if(r-i==1 && j==c){
                if(board[r][c][0] == '-'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], ".", 2);
                    moved_pawnB[r][c] = 1;
                    moved_pawnB[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else if(board[r][c][0] == '.'){
                    memcpy(board[r][c], board[i][j], 4);
                    memcpy(board[i][j], "-", 2);
                    moved_pawnB[r][c] = 1;
                    moved_pawnB[i][j] = 0;
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                }
                else{
                    invalid_move=1;
                    if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                }
            }
            else if(r-i == 1 && c-j == 1 && isWhite(board[r][c]) || r-i == 1 && j-c == 1 && isWhite(board[r][c])){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++;
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                change( i, j);
            }
            else if(abs(c-j)==1 && r-i==1 && i==4 && (board[r][c][0] == '-' || board[r][c][0] == '.')){
                possible_en_passant=1;
                if(possible_en_passant){
                    if(board[i][c][2] == WhitePawn && moved_pawnW[i][c] == 2){
                        memcpy(killed_arrW[counterW],board[i][c],4);
                        counterW++;
                        memcpy(board[r][c],board[i][j],4);
                        moved[r][c] = 1;
                        moved[i][j] = 0;
                        if(i % 2 == 0 && j % 2 == 0){
                            memcpy(board[i][j], "-", 2);
                            memcpy(board[i][c],".",2);
                        }
                        if(i % 2 == 1 && j % 2 == 1){
                            memcpy(board[i][j], "-", 2);
                            memcpy(board[i][c],".",2);
                        }
                        if(i % 2 == 1 && j % 2 == 0){
                            memcpy(board[i][j], ".", 2);
                            memcpy(board[i][c],"-",2);
                        }
                        if(i % 2 == 0 && j % 2 == 1){
                            memcpy(board[i][j], ".", 2);
                            memcpy(board[i][c],"-",2);
                        }
                        enPassantDone=1;
                    }
                    else{
                        invalid_move=1;
                        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                    }
                }
            }
            else{
                invalid_move=1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
            }
        }
    }
}

void bishop(int i, int j, int r, int c, int colour){
    int k ; int p ;  int emptyPath=1;  invalid_move = 0;
    if(abs(r - i) == abs(c - j)){
        if(i>r && j>c){
            k = i-1; p = j-1;
            while(k>r && p>c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k--;
                p--;
            }
        }
        else if(i<r && j<c){
            k = i+1; p = j+1;
            while(k<r && p<c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k++;
                p++;
            }
        }
        else if(i<r && j>c){
            k = i+1; p = j-1;
            while(k<r && p>c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k++;
                p--;
            }
        }
        else if(i>r && j<c){
            k = i-1; p = j+1;
            while(k>r && p<c){
                if(board[k][p][0] == '.' || board[k][p][0] == '-'){
                    emptyPath = 1;
                }
                else{
                    emptyPath = 0;
                    break;
                }
                k--;
                p++;
            }
        }
    }
    if(emptyPath == 1){
        if((board[r][c][0] == '-' || board[r][c][0] == '.') && abs(r - i) == abs(c - j)){
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
            change( i, j);
        }  
        else  if(piece_colour(board[r][c]) != colour && abs(r - i) == abs(c - j)){
            if(isWhite(board[r][c])){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++;
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++;
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;                
            change( i, j);
        }  
        else if(piece_colour(board[r][c]) == colour && abs(r - i) == abs(c - j)){ 
            invalid_move=1;   
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece\n");
        }
        else{
            invalid_move = 1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
        }
    }
    else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
    }
}


void rook(int i, int j, int r, int c, int colour){
    int k ; int p ; int emptyPath=1;invalid_move = 0;
    if((r == i && (c > j || c < j)) || (c == j && (r > i || r < i))){
        if(r==i){
            if(j>c){
                p = j-1;
                while(p>c){
                    if(board[r][p][0] == '.' || board[r][p][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    p--;
                }
            }
            else if(j<c){
                p = j+1;
                while(p<c){
                    if(board[r][p][0] == '.' || board[r][p][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    p++;
                }
            }
        }
        else if(c==j){
            if(i>r){
                k = i-1;
                while(k>r){
                    if(board[k][c][0] == '.' || board[k][c][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    k--;
                }
            }
            else if(i<r){
                k = i+1;
                while(k<r){
                    if(board[k][c][0] == '.' || board[k][c][0] == '-'){
                        emptyPath=1;
                    }
                    else{
                        emptyPath=0;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    if(emptyPath == 1){
        if((board[r][c][0] == '-' || board[r][c][0] == '.') && ((r == i && (c > j || c < j)) || (c == j && (r > i || r < i)))){
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
            change( i, j);
        }  
        else  if(piece_colour(board[r][c]) != colour && ((r == i && (c > j || c < j)) || (c == j && (r > i || r < i)))){
            if(isWhite(board[r][c])){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++;
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++;
            }
            moved[r][c] = 1;
            moved[i][j] = 0;
            memcpy(board[r][c], board[i][j], 4);
            change( i, j);
        }
        else if(piece_colour(board[r][c]) == colour && ((r == i && (c > j || c < j)) || (c == j && (r > i || r < i)))){
            invalid_move=1;   
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece\n");
        }
        else{
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
        }
    }
    else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
    }
}

void king(int i, int j, int r, int c, int colour){
    invalid_move = 0;
    if(board[r][c][0] == '-' || board[r][c][0] == '.'){
        if((r == i && c == j + 1) || (r == i && c == j - 1) || (r == i + 1 && c == j) || (r == i - 1 && c == j) || (r == i + 1 && c == j + 1) || (r == i + 1 && c == j - 1) || (r == i - 1 && c == j - 1) || (r == i - 1 && c == j + 1)){
            moved[r][c] = 1;
            moved[i][j] = 0;
            memcpy(board[r][c], board[i][j], 4);
            change( i, j);
         }  else{
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
         }
    }
     else  if(piece_colour(board[r][c]) != colour){
                if((u8) board[r][c][2] == WhiteKing || (u8) board[r][c][2] == BlackKing){
                        if(isWhite(board[r][c])){
                            memcpy(killed_arrW[counterW], board[r][c], 4);
                            counterW++;
                        }
                        else{
                            memcpy(killed_arrB[counterB], board[r][c], 4);
                            counterB++;
                        }
                        moved[r][c] = 1;
                        moved[i][j] = 0;
                        memcpy(board[r][c], board[i][j], 4);
                        change( i, j);
                    }else{
                        invalid_move=1;
                        if(!checking_checkmate && !checking_stalemate) printf("Invalid move\n");
                    }

     }  else if(piece_colour(board[r][c]) == colour){
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece\n");
     }
}