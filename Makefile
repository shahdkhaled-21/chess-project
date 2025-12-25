all: chess

chess: chessMain.o moves.o specialMoves.o board.o history.o
		gcc chessMain.o moves.o specialMoves.o board.o history.o -o chess

chessMain.o: chessMain.c moves.h board.h specialMoves.h history.h
		gcc -c chessMain.c 

board: board.o moves.o specialMoves.o history.o
	gcc board.o moves.o specialMoves.o history.o -o board

board.o : board.c moves.h specialMoves.h history.h
	gcc -c board.c

history: history.o moves.o
		gcc history.o moves.o -o history

history.o: history.c moves.h
		gcc -c history.c

specialMoves:specialMoves.o moves.o
			gcc specialMoves.o moves.o -o specialMoves

specialMoves.o : specialMoves.c moves.h
		gcc -c specialMoves.c

moves.o: moves.c specialMoves.h
		gcc -c moves.c 
clean:
	rm -f *.o chess board history specialMoves