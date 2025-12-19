

chessMain: chessMain.o moves.o
		gcc chessMain.o moves.o -o chessMain

chessMain.o: chessMain.c moves.h
		gcc -c chessMain.c 

moves.o: moves.c 
		gcc -c moves.c 

