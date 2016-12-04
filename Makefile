CC=gcc
DEPS = board.h util.h input.h logging.h
CFLAGS = -Wall -Wextra -std=c11 -g
all: game

%.o: %c $(DEPS)
	$(CC) -c -o $@ $<$(CFLAGS)

game: game.o board.o util.o input.o logging.o
	$(CC) -o game game.o board.o util.o input.o logging.o $(CFLAGS)
        
clean:
	rm -f game *.o
        
remake: clean game

