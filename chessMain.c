#include <stdio.h>
#include <string.h>
#include "board.h"
#include "moves.h"
#include "specialMoves.h"

extern char width_arr[8][2];
extern char board[8][8][4];
int moved_pawn[8][8];

int main(){
    display(board , width_arr);
    printf("\n");
    while(1){
        for(int i=0 ; i<8 ; i++){
            for(int j=0 ; j<8 ; j++){
                if(moved_pawn[i][j] != 0){
                    moved_pawn[i][j] = 0;
                }
            }
        }
        White_Player(board);
        printf("\n");
        display(board, width_arr);
        printf("\n");
        Black_Player(board);
        printf("\n");
        display(board, width_arr);
        printf("\n");
    } 
    return 0;
}