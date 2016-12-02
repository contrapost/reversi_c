#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "util.h"

int main() {

	// Getting players' names
    char black[10], white[10];
    
    getName("Enter the name of player who will play with black pieces: ", 
    													black, sizeof(black));
    getName("Enter the name of player who will play with white pieces: ", 
    													white, sizeof(white));
    													
    while (strcmp(black, white) == 0) {
    	printf("Names of the player should be different!");
    	getName(" Enter the name of player who will play with white pieces: ", 
    													white, sizeof(white));
    }
    
    printf("\nReversi match between %s and %s.\n\n", black, white);
	
	// Initializing board
	Board currentBoard;
	initBoard(&currentBoard);
	
	// Starting game
	bool isntFinished = true;
	bool blackMove = true;
	
	while(isntFinished) {
		
		printBoard(&currentBoard);
		
		if(blackMove) {
			printf("Make your move, %s: ", black);
		} else {
			printf("Make your move, %s: ", white);
		}
		
		getMove(&blackMove);
		
	}
	
	
	
	return 0;
}
