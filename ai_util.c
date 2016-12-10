#include <stdbool.h>
#include "ai_util.h"
//#include "game_util.h"

void computerMove(Board* board, Point *move) {
	Field piece = WHITE;
	
	Point emptyFields[BOARD_SIZE * BOARD_SIZE - NUMBER_OF_FIELDS_AT_START];
	int numberOfEmptyFields = 0;
	
	for(int y = 0; y < BOARD_SIZE; y++) {
		for(int x = 0; x < BOARD_SIZE; x++) {
			if(board->fields[x][y] == EMPTY) {
				emptyFields[numberOfEmptyFields].x = x;
				emptyFields[numberOfEmptyFields++].y = y;
			} 
		}
	}
	
	for(int i = 0; i < numberOfEmptyFields; i++) {
		Point neighborsWithOtherColor[8];
		int numberOfNeighbors = 0;
		
		getNeighborsWithOtherColor(neighborsWithOtherColor, &numberOfNeighbors, 
						emptyFields[i], false, *board);
											
		for(int n = 0; n < numberOfNeighbors; n++) {
			
			Point validLine[BOARD_SIZE - 1];
			int lineLength = 0;
		
			getValidLine(validLine, neighborsWithOtherColor[n], board, 
						&lineLength, emptyFields[i], piece);
			
										
		}
	}
}
