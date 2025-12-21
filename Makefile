all: chess

chess: chessMain.o moves.o specialMoves.o board.o
		gcc chessMain.o moves.o specialMoves.o board.o -o chess

chessMain.o: chessMain.c moves.h borad.h specialMoves.h
		gcc -c chessMain.c 

moves.o: moves.c 
		gcc -c moves.c 

specialMoves.o : specialMoves.c
                 gcc -c specialMoves.c
	
board.o : borad.c
        gcc -c board.c