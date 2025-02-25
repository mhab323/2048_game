CC=gcc
OBJS=game.o main.o printBoard.o
EXEC=hw1_2048
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@


game.o: game.c game.h printBoard.h
main.o: main.c game.h
printBoard.o: printBoard.c printBoard.h



clean: 
	rm -f $(EXEC) $(OBJS)
	
