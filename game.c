#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "logging.h"

int main() {

	// Getting players' names
    char black[10], white[10];
    char namePromptBlack[] =
    			"Enter the name of player who will play with BLACK pieces: ";
    char namePromptWhite[] = 
    			"Enter the name of player who will play with WHITE pieces: ";
    
    getName(namePromptBlack, black, sizeof(black));
    getName(namePromptWhite, white, sizeof(white));
    													
    while (strcmp(black, white) == 0) {
    	printf("Names of the player should be different!");
    	getName(namePromptWhite, white, sizeof(white));
    }
    
    printf("\nReversi match between %s and %s.\n\n", black, white);
	
	// Initializing board
	Board currentBoard;
	initBoard(&currentBoard);
	
	// Starting game
	startGameLog(black, white);
	
	bool isntFinished = true;
	bool blackMove = true;
	Point move;
	move.x = -1;
	move.y = -1;
	
	while(isntFinished) {
		
		printBoard(&currentBoard);
		
		if(possibleToMakeMove(currentBoard, blackMove)) {
			printf("Make your move, %s: ", blackMove ? black : white);
		
			bool wrongMove = false;
		
			getMove(&move);
		
			// If it's possible to make a move the player cannot refuse it
			while(!makeMove(&currentBoard, &blackMove, move)) {
				wrongMove = true;
				printf("Your move isn't valid, try again: ");
				saveMoveToLog(blackMove, black, white, move, wrongMove);
				getMove(&move);
				wrongMove = false;
			}
		
			saveMoveToLog(blackMove, black, white, move, wrongMove);
		
			printf("\n%d %d\n", move.x, move.y);
		} else {
			isntFinished = false;
		}
	}
	
	return 0;
}
