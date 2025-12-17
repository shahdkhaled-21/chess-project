#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include<locale.h>
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

char promotionPiecesW[4][12]={"whiteRook","whiteBishop","whiteKnight","whiteQueen"};
char promotionPiecesB[4][12]={"blackRook","blackBishop","blackKnight","blackQueen"};

char moves[9][10] = {"promotion","castling","en passant","pawn","king","queen","bishop","rook","knight"};

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

void which_move(char moves[9][10]){
    char move[10];
    fgets(move , 10 , stdin);
    switch(⁇⁇){//// NOT COMPLETED***********
        case(!!!){
            void king;
            break;
        }
        case(!!!){
            void rook;
            break;
        }
        case(!!!){
            void bishop;
            break;
        }
        case(!!!){
            void knight;
            break;
        }
        case(!!!){
            void pawn;
            break;
        }
        case(!!!){
            void queen;
            break;
        }
        case(!!!){
            void castling;
            break;
        }
        case(!!!){
            void promotion;
            break;
        }
        case(!!!){
            void en_passant;
            break;
        }
    }
}

void White_Player(char notation[8][8][3],char board[8][8][4]){
    int valid_place=0; int i; int j; int r; int c; char move[10];
    int valid_piece=0;
    int valid_new=0;
    char original_place[3];
    char new_place[3];
    while(valid_place==0 || valid_piece==0 || valid_new==0){
        i=0;j=0;r=0;c=0;valid_place=0;valid_piece=0;valid_new=0;
        scanf("%s %s",original_place,new_place);
        for(i=0 ; i < 8 ; i++){
            for(j=0 ; j < 8 ; j++){
                if(strcmp(notation[i][j],original_place)==0){
                    valid_place=1;
                    break;
                }
            }
            if(valid_place){
                break;
            }
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
        for(r=0 ; r < 8 ; r++){
            for(c=0 ; c < 8 ; c++){
                if(strcmp(notation[r][c],new_place)==0){
                    valid_new=1;
                    break;
                }
            }
            if(valid_new){
                break;
            }
        }
        if(valid_new==0){
            printf("Enter a valid NEW place\n");
            continue;
        }
    }
    //promotion case********* NOT COMPLETED
}

void Black_Player(char notation[8][8][3],char board[8][8][4]){
    int valid_place=0; int i; int j; int r; int c; 
    int valid_piece=0;
    int valid_new=0;
    char original_place[3];
    char new_place[3];
    while(valid_place==0 || valid_piece==0 || valid_new==0){
        i=0;j=0;r=0;c=0;valid_place=0;valid_piece=0;valid_new=0;
        scanf("%s %s",original_place,new_place);
        for(i=0 ; i < 8 ; i++){
            for(j=0 ; j < 8 ; j++){
                if(strcmp(notation[i][j],original_place)==0){
                    valid_place=1;
                    break;
                }
            }
            if(valid_place){
                break;
            }
        }
        if(valid_place==1){
            if(isBlack(board[i][j])){
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
        for(r=0 ; r < 8 ; r++){
            for(c=0 ; c < 8 ; c++){
                if(strcmp(notation[r][c],new_place)==0){
                    valid_new=1;
                    break;
                }
            }
            if(valid_new){
                break;
            }
        }
        if(valid_new==0){
            printf("Enter a valid NEW place\n");
            continue;
        }
    }
    // promotion case********** NOT COMPLETED
}

int moved[8][8] = {0};
int counter = 0;
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
char killed_arrW[15][4] = {" "};
char killed_arrW[15][4] = {" "};
char opponent_piece[4], friendly_piece[4];
char display(char board[8][8][4],char width_arr[8][2]){
    for(int k=0 ; k<8 ; k++){
        printf("      %s ",width_arr[k]);
    }
    printf("\n\n");
    for(int i = 0; i < 8; i++){
        printf("%d ",8-i);
        for(int j = 0; j <8; j++){
            printf("    %s   ",board[i][j]);
        }
        printf("  %d ",8-i);
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
    White_Player(notation,board);
    Black_Player(notation,board);
    return 0;
}


