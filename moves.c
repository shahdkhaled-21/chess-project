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
        else if(board[r][c]==opponent_piece){
            killed_arr[counter]=board[r][c];
            counter++;
            board[r][c]=board[i][j];
            board[i][j]='.';//some modifications must be applied here******************
        }
        else if(board[r][c]==friendly_piece){
            printf("Cannot eat friendly piece");
        }
    }
    else{
        printf("Invalid move");
    }
}
void queen(int i, int j, int r, int c){
    int k=i;int p=j;int emptyPath;
    if(abs(i-r)==abs(j-c)){
        if(i>r && j>c){
            while(k>r && p>c){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k--;
                p--;
            }
        }
        else if(i<r && j<c){
            while(k<r && p<c){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k++;
                p++;
            }
        }
        else if(i<r && j>c){
            while(k<r && p>c){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k++;
                p--;
            }
        }
        else if(i>r && j<c){
            while(k<r && p>c){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k--;
                p++;
            }
        }
        if(emptyPath==1){
            if(board[r][c]=='-'||board[r][c]=='.'){
                char temp=board[r][c];
                board[r][c]=board[i][j];
                board[i][j]=temp;
            }
            else if(board[r][c]==opponent_piece){
                killed_arr[counter]=board[r][c];
                counter++;
                board[r][c]=board[i][j];
                board[i][j]=board[r-1][c];
            }
            else if(board[r][c]==friendly_piece){
                printf("Cannot eat friendly piece");
            }
        }
        else{
            printf("Invalid move");
        }
    }
    else if(r==i){
        if(j>c){
            while(p>c){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                p--;
            }
        }
        else if(j<c){
            while(p<c){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                p++;
            }
        }
    }
    else if(c==j){
        if(i>r){
            while(k>r){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k--;
            }
        }
        else if(j<c){
            while(k<r){
                if(board[k][p]=='.'||board[k][p]=='-'){
                    emptyPath=1;
                }
                else{
                    emptyPath=0;
                    break;
                }
                k++;
            }
        }
    }
    if(emptyPath==1){
        if(board[r][c]=='-'||board[r][c]=='.'){
            char temp=board[r][c];
            board[r][c]=board[i][j];
            board[i][j]=temp;
        }
        else if(board[r][c]==opponent_piece){
            killed_arr[counter]=board[r][c];
            counter++;
            board[r][c]=board[i][j];
            board[i][j]=board[r-1][c];//some modifications must be applied here******************
        }
        else if(board[r][c]==friendly_piece){
            printf("Cannot eat friendly piece");
        }
    }
    else{
        printf("Invalid move");
    }
}
void pawn(int i, int j, int r, int c){
    int firstMove=0;
    if(board[i][j]==board[1][j] || board[i][j]==board[6][j]){
        firstMove=1;
    }
    if(firstMove==1 && r-i==2)){
        if(board[r][c]=='-'||board[r][c]=='.'){
            char temp=board[r][c];
            board[r][c]=board[i][j];
            board[i][j]=temp;
        }
        else if(board[r][c]==opponent_piece || board[r][c]==friendly_piece){
            printf("Invalid move");
        }
    }
    else if(r-i==1){
        if(board[r][c]=='-'){
            board[r][c]=board[i][j];
            board[i][j]='.';
        }
        else if(board[r][c]=='.'){
            board[r][c]=board[i][j];
            board[i][j]='-';
        }
        else if(board[r][c]==opponent_piece || board[r][c]==friendly_piece){
            printf("Invalid move");
        }
    }
    else if(r-i=1 && c-j=1 && board[r][c]==opponent_piece || r-i=-1 && c-j==1 && board[r][c]==opponent_piece){
            killed_arr[counter]=board[r][c];
            counter++;
            board[r][c]=board[i][j];
            board[i][j]='-';//some modifications must be applied here******************
    }
    else{
        printf("Invalid move");
    }
}




