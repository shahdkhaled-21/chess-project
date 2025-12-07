void knight(int i, int j, int r, int c){
    if(abs(r-i)==1 && abs(c-j)==2 || abs(r-i)==3 && abs(c-j)==1){
        if(board[r][c]=='-' || board[r][c]=='.'){
            char temp=board[r][c];
            board[r][c]=board[i][j];
            if(temp=='-'){
                board[i][j]='.';
            }
            else{
                board[i][j]='-';
            }
        }
    }
    else{
        printf("Not valid move");
    }
}