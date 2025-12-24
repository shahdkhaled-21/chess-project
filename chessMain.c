#include <stdio.h>
#include <string.h>
#include "board.h"
#include "moves.h"
#include "specialMoves.h"
#include "history.h"

extern char width_arr[8][2];
extern char board[8][8][4];
int moved_pawn[8][8];

int main(){
    int input, turns = 1;
    char fileName[255];
    int current_color;
    printf("===================================================\n");
    printf("                Welcome to CHESS                   \n");
    printf("===================================================\n");
    start:
    printf("Choose an option(1, 2 or 3)\n1. Start.\n2. Load a previous game.\n3. Exit.");
    scanf("%d", &input);
    switch(input){
        case 1:
                display(board, width_arr);
                while(isCheckmate(current_color) == 0 && isStalemate(current_color) == 0){
                    if(turns % 2 == 1){
                        White_Player(board);
                        turns++;
                        continue;
                    }else{
                        Black_Player(board);
                        turns++;
                        continue;
                    }
                         
                }
                break;
        case 2:
                displaySavedGames();
                printf("Enter filename (without .txt) or 0 to cancel: ");
                scanf("%255s", fileName);
                if(fileName[0] != '0'){
                if(strstr(fileName, ".txt") == NULL) {
                    strcat(fileName, ".txt");
                    }   
                }else goto start;
                loadGame(fileName);
                break;
        case 3: return 0;
        default: printf("Invalid option");
    }
    return 0;
}