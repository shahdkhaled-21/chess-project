#include <stdio.h>
#include <string.h>
#include "board.h"
#include "moves.h"
#include "specialMoves.h"
#include "history.h"

extern char width_arr[8][2];
extern char board[8][8][4];
int moved_pawnW[8][8];
int moved_pawnB[8][8];

int main(){
    historyInitialization();
    int input, turns = 1;
    char fileName[255];
    int maxLen = 255;
    int running = 1;
    int current_color;
    printf("===================================================\n");
    printf("                Welcome to CHESS                   \n");
    printf("===================================================\n");
    while(running){
        printf("Choose an option(1, 2 or 3)\n1. Start.\t2. Load a previous game.\t3. Exit.\n");
        scanf("%d", &input);
        while(getchar() != '\n');
        switch(input){
            case 1:
                display(board, width_arr);
                while(checking_checkmate == 0 ){
                    if(turns % 2 == 0){memset(moved_pawnW, 0, sizeof(moved_pawnW));}
                    else{memset(moved_pawnB, 0, sizeof(moved_pawnB));}
                    if(turns % 2 == 1){
                        player(board, turns);
                        display(board, width_arr);
                        turns++;
                    }
                    else{
                        player(board, turns);
                        display(board, width_arr);
                        turns++;
                    }
                }
                    break;
            case 2:
                    displaySavedGames();
                    getFilename(fileName, maxLen);
                    if(fileName[0]== '0'){
                        continue;
                    }
                    loadGame(fileName);
                    break;
            case 3: 
                    return 0;
            default: 
                    printf("Invalid option");
                    break;
        }
    }
    return 0;
}