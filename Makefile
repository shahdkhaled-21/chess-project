all: chess

chess: chessMain.o moves.o specialMoves.o board.o
		gcc chessMain.o moves.o specialMoves.o board.o -o chess

chessMain.o: chessMain.c moves.h board.h specialMoves.h
		gcc -c chessMain.c 

board: board.o moves.o specialMoves.o
	gcc board.o moves.o specialMoves.o -o board

board.o : board.c moves.h specialMoves.h 
	gcc -c board.c

moves.o: moves.c 
		gcc -c moves.c 

specialMoves.o : specialMoves.c
		gcc -c specialMoves.c
 