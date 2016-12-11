#include <stdio.h>
#include <stdbool.h>
#include "ai_util.h"

void getAllPossibleMoves(Point* moves, int* numberOfMoves, 
												Board* board, bool blackMove) {
	
	Field piece = blackMove ? BLACK : WHITE;
	int numberOfPossibleMoves = 0;
	
	Point emptyFields[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfEmptyFields = 0;
	
	// check if there are no empty fields
	for(int y = 0; y < BOARD_SIZE; y++) {
		for(int x = 0; x < BOARD_SIZE; x++) {
			if(board->fields[x][y] == EMPTY) {
				emptyFields[numberOfEmptyFields].x = x;
				emptyFields[numberOfEmptyFields++].y = y;
			} 
		}
	}
	
	if(numberOfEmptyFields == 0) {
		*numberOfMoves = 0;
		return;
	}
	
	for(int i = 0; i < numberOfEmptyFields; i++) {
		Point neighborsWithOtherColor[8];
		int numberOfNeighbors = 0;
		
		getNeighborsWithOtherColor(neighborsWithOtherColor, &numberOfNeighbors, 
						emptyFields[i], blackMove, *board);
											
		for(int n = 0; n < numberOfNeighbors; n++) {
			
			Point validLine[BOARD_SIZE - 1];
			int lineLength = 0;
		
			getValidLine(validLine, neighborsWithOtherColor[n], board, 
						&lineLength, emptyFields[i], piece);
													
			if(lineLength != 0) moves[numberOfPossibleMoves++] = emptyFields[i];
		}
	}
	
	if(numberOfPossibleMoves != 0) {
		int i, j, numberOfMovesWithouDuplicates = 1;

		for(i = 1; i < numberOfPossibleMoves; i++){

		   	for(j = 0; j < numberOfMovesWithouDuplicates ; j++) {

				if(moves[i].x == moves[j].x && moves[i].y == moves[j].y) break;
			  
		   	}

			if (j == numberOfMovesWithouDuplicates) 
				moves[numberOfMovesWithouDuplicates++] = moves[i];
		}
	
		*numberOfMoves = numberOfMovesWithouDuplicates;
	} else {
		*numberOfMoves = 0;
	}
}

void getComputerMove(Board* board, Point *move) {
	Point possibleMoves[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfPossibleMoves = 0;
	
	getAllPossibleMoves(possibleMoves, &numberOfPossibleMoves, board, false);
	
	printf("All possible move for COMPUTER");
	for(int i = 0; i < numberOfPossibleMoves; i++) {
		printf(" %d-%c ", possibleMoves[i].y +1, possibleMoves[i].x + 65);
	}
	printf("\n");
}
