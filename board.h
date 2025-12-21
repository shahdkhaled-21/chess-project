#ifndef BOARD_H
#define BOARD_H
typedef struct{
    char original_place[3];
    char new_place[3];
    char moved_piece[4];
    char captured_piece[4];
}History;

char display(char board[8][8][4],char width_arr[8][2]);
void Black_Player(char board[8][8][4]);
void White_Player(char board[8][8][4]);
int piece_colour(char piece[4]);
int isBlack(char piece[4]);
int isWhite(char piece[4]);
void initialize_history(History history);
void Add_to_history(History history);
void undo();
void redo();
#endif