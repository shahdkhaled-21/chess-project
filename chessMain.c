#include <stdio.h>
#include <string.h>
#include "board.h"
#include "moves.h"
#include "specialMoves.h"

extern width_arr[8][2];
extern board[8][8][4];

int main(){
    display(board , width_arr);
    printf("\n");
    White_Player(board);
    Black_Player(board);
    return 0;
}