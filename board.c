#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moves.h"
#include "specialMoves.h"
#include "history.h"

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

char promotion_piece_letters[4] = {'Q','K','B','R'};

int moved[8][8] = {0};

char killed_arrW[15][4];
char killed_arrB[15][4];

int i, j, r, c;
int counterW = 0;
int counterB = 0;
int invalid_move;
int colour;
int enPassantDone;
int checking_checkmate = 0;
int checking_stalemate = 0;

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

extern History history[6000];
extern int historyCount;

void player(char board[8][8][4],int turns){
    int valid_place=0;  int colour = (turns % 2);
    int valid_piece=0;  char(*promotion_pieces)[4] = (colour == 1)? promotion_pieceW : promotion_pieceB;
    int valid_new=0;    int option;    char filename[255];   int history_added = 0;
    char promotion_letter;
    char input[10];
    char original_place[3];
    char new_place[3];
    while(valid_place==0 || valid_piece==0 || valid_new==0 || invalid_move == 1){
        valid_place = 0;  valid_piece = 0;  valid_new = 0;  invalid_move = 0;
        printf("Enter your move(e.g A1 B2):");
        if(fgets(input, sizeof(input), stdin) != NULL){
            sscanf(input ,"%2s %2s",original_place,new_place);
        }
        if(original_place[0] >= 'A' && original_place[0] <= 'H' && original_place[1] >= '1' && original_place[1] <= '8'){
            valid_place=1;
            i = 8 - (original_place[1] - '0');
            j = original_place[0] - 'A';
        }
        else{
            valid_place = 0;
            printf("Enter a valid place\n");
            continue;
        }
        if(valid_place==1){
            if((colour == 1 && isWhite(board[i][j])) ||( colour == 0 && (isBlack(board[i][j])))){
                valid_piece=1;
            }
            else{
                valid_piece = 0;
                printf("Choose only a piece of your colour\n");
                continue;
            }
        }
        if(new_place[0] >= 'A' && new_place[0] <= 'H' && new_place[1] >= '1' && new_place[1] <= '8'){
            valid_new=1;
            r = 8 - (new_place[1] - '0');
            c = new_place[0] - 'A';
        }
        else{
            valid_new = 0;
            printf("Enter a valid NEW place\n");
            continue;
        }
        if((u8) board[i][j][2] == WhiteKing || (u8) board[i][j][2] == BlackKing){
            if(i - r == 0 && abs(j - c) == 2) {
                castling(i, j, r, c);
                addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
                markCastling(i, j, r, c);// not sure***************
                history_added = 1;
            }
            else {king( i, j, r, c, colour);}
            if(invalid_move==1){
                continue;
            }     
        }
        else if((u8) board[i][j][2] == WhiteQueen || (u8) board[i][j][2] == BlackQueen){
            queen( i, j, r, c, colour);
            if(invalid_move==1){
                continue;
            }
        }
        else if((u8) board[i][j][2] == WhiteRook || (u8) board[i][j][2] == BlackRook){
            rook( i, j, r, c, colour);
            if(invalid_move==1){
                continue;
            }
        }
        else if((u8) board[i][j][2] == WhiteBishop || (u8) board[i][j][2] == BlackBishop){
            bishop( i, j, r, c, colour);
            if(invalid_move==1){
                continue;
            }
        }
        else if((u8) board[i][j][2] == WhiteKnight || (u8) board[i][j][2] == BlackKnight){
            knight( i, j, r, c, colour);
            if(invalid_move==1){
                continue;
            }
        }
        else if((u8) board[i][j][2] == WhitePawn && must_promote(i, j, r, c)==0){
            white_pawn( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            if(enPassantDone == 1){
                addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
                markEnPassant(c);
                history_added = 1;
            } 
        }
        else if((u8) board[i][j][2] == BlackPawn && must_promote(i, j, r, c)==0){
            black_pawn( i, j, r, c);
            if(invalid_move==1){
                continue;
            }
            if(enPassantDone == 1) {
                addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
                markEnPassant(c);
                history_added = 1;
            }
        }
        else if(((u8) board[i][j][2] == WhitePawn || (u8) board[i][j][2] == BlackPawn) && must_promote( i, j, r, c)==1){
            printf("Enter the promotion piece (R, B, K, Q):\n");
            scanf(" %c",&promotion_letter);
            if(promotion_letter == 'R'){
                promotion( i, j, r, c, promotion_pieces[0]);
                if(invalid_move==1){
                    continue;
                }
            }
            else if(promotion_letter == 'B'){
                promotion( i, j, r, c, promotion_pieces[1]);
                if(invalid_move==1){
                    continue;
                }
            }
            else if(promotion_letter == 'K'){
                promotion( i, j, r, c, promotion_pieces[2]);
                if(invalid_move==1){                        
                    continue;
                }
            }
            else if(promotion_letter == 'Q'){
                promotion( i, j, r, c, promotion_pieces[3]);
                if(invalid_move==1){
                    continue;
                }
            }
            else{
                invalid_move = 1;
                continue;
            }
            addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
            if(colour == 1){markPromotion(whitePawn);}
            else{markPromotion(blackPawn);}
            history_added = 1;
        }
        if(history_added == 0){addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);}
        history[historyCount - 1].counterW_after = counterW;
        history[historyCount - 1].counterB_after = counterB; 
    }
    printf("Enter an option(1, 2, 3 OR 4):\n 1.Save Game.\t 2.Undo.\t 3.Redo.\t 4.None\n");
    scanf("%d",&option);
    while(getchar() != '\n');
    switch (option){
        case 1:
            printf("Enter a name for your file:");
            fgets(filename, 255, stdin);
            saveGame(filename);
            break;
        case 2:
            undo();
            break;
        case 3:
            redo();
            break;
        case 4:
            return;
        default:
            printf("Invaid option,TRY AGAIN. Just choose an existing option\n");
    }   
}

char display(char board[8][8][4],char width_arr[8][2]){
    for(int k=0 ; k<8 ; k++){
        printf("       %s",width_arr[k]);
    }
    printf("\n\n");
    for(int i = 0; i < 8; i++){
        printf("%d  ",8-i);
        for(int j = 0; j <8; j++){
            printf("    %s   ",board[i][j]);
        }
        printf("    %d ",8-i);
        printf("%s\t%s", killed_arrB[i],killed_arrW[i]);
        if(killed_arrW[i][2] == WhitePawn){}
        printf("\n\n");
    }
    for(int k=0 ; k<8 ; k++){
        printf("       %s",width_arr[k]);
    }
    printf("\n");
}
