#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char board[8][8][4];
extern int counter;
extern char killed_arr[32][4];
extern char opponent_piece[4], friendly_piece[4];
extern char whiteKing[4];
extern char whiteRock[4];
extern char blackKing[4];
extern char blackRock[4];
void knight(int i, int j, int r, int c){
    if(abs(r-i)==1 && abs(c-j)==2 || abs(r-i)==3 && abs(c-j)==1){
        if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".") == 0){
            char temp[4];
            memcpy(temp, board[r][c], 4);
            memcpy(board[r][c], board[i][j], 4);
            if(strcmp(temp, "-") == 0){
                memcpy(board[i][j], ".", 2);
            }
            else{
                memcpy(board[i][j], "-", 2);
            }
        }
        else if(strcmp(board[r][c], opponent_piece) == 0){
                memcpy(killed_arr[counter], board[r][c], 4);
                counter++;
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
            printf("Cannot eat a friendly piece");
        }
    }
    else{
        printf("Invalid move");
    }
}
void queen(int i, int j, int r, int c){
    int k=i;int p=j;int emptyPath;
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
        if(emptyPath == 1){
            if(strcmp(board[r][c], "-") == 0 && abs(r-i) == abs(c-j) || strcmp(board[r][c], ".") == 0 && abs(r-i) == abs(c-j)){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
            }
            else if(strcmp(board[r][c], "-") == 0 && i==r && r&1==1 || strcmp(board[r][c], "-") == 0  && j==c && c&1 == 1){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], ".", 2);
            }
            else if(strcmp(board[r][c], "-") == 0 && i==r && r&1==0 || strcmp(board[r][c], "-") == 0 && j == c && c&1 == 0){
                 memcpy(board[r][c], board[i][j], 4);
                 memcpy(board[i][j], "-", 2);
            }
            else if(strcmp(board[r][c], ".") == 0 && i == r && r&1 == 0 || strcmp(board[r][c], ".") == 0 && j == c && c&1 == 0){
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], ".", 2);
            }
            else if(strcmp(board[r][c], ".") == 0 && i == r && r&1 == 1 || strcmp(board[r][c], ".") == 0 && j == c && c&1 == 1){
                 memcpy(board[r][c], board[i][j], 4);
                 memcpy(board[i][j], "-", 2);
            }
            else if(strcmp(board[r][c], opponent_piece) == 0){
                memcpy(killed_arr[counter], board[r][c], 4);
                counter++;
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], board[r-1][c], 4);
            }
            else if(strcmp(board[r][c], friendly_piece) == 0){
                printf("Cannot eat friendly piece");
            }
        }
        else{
            printf("Invalid move");
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
        if(strcmp(board[r][c], ".") == 0 || strcmp(board[r][c], "-") == 0){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
        }
        else if(strcmp(board[r][c], opponent_piece) == 0){
                 memcpy(killed_arr[counter], board[r][c], 4);
                 counter++;
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
            printf("Cannot eat friendly piece");
        }
    }
    else{
        printf("Invalid move");
    }
}
void pawn(int i, int j, int r, int c){
    int firstMove=0;
    if(strcmp(board[i][j], board[1][j]) == 0 || strcmp(board[i][j], board[6][j]) == 0){
        firstMove = 1;
    }
    if(firstMove == 1 && r-i == 2){
        if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".")){
                char temp[4];
                memcpy(temp, board[r][c], 4);
                memcpy(board[r][c], board[i][j], 4);
                memcpy(board[i][j], temp, 4);
        }
        else if(strcmp(board[r][c], opponent_piece) == 0 || strcmp(board[r][c], friendly_piece) == 0){
            printf("Invalid move");
        }
    }
    else if(r-i==1){
        if(strcmp(board[r][c], "-") == 0){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], ".", 2);
        }
        else if(strcmp(board[r][c], ".") == 0){
            memcpy(board[r][c], board[i][j], 4);
            memcpy(board[i][j], "-", 2);
        }
        else if(strcmp(board[r][c], opponent_piece) == 0 || strcmp(board[r][c], friendly_piece) == 0){
            printf("Invalid move");
        }
    }
    else if(r-i == 1 && c-j == 1 && strcmp(board[r][c], opponent_piece) == 0 || r-i == -1 && c-j == 1 && strcmp(board[r][c], opponent_piece) == 0){
                memcpy(killed_arr[counter], board[r][c], 4);
                counter++;
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
    else{
        printf("Invalid move");
    }
}
void bishop(int i, int j, int r, int c){
    int k = i; int p = j; int emptyPath;
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
                        memcpy(killed_arr[counter], board[r][c], 4);
                        counter++;
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

        }  else if(strcmp(board[r][c], friendly_piece) == 0)   printf("Cannot eat a friendly piece");
      }else printf("Invalid move");
    }else printf("Invalid move");
 }
void rock(int i, int j, int r, int c){
    int k = i; int p = j; int emptyPath;
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
                        memcpy(killed_arr[counter], board[r][c], 4);
                        counter++;
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

        }  else if(strcmp(board[r][c], friendly_piece) == 0)   printf("Cannot eat a friendly piece");
      }else printf("Invalid move");
    }else printf("Invalid move");
}
void king(int i, int j, int r, int c){
    if(strcmp(board[r][c], "-") == 0 || strcmp(board[r][c], ".") == 0){

        if((r == i && c == j + 1) || (r == i && c == j - 1) || (r == i + 1 && c == j) || (r == i - 1 && c == j) || (r == i + 1 && c == j + 1) || (r == i + 1 && c == j - 1) || (r == i - 1 && c == j - 1) || (r == i - 1 && c == j + 1)){

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
         }  else printf("Invalid move");
    }
     else  if(strcmp(board[r][c], opponent_piece) == 0){
                if(strcmp(opponent_piece, "\u2654") != 0 || strcmp(opponent_piece, "\u265A") != 0){
                        memcpy(killed_arr[counter], board[r][c], 4);
                        counter++;
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
                    }else printf("Invalid move");

     }  else    if(strcmp(board[r][c], friendly_piece) == 0)   printf("Cannot eat a friendly piece");
}
void castling(int i, int j, int r, int c){
   if(strcmp(board[i][j], whiteKing) == 0){
        if(haveMoved(whiteKing) == 0 && haveMoved(whiteRock) == 0 && isSquareAttacked(7, 4) == 0){
            if(strcmp(board[7][5], "-") == 0 && strcmp(board[7][6], ".") == 0){
                if(r == 7 && c == 6 && isSquareAttacked(7, 6) == 0 && isSquareAttacked(7, 5) == 0){
                    strcpy(board[7][6], whiteKing);
                    strcpy(board[7][5], whiteRock);
                    strcpy(board[7][4], ".");
                    strcpy(board[7][7], "-");
                }
            }
            if(strcmp(board[7][3], "-") == 0 && strcmp(board[7][2], ".") == 0 && strcmp(board[7][1], "-") == 0 ){
                if(r == 7 && c == 2 && isSquareAttacked(7, 2) == 0 && isSquareAttacked(7, 3) == 0){
                    strcpy(board[7][2], whiteKing);
                    strcpy(board[7][3], whiteRock);
                    strcpy(board[7][4], ".");
                    strcpy(board[7][0], ".");
                }
            }
        }
   }
   if(strcmp(board[i][j], blackKing) == 0){
        if(haveMoved(blackKing) == 0 && haveMoved(blackRock) == 0 && isSquareAttacked(0, 4) == 0){
            if(strcmp(board[0][5], ".") == 0 && strcmp(board[0][6], "-") == 0){
                if(r == 0 && c == 6 && isSquareAttacked(0, 6) == 0 && isSquareAttacked(0, 5) == 0){
                    strcpy(board[0][6], blackKing);
                    strcpy(board[0][5], blackRock);
                    strcpy(board[0][4], "-");
                    strcpy(board[0][7], ".");
                }
            }
            if(strcmp(board[0][3], ".") == 0 && strcmp(board[0][2], "-") == 0 && strcmp(board[0][1], ".") == 0 ){
                if(r == 0 && c == 2 && isSquareAttacked(0, 2) == 0 && isSquareAttacked(0, 3) == 0){
                    strcpy(board[0][2], blackKing);
                    strcpy(board[0][3], blackRock);
                    strcpy(board[0][4], "-");
                    strcpy(board[0][0], "-");
                }
            }
        }
   }
}
int haveMoved(char piece[4]){

}
int kingInCheck() {
    
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
void promotion(int i, int j, int r, int c, char underpromotion_piece[4]){
    int possible_promotion=0;
    if(strcmp(board[i][j],blackPawn)==0 && i==6 && r-i==1 && c==j){
        possible_promotion=1;
    }
    if(possible_promotion){
        for(int i=0; i<counter ; i++){
            int found=0;
            if(underpromotion_piece[3]==killed_arr[i][3] && strcmp(underpromotion_piece,blackPawn)!=0){
                found=1;
            }
        }
        if(found){
            memcpy(board[r][c],underpromotion_piece,4);
        }
    }
    else{
        printf("Cannot promote the Black pawn");
    }
    if(strcmp(board[i][j],whitePawn)==0 && i==1 && r-i==1 && c==j){
        possible_promotion=1;
    }
    if(possible_promotion){
        for(int i=0; i<counter ; i++){
            int found=0;
            if(underpromotion_piece[3]==killed_arr[i][3] && !strcmp(underpromotion_piece,whitePawn)!=0){
                found=1;
            }
        }
        if(found){
            memcpy(board[r][c],underpromotion_piece,4);
        }
    }
    else{
        printf("Cannot promote the White pawn");
    }
}
