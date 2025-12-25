#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void toUpperCase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int player(char board[8][8][4], int turns){
    int valid_place = 0;
    int colour = (turns % 2);
    int valid_piece = 0;
    char(*promotion_pieces)[4] = (colour == 1) ? promotion_pieceW : promotion_pieceB;
    int valid_new = 0;
    int option;
    char filename[255];
    int history_added = 0;
    char promotion_letter;
    char input[20];
    char original_place[10];
    char new_place[10];
    int save_option;
    
    while(valid_place == 0 || valid_piece == 0 || valid_new == 0 || invalid_move == 1) {
        valid_place = 0;
        valid_piece = 0;
        valid_new = 0;
        invalid_move = 0;
        history_added = 0;
        printf("======================================\n");
        if(turns % 2 == 1) {
            printf("        WHITE'S TURN\n");
        } else {
            printf("        BLACK'S TURN\n");
        }
        printf("======================================\n\n");
        printf("Choose an action:\n1. Make a move\n2. Undo last move\n3. Redo move\n4. Save game\n5. Return to startup menu\n");
        printf("\nEnter your choice (1-5): ");
        if(scanf("%d", &option) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while(getchar() != '\n');
        switch(option) {
            case 1:
                goto start;
                
            case 2:
                undo();
                return 0;
                
            case 3:
                redo();
                return 0;
                
            case 4:
                printf("Enter a filename for your save: ");
                fgets(filename, 255, stdin);
                filename[strcspn(filename, "\n")] = 0; // Remove newline
                saveGame(filename);
                continue;
                
            case 5:
                printf("\nDo you want to save before returning to menu?\n");
                printf("1. Yes, save and return\n");
                printf("2. No, return without saving\n");
                printf("Enter your choice: ");
                if(scanf("%d", &save_option) != 1) {
                    while(getchar() != '\n');
                    printf("Invalid input!\n");
                    continue;
                }
                while(getchar() != '\n');
                if(save_option == 1) {
                    printf("Enter a filename for your save: ");
                    fgets(filename, 255, stdin);
                    filename[strcspn(filename, "\n")] = 0;
                    saveGame(filename);
                }
                return 1;
            default:
                printf("Invalid option! Please choose a number between 1 and 5.\n");
                continue;
        }
        start:
        if(turns % 2 == 1) {
            printf("\nWhite's turn - Enter your move (e.g., A2 A4 or a2 a4): ");
        } else {
            printf("\nBlack's turn - Enter your move (e.g., A7 A5 or a7 a5): ");
        }
        if(fgets(input, sizeof(input), stdin) != NULL) {
            if(sscanf(input, "%9s %9s", original_place, new_place) != 2) {
                printf("Invalid format! Please enter move as: FROM TO (e.g., A2 A4)\n");
                continue;
            }
            toUpperCase(original_place);
            toUpperCase(new_place);
        }
        if(original_place[0] >= 'A' && original_place[0] <= 'H' && 
           original_place[1] >= '1' && original_place[1] <= '8') {
            valid_place = 1;
            i = 8 - (original_place[1] - '0');
            j = original_place[0] - 'A';
        } else {
            valid_place = 0;
            printf("Invalid starting position! Use format like A2, B4, etc.\n");
            continue;
        }
        if(valid_place == 1) {
            if((colour == 1 && isWhite(board[i][j])) || 
               (colour == 0 && (isBlack(board[i][j])))) {
                valid_piece = 1;
            } else {
                valid_piece = 0;
                if(board[i][j][0] == '-' || board[i][j][0] == '.') {
                    printf("No piece at that position!\n");
                } else {
                    printf("That's not your piece! Choose a piece of your color.\n");
                }
                continue;
            }
        }
        if(new_place[0] >= 'A' && new_place[0] <= 'H' && 
           new_place[1] >= '1' && new_place[1] <= '8') {
            valid_new = 1;
            r = 8 - (new_place[1] - '0');
            c = new_place[0] - 'A';
        } else {
            valid_new = 0;
            printf("Invalid destination! Use format like A4, B6, etc.\n");
            continue;
        }
        if((u8)board[i][j][2] == WhiteKing || (u8)board[i][j][2] == BlackKing) {
            if(i - r == 0 && abs(j - c) == 2) {
                castling(i, j, r, c);
                addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
                markCastling(i, j, r, c);
                history_added = 1;
            } else {
                king(i, j, r, c, colour);
            }
            if(invalid_move == 1) {
                printf("Invalid king move!\n");
                continue;
            }
        }
        else if((u8)board[i][j][2] == WhiteQueen || (u8)board[i][j][2] == BlackQueen) {
            queen(i, j, r, c, colour);
            if(invalid_move == 1) {
                printf("Invalid queen move!\n");
                continue;
            }
        }
        else if((u8)board[i][j][2] == WhiteRook || (u8)board[i][j][2] == BlackRook) {
            rook(i, j, r, c, colour);
            if(invalid_move == 1) {
                printf("Invalid rook move!\n");
                continue;
            }
        }
        else if((u8)board[i][j][2] == WhiteBishop || (u8)board[i][j][2] == BlackBishop) {
            bishop(i, j, r, c, colour);
            if(invalid_move == 1) {
                printf("Invalid bishop move!\n");
                continue;
            }
        }
        else if((u8)board[i][j][2] == WhiteKnight || (u8)board[i][j][2] == BlackKnight) {
            knight(i, j, r, c, colour);
            if(invalid_move == 1) {
                printf("Invalid knight move!\n");
                continue;
            }
        }
        else if((u8)board[i][j][2] == WhitePawn && must_promote(i, j, r, c) == 0) {
            white_pawn(i, j, r, c);
            if(invalid_move == 1) {
                printf("Invalid pawn move!\n");
                continue;
            }
            if(enPassantDone == 1) {
                addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
                markEnPassant(c);
                history_added = 1;
            }
        }
        else if((u8)board[i][j][2] == BlackPawn && must_promote(i, j, r, c) == 0) {
            black_pawn(i, j, r, c);
            if(invalid_move == 1) {
                printf("Invalid pawn move!\n");
                continue;
            }
            if(enPassantDone == 1) {
                addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
                markEnPassant(c);
                history_added = 1;
            }
        }
        else if(((u8)board[i][j][2] == WhitePawn || (u8)board[i][j][2] == BlackPawn) && 
                must_promote(i, j, r, c) == 1) {
            printf("Pawn promotion! Enter the piece (Q=Queen, R=Rook, B=Bishop, K=Knight): ");
            scanf(" %c", &promotion_letter);
            promotion_letter = toupper(promotion_letter);
            
            if(promotion_letter == 'R') {
                promotion(i, j, r, c, promotion_pieces[0]);
            }
            else if(promotion_letter == 'B') {
                promotion(i, j, r, c, promotion_pieces[1]);
            }
            else if(promotion_letter == 'K') {
                promotion(i, j, r, c, promotion_pieces[2]);
            }
            else if(promotion_letter == 'Q') {
                promotion(i, j, r, c, promotion_pieces[3]);
            }
            else {
                printf("Invalid promotion piece!\n");
                invalid_move = 1;
                continue;
            }
            
            if(invalid_move == 1) {
                printf("Invalid promotion move!\n");
                continue;
            }
            
            addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
            if(colour == 1) {
                markPromotion(whitePawn);
            } else {
                markPromotion(blackPawn);
            }
            history_added = 1;
        }
        
        if(history_added == 0) {
            addToHistory(original_place, new_place, board[i][j], board[r][c], i, j, r, c);
        }
        history[historyCount - 1].counterW_after = counterW;
        history[historyCount - 1].counterB_after = counterB;
    }
    
    return 0;
}

char display(char board[8][8][4], char width_arr[8][2]) {
    printf("\n");
    for(int k = 0; k < 8; k++) {
        printf("       %s", width_arr[k]);
    }
    printf("         Captured by White\tCaptured by Black");
    printf("\n\n");
    
    for(int i = 0; i < 8; i++) {
        printf("%d  ", 8 - i);
        for(int j = 0; j < 8; j++) {
            printf("    %s   ", board[i][j]);
        }
        printf("    %d ", 8 - i);
        printf("        %s        \t        %s        ", killed_arrB[i], killed_arrW[i]);
        printf("\n\n");
    }
    
    for(int k = 0; k < 8; k++) {
        printf("       %s", width_arr[k]);
    }
    printf("\n\n");
}