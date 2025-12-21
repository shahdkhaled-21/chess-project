#include <stdio.h>
#include <string.h>
#include "board.h"
#include "moves.h"
#include "specialMoves.h"

extern char width_arr[8][2];
extern char board[8][8][4];

int main(){
    display(board , width_arr);
    printf("\n");
    White_Player(board);
    printf("\n");
    display(board , width_arr);
    printf("\n");
    Black_Player(board);
    printf("\n");
    display(board , width_arr);
    printf("\n");
    White_Player(board);
    printf("\n");
    display(board , width_arr);
    return 0;
}