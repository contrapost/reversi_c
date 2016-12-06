#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "logging.h"
#include "input.h"

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
    
    printf("\nReversi match between %s and %s.", black, white);
	
	// Initializing board
	Board currentBoard;
	initBoard(&currentBoard);
	
	// Starting game
	startGameLog(black, white);
	
	bool isntFinished = true;
	bool blackMove = true, blackCanMove = true, whiteCanMove = true;
	int blackScore = 0, whiteScore = 0;
	Point move;
	move.x = -1;
	move.y = -1;
	
	while(isntFinished) {
			
		bool changeTurn = (blackMove && !blackCanMove && whiteCanMove) ||
							(!blackMove && blackCanMove && !whiteCanMove);
		
		printf("DEB: blackCanMove=%s\n", blackCanMove ? "true" : "false");
		printf("DEB: whiteCanMove=%s\n", whiteCanMove ? "true" : "false");
		printf("DEB: changeTurn=%s\n", changeTurn ? "true" : "false");
						
	/*	bool changeTurn = (blackMove && !blackCanMove && whiteCanMove) ||
								!(blackMove && !blackCanMove && whiteCanMove);*/
		
		isntFinished = blackCanMove || whiteCanMove;
		
		if(isntFinished && changeTurn)
					blackMove = !blackMove; 
		
		if(isntFinished) {
		
			printBoard(&currentBoard);
			
			blackCanMove = possibleToMakeMove(&currentBoard, blackMove);
			whiteCanMove = possibleToMakeMove(&currentBoard, !blackMove);
			
			printf("\n\nMake your move, %s: ", blackMove ? black : white);
			
			bool wrongMove = false;
		
			getMove(&move);
		
			// If it's possible to make a move the player cannot refuse it
			while(!makeMove(&currentBoard, blackMove, move)) {
				wrongMove = true;
				printf("Your move isn't valid, try again: ");
				saveMoveToLog(blackMove, black, white, move, wrongMove);
				getMove(&move);
				wrongMove = false;
			}
			
			saveMoveToLog(blackMove, black, white, move, wrongMove);
			
			blackMove = !blackMove;
		}
	}
	
	printBoard(&currentBoard);
	
	getScore(&blackScore, &whiteScore, currentBoard);
	
	endGameLog(blackScore, whiteScore, black, white);
	
	if(blackScore == whiteScore) {
		printf("\nThe game ended in a draw.");
	} else {
		printf("\nThe winner is %s. Final score %d (%s) : %d (%s).\n", 
			blackScore > whiteScore ? black : white, 
			blackScore > whiteScore ? blackScore : whiteScore, 
			blackScore > whiteScore ? black : white, 
			blackScore > whiteScore ? whiteScore : blackScore,
			blackScore > whiteScore ? white : black);
	}
	
	return 0;
}
