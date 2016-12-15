CC=gcc
DEPS = board.h game_util.h input.h logging.h ai_util.h
CFLAGS = -Wall -Wextra -std=c11 -g
all: game

%.o: %c $(DEPS)
	$(CC) -c -o $@ $<$(CFLAGS)

game: game.o board.o game_util.o input.o logging.o ai_util.o
	$(CC) -o game game.o board.o game_util.o input.o logging.o ai_util.o $(CFLAGS)
        
clean:
	rm -f game *.o
        
remake: clean game

