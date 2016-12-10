#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "logging.h"
#include "input.h"

int main() {

	// Check if the player prefers match with omputer or another player.
	bool withComputer = false;
	char playerChiosePrompt[] = 
		"Do you want to play with computer or another person (C/P)? ";
	getPlayerChoise(&withComputer, playerChiosePrompt);

	// Getting players' names
    char black[10], white[10];
    char namePromptForPlayWithComputer[] = 
    			"You will play with black pieces. Enter your name: ";
    char namePromptBlack[] =
    			"Enter the name of player who will play with BLACK pieces: ";
    char namePromptWhite[] = 
    			"Enter the name of player who will play with WHITE pieces: ";
    
    if(!withComputer) {
    	getName(namePromptBlack, black, sizeof(black));
    	getName(namePromptWhite, white, sizeof(white));
    													
		while (strcmp(black, white) == 0) {
			printf("Names of the player should be different!");
			getName(namePromptWhite, white, sizeof(white));
		} 
    
    } else {
    	getName(namePromptForPlayWithComputer, black, sizeof(black));
    	strcpy(white, "Computer");
    }
    
    printf("\nReversi match between %s and %s.", black, white);
	
	// Initializing board
	Board currentBoard;
	initBoard(&currentBoard);
	
	// Starting game
	startGameLog(black, white);
	
	bool changeTurn = false, blackMove = true, 
		 blackCanMove = true, whiteCanMove = true;
	int blackScore = 0, whiteScore = 0;
	Point move;
	move.x = -1;
	move.y = -1;
	
	while(blackCanMove || whiteCanMove) {
		
		changeTurn = (blackMove && !blackCanMove && whiteCanMove) ||
							(!blackMove && blackCanMove && !whiteCanMove);
		
/*		printf("\nDEB: blackCanMove=%s\n", blackCanMove ? "true" : "false");
		printf("DEB: whiteCanMove=%s\n", whiteCanMove ? "true" : "false");
		printf("DEB: changeTurn=%s\n", changeTurn ? "true" : "false");*/
		
		if(changeTurn) {
			blackMove = !blackMove; 
			printf("There is no way to move for %s\n.", 
													blackMove ? white : black);
			changeTurn = false;
		}
		
		blackCanMove = possibleToMakeMove(&currentBoard, blackMove);
		whiteCanMove = possibleToMakeMove(&currentBoard, !blackMove);
		
		if(!blackCanMove && !whiteCanMove) break;
		
		printBoard(&currentBoard);
		
		printf("\n\nMake your move, %s: ", blackMove ? black : white);
		
		bool wrongMove = false;
	
		if(blackMove) getMove(&move);
		else computerMove(&currentBoard, &move);
	
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
