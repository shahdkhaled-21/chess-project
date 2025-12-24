#ifndef BOARD_H
#define BOARD_H
char display(char board[8][8][4],char width_arr[8][2]);

void Black_Player(char board[8][8][4]);

void White_Player(char board[8][8][4]);

void moveFromCoords(char from[3], char to[3]);
#endif