#include <stdio.h>
#include <string.h>
#include "board.h"
#include "moves.h"
#include "specialMoves.h"
#include "history.h"

extern char width_arr[8][2];
extern char board[8][8][4];
extern int historyPosition;
int moved_pawnW[8];
int moved_pawnB[8];

int main() {
    historyInitialization();
    int input, turns = 1;
    char fileName[255];
    int running = 1;
    int return_to_menu = 0;
    int colour;
    printf("===================================================\n");
    printf("           ♔ WELCOME TO CHESS ♚                   \n");
    printf("===================================================\n\n");
    while(running) {
        printf("===========================================\n");
        printf("              MAIN MENU                    \n");
        printf("===========================================\n\n");
        printf("Choose an option:\n1. Start new game\n2. Load saved game\n3. Exit\n");
        printf("\nEnter your choice (1-3): ");
        if(scanf("%d", &input) != 1) {
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while(getchar() != '\n');
        switch(input) {
            case 1:
                printf("\n===========================================\n");
                printf("          STARTING NEW GAME                 \n");
                printf("===========================================\n");
                resetGame();
                turns = 1;
                display(board, width_arr);
                return_to_menu = 0;
                while(return_to_menu == 0) {
                    colour = (turns % 2 == 1) ? 1 : 0;
                    if(isCheckmate(colour) == 1) {
                        printf("\n===========================================\n");
                        printf("              CHECKMATE!                   \n");
                        printf("===========================================\n");
                        if(colour == 1) {
                            printf("              BLACK WINS!                  \n");
                        } else {
                            printf("              WHITE WINS!                  \n");
                        }
                        printf("===========================================\n");
                        break;
                    }
                    if(isStalemate(colour) == 1) {
                        printf("\n===========================================\n");
                        printf("              STALEMATE!                   \n");
                        printf("===========================================\n");
                        printf("              IT'S A DRAW!                 \n");
                        printf("===========================================\n");
                        break;
                    }
                    return_to_menu = player(board, turns);
                    if(return_to_menu == 0) {
                        display(board, width_arr);
                        turns++;
                        if(turns % 2 == 1) {
                            memset(moved_pawnB, 0, sizeof(moved_pawnB));
                        } else {
                            memset(moved_pawnW, 0, sizeof(moved_pawnW));
                        }
                    }
                }
                break;
            case 2:
                displaySavedGames();
                getFilename(fileName);
                if(fileName[0] == '0') {
                    printf("Load cancelled.\n");
                    continue;
                }
                if(loadGame(fileName)) {
                    turns = historyPosition + 1;
                    display(board, width_arr);
                    return_to_menu = 0;
                    while(return_to_menu == 0) {
                        colour = (turns % 2 == 1) ? 1 : 0;
                        if(isCheckmate(colour) == 1) {
                            printf("\n===========================================\n");
                            printf("              CHECKMATE!                   \n");
                            printf("===========================================\n");
                            if(colour == 1) {
                                printf("              BLACK WINS!                  \n");
                            } else {
                                printf("              WHITE WINS!                  \n");
                            }
                            printf("===========================================\n");
                            break;
                        }
                        if(isStalemate(colour) == 1) {
                            printf("\n===========================================\n");
                            printf("              STALEMATE!                   \n");
                            printf("===========================================\n");
                            printf("              IT'S A DRAW!                 \n");
                            printf("===========================================\n");
                            break;
                        }
                        if(turns % 2 == 0) {
                            memset(moved_pawnW, 0, sizeof(moved_pawnW));
                        } else {
                            memset(moved_pawnB, 0, sizeof(moved_pawnB));
                        }
                        return_to_menu = player(board, turns);
                        if(return_to_menu == 0) {
                            display(board, width_arr);
                            turns++;
                        }
                    }
                } else {
                    printf("Failed to load game.\n");
                }
                break;
            case 3:
                printf("===========================================\n");
                printf("      Thank you for playing CHESS!         \n");
                printf("               Goodbye!                    \n");
                printf("===========================================\n");
                return 0;
            default:
                printf("Invalid option! Please choose 1, 2, or 3.\n");
                break;
        }
    }
    return 0;
}