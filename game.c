#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "logging.h"

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
	startGameLog(black, white);
	
	bool isntFinished = true;
	bool blackMove = true;
	int rowIndex = -1, columnIndex = -1;
	
	while(isntFinished) {
		
		printBoard(&currentBoard);
		
		if(blackMove) {
			printf("Make your move, %s: ", black);
		} else {
			printf("Make your move, %s: ", white);
		}
		
		
		bool wrongMove = false;
		
		getMove(&rowIndex, &columnIndex);
		
		while (!makeMove(&currentBoard, blackMove, rowIndex, columnIndex)) {
			wrongMove = true;
			printf("Your move isn't valid, try again: ");
			saveMoveToLog(blackMove, black, white, 
											rowIndex, columnIndex, wrongMove);
			getMove(&rowIndex, &columnIndex);
			wrongMove = false;
		}
		
		saveMoveToLog(blackMove, black, white, 
											rowIndex, columnIndex, wrongMove);
		
		printf("\n%d %d\n", rowIndex, columnIndex);
		
		blackMove = !blackMove;
	}
	
	
	
	return 0;
}
