#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "logging.h"
#include "input.h"
#include "ai_util.h"

int main() {

	// Check if the player prefers match with computer or another player.
	bool withComputer = false;
	bool computerAnswersWithDelay = true;
	int delay = 2;
	char playerChiosePrompt[] = 
		"Do you want to play with computer or another person (C/P)? ";
	getPlayerChoise(&withComputer, playerChiosePrompt);

	// Getting players' names
    char black[10], white[10];
    char namePromptForPlayWithComputer[] = 
    			"You will play with BLACK(@) pieces. Enter your name: ";
    char namePromptBlack[] =
    			"Enter the name of player who will play with BLACK(@) pieces: ";
    char namePromptWhite[] = 
    			"Enter the name of player who will play with WHITE(.) pieces: ";
    
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
	
	bool blackMove = true;
	int blackScore = 0, whiteScore = 0;
	Point move;
	move.x = -1;
	move.y = -1;
	
	while(blackCanMove(&currentBoard) || whiteCanMove(&currentBoard)) {
		
		// Check if it's necessary to return move (i.e. if one player has to 
		// move but has no possibility to move the move should be return to 
		// player that can move.
		if((blackMove && !blackCanMove(&currentBoard) && 
									whiteCanMove(&currentBoard)) ||
					 (!blackMove && blackCanMove(&currentBoard) && 
					 				!whiteCanMove(&currentBoard))) {
			blackMove = !blackMove; 
			printf("\n%s cannot move.\n", blackMove ? white : black);
		}
		
		printBoard(&currentBoard);
		
		if(withComputer && !blackMove) {
			if(computerAnswersWithDelay) {
				printf("\nComputer is thinking...");
				fflush(stdout);
				sleep(delay);
			}
			getComputerMove(&currentBoard, &move);
			printf("\n\nComputer made move %d-%c.", move.y + 1, move.x + 65);
		} else {
			printf("\n\nMake your move, %s: ", blackMove ? black : white);
			getMove(&move);
		}
	
		bool wrongMove = false;
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
	
	// End the game: print final board, results and save results to the log.
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
	
	// For executing a compiled file on Windows
	printf("Press some button to close the window");
	getchar();
	
	return 0;
}
