#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include "moves.h"

//white pieces
char whiteKing[4]   = "\u2654";
char whiteRook[4]   = "\u2656";
char whiteBishop[4] = "\u2657";
char whiteKnight[4] = "\u2658";
char whitePawn[4]   = "\u2659";
char whiteQueen[4]  = "\u2655";
//black pieces
char blackKing[4]   = "\u265A";
char blackRook[4]   = "\u265C";
char blackBishop[4] = "\u265D";
char blackKnight[4] = "\u265E";
char blackPawn[4]   = "\u265F";
char blackQueen[4]  = "\u265B";

char black[6][4] = {"\u265D", "\u265A", "\u265C", "\u265E", "\u265F", "\u265B"};
char white[6][4] = {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659"};

char promotion_pieceW[4][4] = {"\u2656", "\u2657", "\u2658", "\u2655"};
char promotion_pieceB[4][4] = {"\u265C", "\u265D", "\u265E", "\u265B"};

int moved[8][8] = {0};

int counterW = 0;
int counterB = 0;
int invalid_move = 1;

char board[8][8][4] =   {{"\u265C","\u265E","\u265D","\u265B","\u265A","\u265D","\u265E","\u265C"},
                         {"\u265F","\u265F","\u265F","\u265F","\u265F","\u265F","\u265F","\u265F"},
                         {"-", ".", "-", ".", "-", ".", "-", "."},
                         {".", "-", ".", "-", ".", "-", ".", "-"},
                         {"-", ".", "-", ".", "-", ".", "-", "."},
                         {".", "-", ".", "-", ".", "-", ".", "-"},
                         {"\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659","\u2659"},
                         {"\u2656","\u2658","\u2657","\u2655","\u2654","\u2657","\u2658","\u2656"}};
char width_arr[8][2]      =   {"A" , "B" , "C" , "D" , "E" , "F" , "G" , "H"};
char notation[8][8][3]    =  {{"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"},
                              {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7"}, 
                              {"A6", "B6", "C6", "D6", "E6", "F6", "G7", "H6"},
                              {"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5"}, 
                              {"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4"},
                              {"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3"},
                              {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2"},
                              {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1"}};

char opponent_piece[4], friendly_piece[4];

int isWhite(char piece[4]){
    for(int i = 0; i < 6; i++){
        if(strcmp(piece, white[i]) == 0){
            return 1;
        }
    } return 0;
}

int isBlack(char piece[4]){
    for(int i = 0; i < 6; i++){
        if(strcmp(piece, black[i]) == 0){
            return 1;
        }
    } return 0;
}

void White_Player(char board[8][8][4]){
    int valid_place=0;
    int valid_piece=0;
    int valid_new=0;
    int invalid_move=1;
    char promotion_piece[4];
    char original_place[3];
    char new_place[3];
    while(valid_place==0 || valid_piece==0 || valid_new==0){
        i=0;  j=0;  r=0;  c=0;  valid_place=0;  valid_piece=0;  valid_new=0;
        scanf("%s %s",original_place,new_place);
        if(original_place[0] >= 'A' && original_place[0] <= 'H' && original_place[1] >= '1' && original_place[1] <= '8'){
            valid_place=1;
            i = 8 - (original_place[1] - '0');
            j = original_place[0] - 'A';
        }
        if(valid_place==1){
            if(isWhite(board[i][j])){
                valid_piece=1;
            }
        }
        else{
            printf("Enter a valid place\n");
            continue;
        }
        if(valid_piece==0){
            printf("Choose only any white piece\n");
            continue;
        }
        if(new_place[0] >= 'A' && new_place[0] <= 'H' && new_place[1] >= '1' && new_place[1] <= '1'){
            valid_new=1;
            r = 8 - (new_place[1] - '0');
            c = new_place[0] - 'A';
        }
        if(valid_new==0){
            printf("Enter a valid NEW place\n");
            continue;
        }
    }
    while(invalid_move==1){
        invalid_move=1;
        if(strcmp(board[i][j],"\u2654")==0){
            king( i, j, r, c);
            //castling and check***************
        }
        else if(strcmp(board[i][j],"\u2655")==0){
            queen( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u2656")==0){
            rook( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u2657")==0){
            bishop( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u2658")==0){
            knight( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u2659")==0){
            if(must_promote( i, j, r, c)==0){
                pawn( i, j, r, c);
                if(invalid_move==1){
                    continue;
                }
                break;
            }
            else if(must_promote( i, j, r, c)==1){
                scanf("%s",promotion_piece);
                if(strcmp(promotion_piece,promotion_pieceB[0])==0){
                    promotion( i, j, r, c, promotion_pieceB[0]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
                if(strcmp(promotion_piece,promotion_pieceB[1])==0){
                    promotion( i, j, r, c, promotion_pieceB[1]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
                if(strcmp(promotion_piece,promotion_pieceB[2])==0){
                    promotion( i, j, r, c, promotion_pieceB[2]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
                if(strcmp(promotion_piece,promotion_pieceB[3])==0){
                    promotion( i, j, r, c, promotion_pieceB[3]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
            }
        }
    } 
}

void Black_Player(char board[8][8][4]){
    int valid_place=0;
    int valid_piece=0;
    int valid_new=0;
    int invalid_move=1;
    char promotion_piece[4];
    char original_place[3];
    char new_place[3];
    while(valid_place==0 || valid_piece==0 || valid_new==0){
        i=0;  j=0;  r=0;  c=0;  valid_place=0;  valid_piece=0;  valid_new=0;
        scanf("%s %s",original_place,new_place);
        if(original_place[0] >= 'A' && original_place[0] <= 'H' && original_place[1] >= '1' && original_place[1] <= '8'){
            valid_place=1;
            i = 8 - (original_place[1] - '0');
            j = original_place[0] - 'A';
        }
        if(valid_place==1){
            if(isWhite(board[i][j])){
                valid_piece=1;
            }
        }
        else{
            printf("Enter a valid place\n");
            continue;
        }
        if(valid_piece==0){
            printf("Choose only any black piece\n");
            continue;
        }
        if(new_place[0] >= 'A' && new_place[0] <= 'H' && new_place[1] >= '1' && new_place[1] <= '1'){
            valid_new=1;
            r = 8 - (new_place[1] - '0');
            c = new_place[0] - 'A';
        }
        if(valid_new==0){
            printf("Enter a valid NEW place\n");
            continue;
        }
    }
    while(invalid_move==1){
        invalid_move=1;
        if(strcmp(board[i][j],"\u265A")==0){
            king( i, j, r, c);
            //castling and check***************
        }
        else if(strcmp(board[i][j],"\u265B")==0){
            queen( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u265C")==0){
            rook( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u265D")==0){
            bishop( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u265E")==0){
            knight( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            break;
        }
        else if(strcmp(board[i][j],"\u265F")==0){
            if(must_promote( i, j, r, c)==0){
                pawn( i, j, r, c);
                if(invalid_move==1){
                    continue;
                }
                break;
            }
            else if(must_promote( i, j, r, c)==1){
                scanf("%s",promotion_piece);
                if(strcmp(promotion_piece,promotion_pieceB[0])==0){
                    promotion( i, j, r, c, promotion_pieceB[0]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
                if(strcmp(promotion_piece,promotion_pieceB[1])==0){
                    promotion( i, j, r, c, promotion_pieceB[1]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
                if(strcmp(promotion_piece,promotion_pieceB[2])==0){
                    promotion( i, j, r, c, promotion_pieceB[2]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
                if(strcmp(promotion_piece,promotion_pieceB[3])==0){
                    promotion( i, j, r, c, promotion_pieceB[3]);
                    if(invalid_move==1){
                        continue;
                    }
                    break;
                }
            }
        }
    } 
}

char display(char board[8][8][4],char width_arr[8][2]){
    for(int k=0 ; k<8 ; k++){
        printf("      %s ",width_arr[k]);
    }
    printf("\n\n");
    for(int i = 0; i < 8; i++){
        printf("%d  ",8-i);
        printf("%s", killed_arrW[i]);
        for(int j = 0; j <8; j++){
            printf("    %s   ",board[i][j]);
        }
        printf("  %d ",8-i);
        printf("%s", killed_arrB[i]);
        printf("\n\n");
    }
    for(int k=0 ; k<8 ; k++){
        printf("      %s ",width_arr[k]);
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL,"UTF-8");
    display(board , width_arr);
    printf("\n");
    White_Player(board);
    Black_Player(board);
    return 0;
}


