#ifndef MOVES_H
#define MOVES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char board[8][8][4];
extern int counter;
extern char killed_arr[32][4];
extern char opponent_piece[4], friendly_piece[4];
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

     }  else    if(strcmp(board[r][c], friendly_piece) == 0)   printf("Cannot eat a friendly piece");
}
#endif