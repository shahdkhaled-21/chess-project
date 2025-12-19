#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char board[8][8][4];
extern int i, j, r, c;
extern int counterW;
extern int counterB;
extern int invalid_move;
extern char killed_arrW[15][4];
extern char killed_arrB[15][4];
extern char opponent_piece[4], friendly_piece[4];
extern char whiteKing[4];
extern char whiteRook[4];
extern char blackKing[4];
extern char blackRook[4];
extern char "\u2659"[4];
extern char "\u265F"[4];
extern int moved[8][8];

void knight(int i, int j, int r, int c){
    invalid_move=0;
    if(abs(r-i)==1 && abs(c-j)==2 || abs(r-i)==3 && abs(c-j)==1){
        if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".") == 0){
            char temp[4];
            memcpy(temp, board[r][c], 4);
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
            if(strcmp(temp, "-") == 0){
                memcpy(board[i][j], ".", 2);
            }
            else{
                memcpy(board[i][j], "-", 2);
            }
        }
        else if(strcmp(board[r][c], opponent_piece) == 0){
            if(isWhite(opponent_piece)){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
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
        else if(strcmp(board[r][c], friendly_piece) == 0){
            invalid_move=1;
            printf("Cannot eat a friendly piece");
        }
    }
    else{
        invalid_move=1;
        printf("Invalid move");
    }
}

void queen(int i, int j, int r, int c){
    invalid_move=0;
    int k=i;int p=j;int emptyPath=0;
    if(abs(i-r)==abs(j-c)){
        if(i>r && j>c){
            while(k>r && p>c){
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
        if(strcmp(board[r][c], "-") == 0 && abs(r-i) == abs(c-j) || strcmp(board[r][c], ".") == 0 && abs(r-i) == abs(c-j)){
            char temp[4];
            memcpy(temp, board[r][c], 4);
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], temp, 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(strcmp(board[r][c], "-") == 0 && i==r && r&1==1 || strcmp(board[r][c], "-") == 0  && j==c && c&1 == 1){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], ".", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(strcmp(board[r][c], "-") == 0 && i==r && r&1==0 || strcmp(board[r][c], "-") == 0 && j == c && c&1 == 0){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], "-", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(strcmp(board[r][c], ".") == 0 && i == r && r&1 == 0 || strcmp(board[r][c], ".") == 0 && j == c && c&1 == 0){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], ".", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(strcmp(board[r][c], ".") == 0 && i == r && r&1 == 1 || strcmp(board[r][c], ".") == 0 && j == c && c&1 == 1){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], "-", 2);
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
        else if(strcmp(board[r][c], opponent_piece) == 0){
            if(isWhite(opponent_piece)){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
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
        else if(strcmp(board[r][c], friendly_piece) == 0){
            invalid_move=1;
            printf("Cannot eat friendly piece");
        }
    }
    else{
        invalid_move=1;
        printf("Invalid move");
    }
}

void pawn(int i, int j, int r, int c){
    invalid_move=0;
    int firstMove=0;
    int possible_en_passant=0;
    if(isWhite(board[i][j])){
        if(i==6 && strcmp(board[i][j],"\u2659")==0){
            firstMove = 1;
        }
        if(firstMove == 1 && i-r == 2 && j==c){
            if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".")){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(strcmp(board[r][c], opponent_piece) == 0 || strcmp(board[r][c], friendly_piece) == 0){
                invalid_move=1;
                printf("Invalid move");
            }
        }
        else if(i-r==1 && j==c){
            if(strcmp(board[r][c], "-") == 0){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], ".", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(strcmp(board[r][c], ".") == 0){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], "-", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(strcmp(board[r][c], opponent_piece) == 0 || strcmp(board[r][c], friendly_piece) == 0){
                invalid_move=1;
                printf("Invalid move");
            }
        }
        else if(i-r == 1 && c-j == 1 && strcmp(board[r][c], opponent_piece) == 0 || i-r == 1 && j-c == 1 && strcmp(board[r][c], opponent_piece) == 0){
            if(isWhite(opponent_piece)){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
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
        if(strcmp(board[i][j],"\u2659")==0 && abs(c-j)==1 && i-r==1 && i==3 && strcmp(board[r][c],opponent_piece)!=0 && strcmp(board[r][c],friendly_piece)!=0){
            possible_en_passant=1;
        }
        if(possible_en_passant){
            if(strcmp(board[r+1][c],"\u265F")==0 &&){ //history move of this black pawn*********
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
            printf("Invalid move");
        }
    }
    else{//black Pawn
        if(i==1 && strcmp(board[i][j],"\u265F")==0){
            firstMove = 1;
        }
        if(firstMove == 1 && r-i == 2 && j==c){
            if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".")){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(strcmp(board[r][c], opponent_piece) == 0 || strcmp(board[r][c], friendly_piece) == 0){
                invalid_move=1;
                printf("Invalid move");
            }
        }
        else if(r-i==1 && j==c){
            if(strcmp(board[r][c], "-") == 0){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], ".", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(strcmp(board[r][c], ".") == 0){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], "-", 2);
                moved[r][c] = 1;
                moved[i][j] = 0;
            }
            else if(strcmp(board[r][c], opponent_piece) == 0 || strcmp(board[r][c], friendly_piece) == 0){
                invalid_move=1;
                printf("Invalid move");
            }
        }
        else if(r-i == 1 && c-j == 1 && strcmp(board[r][c], opponent_piece) == 0 || r-i == 1 && j-c == 1 && strcmp(board[r][c], opponent_piece) == 0){
            if(isWhite(opponent_piece)){
                memcpy(killed_arrW[counterW], board[r][c], 4);
                counterW++
            }
            else{
                memcpy(killed_arrB[counterB], board[r][c], 4);
                counterB++
            }
            memcpy(board[r][c], board[i][j], 4);
            moved[r][c] = 1;
            moved[i][j] = 0;
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
        else if(strcmp(board[i][j],"\u265F")==0 && abs(c-j)==1 && r-i==1 && i==4 && strcmp(board[r][c],opponent_piece)!=0 && strcmp(board[r][c],friendly_piece)!=0){
            possible_en_passant=1;
        }
        if(possible_en_passant){
            if(strcmp(board[r-1][c],"\u2659")==0 &&){ //history move of this white pawn*********
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
            printf("Invalid move");
        }
    }
}

void bishop(int i, int j, int r, int c){
    int k = i; int p = j; int emptyPath=0;int invalid_move=0;
    if(abs(r - i) == abs(c - j)){
        if(i>r && j>c){
            while(k>r && p>c){
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
                if(strcmp(board[k][p], ".") == 0 || strcmp(board[k][p], "-") == 0){
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
            if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".") == 0){
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
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
            }  else  if(strcmp(board[r][c], opponent_piece) == 0){
                    if(isWhite(opponent_piece)){
                        memcpy(killed_arrW[counterW], board[r][c], 4);
                        counterW++
                    }
                    else{
                        memcpy(killed_arrB[counterB], board[r][c], 4);
                        counterB++
                    }
                    memcpy(board[r][c], board[i][j], 4);
                    moved[r][c] = 1;
                    moved[i][j] = 0;
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

        }  else if(strcmp(board[r][c], friendly_piece) == 0){ 
            invalid_move=1;   
            printf("Cannot eat a friendly piece");
        }
      }
      else{
        invalid_move=1;
         printf("Invalid move");
      }
    }else{ 
        invalid_move=1;
        printf("Invalid move");
    }
}

void rook(int i, int j, int r, int c){
    int k = i; int p = j; int emptyPath=0;int invalid_move=0;
    if((r == i && (c > j || c < j)) || (c == j && (r > i || r < i))){
        if(r==i){
          if(j>c){
            while(p>c){
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
                if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
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
            if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".") == 0){
                memcpy(board[r][c], board[i][j], 4);
                moved[r][c] = 1;
                moved[i][j] = 0;
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
            else  if(strcmp(board[r][c], opponent_piece) == 0){
                    if(isWhite(opponent_piece)){
                        memcpy(killed_arrW[counterW], board[r][c], 4);
                        counterW++
                    }
                    else{
                        memcpy(killed_arrB[counterB], board[r][c], 4);
                        counterB++
                    }
                    moved[r][c] = 1;
                    moved[i][j] = 0;
                    memcpy(board[r][c], board[i][j], 4);
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
          else if(strcmp(board[r][c], friendly_piece) == 0){
            invalid_move=1;   
            printf("Cannot eat a friendly piece");
        }
    }
      else{
        invalid_move=1;
        printf("Invalid move");
      }
    }else{
        invalid_move=1;
        printf("Invalid move");
    }
}

void king(int i, int j, int r, int c){
    int invalid_move=0;
    if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".") == 0){
        if((r == i && c == j + 1) || (r == i && c == j - 1) || (r == i + 1 && c == j) || (r == i - 1 && c == j) || (r == i + 1 && c == j + 1) || (r == i + 1 && c == j - 1) || (r == i - 1 && c == j - 1) || (r == i - 1 && c == j + 1)){
            moved[r][c] = 1;
            moved[i][j] = 0;
            memcpy(board[r][c], board[i][j], 4);
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
         }  else{
            invalid_move=1;
            printf("Invalid move");
         }
    }
     else  if(strcmp(board[r][c], opponent_piece) == 0){
                if(strcmp(opponent_piece, "\u2654") != 0 || strcmp(opponent_piece, "\u265A") != 0){
                        if(isWhite(opponent_piece)){
                            memcpy(killed_arrW[counterW], board[r][c], 4);
                            counterW++
                        }
                        else{
                            memcpy(killed_arrB[counterB], board[r][c], 4);
                            counterB++
                        }
                        moved[r][c] = 1;
                        moved[i][j] = 0;
                        memcpy(board[r][c], board[i][j], 4);
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
                    }else{
                        invalid_move=1;
                        printf("Invalid move");
                    }

     }  else if(strcmp(board[r][c], friendly_piece) == 0){
        invalid_move=1;
        printf("Cannot eat a friendly piece");
     }
}

void castling(int i, int j, int r, int c){
   if(strcmp(board[i][j], whiteKing) == 0){
    if(haveMovedAt(7,4) == 0){
        if(r == 7 && c == 6 && strcmp(board[7][7], whiteRock) == 0 && haveMovedAt(7,7) == 0 && strcmp(board[7][5], "-") == 0 
        && strcmp(board[7][6], ".") == 0 && isSquareAttacked(7,4) == 0 && isSquareAttacked(7,5) == 0 && isSquareAttacked(7,6) == 0){
            strcpy(board[7][6], whiteKing);
            strcpy(board[7][5], whiteRock);
            strcpy(board[7][4], ".");
            strcpy(board[7][7], "-");
            moved[7][6] = 1;
            moved[7][5] = 1;
            moved[7][4] = 0;
            moved[7][7] = 0;
        }
        if(r == 7 && c == 2 && strcmp(board[7][0], whiteRock) == 0 && haveMovedAt(7,0) == 0 && strcmp(board[7][3], "-") == 0 && strcmp(board[7][2], ".") == 0 
        && strcmp(board[7][1], "-") == 0 && isSquareAttacked(7,4) == 0 && isSquareAttacked(7,3) == 0 && isSquareAttacked(7,2) == 0){
            strcpy(board[7][2], whiteKing);
            strcpy(board[7][3], whiteRock);
            strcpy(board[7][4], ".");
            strcpy(board[7][0], ".");
            moved[7][2] = 1;
            moved[7][3] = 1;
            moved[7][4] = 0;
            moved[7][0] = 0;
        }
    }
}
    if(strcmp(board[i][j], blackKing) == 0){
        if(haveMovedAt(0,4) == 0){
            if(r == 0 && c == 6 && strcmp(board[0][7], blackRock) == 0 && haveMovedAt(0,7) == 0 && strcmp(board[0][5], ".") == 0 && strcmp(board[0][6], "-") == 0 
            && isSquareAttacked(0,4) == 0 && isSquareAttacked(0,5) == 0 && isSquareAttacked(0,6) == 0){
                strcpy(board[0][6], blackKing);
                strcpy(board[0][5], blackRock);
                strcpy(board[0][4], "-");
                strcpy(board[0][7], ".");
                moved[0][6] = 1;
                moved[0][5] = 1;
                moved[0][4] = 0;
                moved[0][7] = 0;
            }
            if(r == 0 && c == 2 && strcmp(board[0][0], blackRock) == 0 && haveMovedAt(0,0) == 0 && strcmp(board[0][3], ".") == 0 && strcmp(board[0][2], "-") == 0 
            && strcmp(board[0][1], ".") == 0 && isSquareAttacked(0,4) == 0 && isSquareAttacked(0,3) == 0 && isSquareAttacked(0,2) == 0){
                strcpy(board[0][2], blackKing);
                strcpy(board[0][3], blackRock);
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
int haveMovedAt(int r, int c){
    return moved[r][c];
}
int kingInCheck(char current_king_piece[4]) {
    int i, j;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            if(strcmp(board[i][j], current_king_piece) == 0) {
                return isSquareAttacked(i, j);
            }
        }
    }
    return 0;
}
int isSquareAttacked(int r, int c){
    int i, j;
    // checking knight attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(strcmp(board[i][j], opponent_piece) == 0){
                if((abs(r - i) == 1 && abs(c - j) == 2) || (abs(r - i) == 2 && abs(c - j) == 1)){
                    return 1;
                }
            }
        }
    }
    // checking king attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(strcmp(board[i][j], opponent_piece) == 0){
                if(abs(r - i) <= 1 && abs(c - j) <= 1){
                    return 1;
                }
            }
        }
    }
    // checking pawn attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(strcmp(board[i][j], opponent_piece) == 0){
                if((r - i == 1 && abs(c - j) == 1) || (r - i == -1 && abs(c - j) == 1)){
                    return 1;
                }
            }
        }
    }
    // checking rock & queen attacks
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(strcmp(board[i][j], opponent_piece) == 0){
                if(i == r){
                    int clear = 1;
                    int step = (j < c) ? 1 : -1;
                    for(int k = j + step; k != c; k += step){
                        if(strcmp(board[i][k], ".") != 0 && strcmp(board[i][k], "-") != 0){
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
                        if(strcmp(board[k][j], ".") != 0 && strcmp(board[k][j], "-") != 0){
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
            if(strcmp(board[i][j], opponent_piece) == 0){
                if(abs(r - i) == abs(c - j)){
                    int clear = 1;
                    int dr = (r > i) ? 1 : -1;
                    int dc = (c > j) ? 1 : -1;
                    int x = i + dr;
                    int y = j + dc;
                    while(x != r && y != c){
                        if(strcmp(board[x][y], ".") != 0 && strcmp(board[x][y], "-") != 0){
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

int must_promote(int i, int j, int r, int c){
    if(strcmp(board[i][j],"\u265F")==0 && i==6 && r-i==1 && c==j && strcmp(board[r][c],opponent_piece)!=0 && strcmp(board[r][c],friendly_piece)!=0){
        return 1;
    }
    else if(strcmp(board[i][j],"\u265F")==0 && r-i=1 && abs(c-j)==1 && strcmp(board[r][c],opponent_piece)==0){
        return 1;
    }
    if(strcmp(board[i][j],"\u2659")==0 && i==1 && i-r==1 && c==j && strcmp(board[r][c],opponent_piece)!=0 && strcmp(board[r][c],friendly_piece)!=0){
        return 1;
    }
    else if(strcmp(board[i][j],"\u2659")==0 && i-r=1 && abs(c-j)==1 && strcmp(board[r][c],opponent_piece)==0){
        return 1;
    }
    else{
        return 0;
    }
}
void promotion(int i, int j, int r, int c, char promotion_piece[4]){
    int possible_promotion=0;
    invalid_move=0;
    if(strcmp(board[i][j],"\u265F")==0 && i==6 && r-i==1 && c==j && strcmp(board[r][c],opponent_piece)!=0 && strcmp(board[r][c],friendly_piece)!=0){
        possible_promotion=1;
    }
    if(possible_promotion){
        for(int i=0; i<counterB ; i++){
            int found=0;
            if(str(promotion_piece,killed_arrB[i])==0 && strcmp(promotion_piece,"\u265F")!=0){
                found=1;
                break;
            }
        }
        if(found){
            memcpy(board[r][c],promotion_piece,4);
            counterB--;
            memcpy(killed_arrB[counterB], "\u265F", 4);
            counterB++;
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
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
    else if(strcmp(board[i][j],"\u265F")==0 && r-i=1 && abs(c-j)==1 && strcmp(board[r][c],opponent_piece)==0){
        possible_promotion=1;
    }
    if(possible_promotion){
        for(int i=0; i<counterB ; i++){
            int found=0;
            if(strcmp(promotion_piece,killed_arrB[i])==0 && strcmp(promotion_piece,"\u265F")!=0){
                found=1;
                break;
            }
        }
        if(found){
            memcpy(board[r][c],promotion_piece,4);
            counterB--;
            memcpy(killed_arrB[counterB], "\u265F", 4);
            counterB++;
            memcpy(killed_arrW[counterW], opponent_piece, 4);
            counterW++;
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
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
    else{
        invalid_move=1;
        printf("Cannot promote the Black pawn");
    }
    if(strcmp(board[i][j],"\u2659")==0 && i==1 && i-r==1 && c==j && strcmp(board[r][c],opponent_piece)!=0 && strcmp(board[r][c],friendly_piece)!=0){
        possible_promotion=1;
    }
    if(possible_promotion){
        for(int i=0; i<counterW ; i++){
            int found=0;
            if(strcmp(promotion_piece,killed_arrW[i])==0 && strcmp(promotion_piece,"\u2659")!=0){
                found=1;
                break;
            }
        }
        if(found){
            memcpy(board[r][c],promotion_piece,4);
            counterW--;
            memcpy(killed_arrW[counterW], "\u2659",4);
            counterW++;
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
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
    else if(strcmp(board[i][j],"\u2659")==0 && i-r=1 && abs(c-j)==1 && strcmp(board[r][c],opponent_piece)==0){
        possible_promotion=1;
    }
    if(possible_promotion){
        for(int i=0; i<counterW ; i++){
            int found=0;
            if(strcmp(promotion_piece,killed_arrW[i])==0 && strcmp(promotion_piece,"\u2659")!=0){
                found=1;
                break;
            }
        }
        if(found){
            memcpy(board[r][c],promotion_piece,4);
            counterW--;
            memcpy(killed_arrW[counterW],"\u2659",4);
            counterW++;
            memcpy(killed_arrB[counterB],opponent_piece,4);
            counterB++;
            moved[r][c] = 1;
            moved[i][j] = 0;
        }
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
    else{
        invalid_move=1;
        printf("Cannot promote the White pawn");
    }
}


