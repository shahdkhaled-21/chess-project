#include <stdio.h>
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
extern char opponent_piece[4];
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
    int invalid_move=0;
    if(abs(r-i)==1 && abs(c-j)==2 || abs(r-i)==3 && abs(c-j)==1){
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
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece");
        }
    }
    else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
    }
}

void queen(int i, int j, int r, int c, int colour){
    int invalid_move=0;
    int k=i;int p=j;int emptyPath=0;
    if(abs(i-r)==abs(j-c)){
        if(i>r && j>c){
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
            while(k<r && p>c){
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
    else if(r==i){
        if(j>c){
            while(p>c){
                if(board[r][p][0] == '.' || board[r][p][0] == '-' ){
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
            while(p<c){
                if(board[r][p][0] == '.' || board[r][p][0] == '-' ){
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
            while(k>r){
                if(board[k][c][0] == '.' || board[k][c][0] == '-' ){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k--;
            }
        }
        else if(j<c){
            while(k<r){
                if(board[k][c][0] == '.' || board[k][c][0] == '-' ){
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
    if(emptyPath == 1){
        if(board[r][c][0] == '-' && abs(r-i) == abs(c-j) || board[r][c][0] == '.' && abs(r-i) == abs(c-j)){
            char temp[4];
            memcpy(temp, board[r][c], 4);
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], temp, 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(board[r][c][0] == '-' && i==r && r&1==1 || board[r][c][0] == '-'  && j==c && c&1 == 1){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], ".", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(board[r][c][0] == '-' && i==r && r&1==0 || board[r][c][0] == '-' && j == c && c&1 == 0){
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
            change( i ,j);
        }
        else if(piece_colour(board[r][c]) == colour){
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat friendly piece");
        }
    }
    else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
    }
}

void pawn(int i, int j, int r, int c){
    int invalid_move=0;
    int firstMove=0;
    int possible_en_passant=0;
    if(isWhite(board[i][j])){
        if(i==6){
            firstMove = 1;
        }
        if(firstMove == 1 && i-r == 2 && j==c){
            if(board[r][c][0] == '-' || board[r][c][0] == '.'){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(isBlack(board[r][c]) || isWhite(board[r][c])){
                invalid_move=1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
            }
        }
        else if(i-r==1 && j==c){
            if(board[r][c][0] == '-'){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], ".", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(board[r][c][0] == '.'){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], "-", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(isBlack(board[r][c]) || isWhite(board[r][c])){
                invalid_move=1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
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
        if(abs(c-j)==1 && i-r==1 && i==3 && isBlack(board[r][c])!=1 && isWhite(board[r][c])!=1){
            possible_en_passant=1;
        }
        if(possible_en_passant){
            if((u8) board[r+1][c][2] == BlackPawn){ //&&history move of this black pawn*********
                memcpy(killed_arrB[counterB],"\u265F",4);
                counterB++;
                memcpy(board[r][c],"\u2659",4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                if(i % 2 == 0 && j % 2 == 0){
                    memcpy(board[i][j], "-", 2);
                    memcpy(board[r+1][c],".",2);
                }
                if(i % 2 == 1 && j % 2 == 1){
                    memcpy(board[i][j], "-", 2);
                    memcpy(board[r+1][c],".",2);
                }
                if(i % 2 == 1 && j % 2 == 0){
                    memcpy(board[i][j], ".", 2);
                    memcpy(board[r+1][c],"-",2);
                }
                if(i % 2 == 0 && j % 2 == 1){
                    memcpy(board[i][j], ".", 2);
                    memcpy(board[r+1][c],"-",2);
                }
            }
        }
        else{
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
        }
    }
    else if(isBlack(board[i][j])){
        if(i==1){
            firstMove = 1;
        }
        if(firstMove == 1 && r-i == 2 && j==c){
            if(board[r][c][0] == '-' || board[r][c][0] == '.'){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(isWhite(board[r][c]) || isBlack(board[r][c])){
                invalid_move=1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
            }
        }
        else if(r-i==1 && j==c){
            if(board[r][c][0] == '-'){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], ".", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(board[r][c][0] == '.'){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], "-", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(isWhite(board[r][c]) || isBlack(board[r][c])){
                invalid_move=1;
                if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
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
        else if(abs(c-j)==1 && r-i==1 && i==4 && isWhite(board[r][c])!=1 && isBlack(board[r][c])!=1){
            possible_en_passant=1;
        }
        if(possible_en_passant){
            if(board[r-1][c][2] == WhitePawn ){ //&&history move of this white pawn*********
                memcpy(killed_arrW[counterW],"\u2659",4);
                counterW++;
                memcpy(board[r][c],"\u265F",4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                if(i % 2 == 0 && j % 2 == 0){
                    memcpy(board[i][j], "-", 2);
                    memcpy(board[r-1][c],".",2);
                }
                if(i % 2 == 1 && j % 2 == 1){
                    memcpy(board[i][j], "-", 2);
                    memcpy(board[r-1][c],".",2);
                }
                if(i % 2 == 1 && j % 2 == 0){
                    memcpy(board[i][j], ".", 2);
                    memcpy(board[r-1][c],"-",2);
                }
                if(i % 2 == 0 && j % 2 == 1){
                    memcpy(board[i][j], ".", 2);
                    memcpy(board[r-1][c],"-",2);
                }
            }
        }
        else{
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
        }
    }
}

void bishop(int i, int j, int r, int c, int colour){
    int k = i; int p = j; int emptyPath=0;int invalid_move=0;
    if(abs(r - i) == abs(c - j)){
        if(i>r && j>c){
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
            while(k<r && p>c){
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
        if(emptyPath == 1){
            if(board[r][c][0] == '-' || board[r][c][0] == '.'){
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                change( i, j);
            }  else  if(piece_colour(board[r][c]) != colour){
                    if(isWhite(opponent_piece)){
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

        }  else if(piece_colour(board[r][c]) == colour){ 
            invalid_move=1;   
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece");
        }
      }
      else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
      }
    }else{ 
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
    }
}

void rook(int i, int j, int r, int c, int colour){
    int k = i; int p = j; int emptyPath=0;int invalid_move=0;
    if((r == i && (c > j || c < j)) || (c == j && (r > i || r < i))){
        if(r==i){
          if(j>c){
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
        else if(j<c){
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
     if(emptyPath == 1){
            if(board[r][c][0] == '-' || board[r][c][0] == '.'){
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
                change( i, j);
            }  
            else  if(piece_colour(board[r][c]) != colour){
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
          else if(piece_colour(board[r][c]) == colour){
            invalid_move=1;   
            if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece");
        }
    }
      else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
      }
    }else{
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
    }
}

void king(int i, int j, int r, int c, int colour){
    int invalid_move=0;
    if(board[r][c][0] == '-' || board[r][c][0] == '.'){
        if((r == i && c == j + 1) || (r == i && c == j - 1) || (r == i + 1 && c == j) || (r == i - 1 && c == j) || (r == i + 1 && c == j + 1) || (r == i + 1 && c == j - 1) || (r == i - 1 && c == j - 1) || (r == i - 1 && c == j + 1)){
            moved[r][c] = 1;
            moved[i][j] = 0;
            memcpy(board[r][c], board[i][j], 4);
            change( i, j);
         }  else{
            invalid_move=1;
            if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
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
                        if(!checking_checkmate && !checking_stalemate) printf("Invalid move");
                    }

     }  else if(piece_colour(board[r][c]) == colour){
        invalid_move=1;
        if(!checking_checkmate && !checking_stalemate) printf("Cannot eat a friendly piece");
     }
}