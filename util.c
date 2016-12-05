#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"

void getNeighborsWIthOtherColor(Point* neighbors, int* numberOfneighbors, 
									Point point, bool blackMove, Board board);
									
void getValidLine(Point* validLine, Point neighbor, Board board, 
									int* lineLength, Point point, Field piece);


bool makeMove(Board* board, bool* blackMove, Point move) {
	
	Field piece = (*blackMove ? BLACK : WHITE);
	Point neighborsWithOtherColor[BOARD_SIZE];
	int numberOfNeighbors = 0;

	// 1. Check if move is out of the board
	if(move.x > BOARD_SIZE - 1 || move.y > BOARD_SIZE - 1) return false;
	
	// 2. Check if position is already occupied
	if(board->fields[move.x][move.y] != EMPTY) return false;

	// 3. check if the field has no neighbors with other color
	getNeighborsWIthOtherColor(neighborsWithOtherColor, &numberOfNeighbors, 
													move, *blackMove, *board);
	if(numberOfNeighbors == 0) return false;									


	// 4. check lines and change color if possible
	bool canDrawLine = false;
	
	for(int i = 0; i < numberOfNeighbors; i++){	
		Point validLine[BOARD_SIZE - 1];
		int lineLength = 0;
		
		getValidLine(validLine, neighborsWithOtherColor[i], *board, 
													&lineLength, move, piece);
													
		if(lineLength != 0) {
			canDrawLine = true;
			board->fields[move.x][move.y] = piece;
			for(int i = 0; i < lineLength; i++) {
				board->fields[validLine[i].x][validLine[i].y] = piece;
			}
		}
	}
	
	if(!canDrawLine) return false; 
	
	*blackMove = !*blackMove;
	return true;
}

bool possibleToMakeMove(Board board, bool blackMove) {

	bool noEmpty = true;
	Point playersFields[BOARD_SIZE * BOARD_SIZE - 1];
	int playersFieldsCounter = 0;
	
	// check if there are no empty fields or pieces with same color
	for(int y = 0; y < BOARD_SIZE; y++) {
		for(int x = 0; x < BOARD_SIZE; x++) {
			if(board.fields[x][y] == EMPTY) {
				noEmpty = false;
			} else {
				if(board.fields[x][y] == (blackMove ? BLACK : WHITE)) {
					playersFields[playersFieldsCounter].x = x;
					playersFields[playersFieldsCounter++].y = y;
				}		
			}
					
		}
	}
	
	// DEBUGGING
	printf("Players fields: ");
	for(int i = 0; i < playersFieldsCounter; i++) {
		printf(" %c%d ", playersFields[i].x + 65, 
												playersFields[i].y + 1);
	}
	printf("\n"); 	
	
	if(noEmpty) return false;
	
	// check if it's possible to make a move
	
	for(int i = 0; i < playersFieldsCounter; i++) {
	//	checkIfLineIsValid(blackMove, playersFields[i]);
	}
	
	return true;
}

void getNeighborsWIthOtherColor(Point* neighbors, int* numberOfneighbors, 
									Point point, bool blackMove, Board board) {
	
	int counter = 0;								
	
	for(int dy = -1; dy <= 1; dy++) {
		for(int dx = -1; dx <= 1; dx++) {
			if(dy == 0 && dy == dx) continue;
			
			int newX = point.x + dx, newY = point.y + dy;
			// ignoring positions beyond the edges
			if(newY < 0 || newY > BOARD_SIZE - 1 
						|| newX < 0 || newX > BOARD_SIZE - 1) continue; 
			
			// check for neighbors' color
			if((blackMove && board.fields[newX][newY] == WHITE) || 
				(!blackMove && board.fields[newX][newY] == BLACK)) {
				neighbors[counter].x = newX;
				neighbors[counter++].y = newY;
			}
		}
	}
	
	*numberOfneighbors = counter;
	printf("DEBUGGING NEIGHB: ");
	for(int i = 0; i < counter; i++) {
		printf(" %c%d ", neighbors[i].x + 65, 
												neighbors[i].y + 1);
	}
	printf("\n");
}

void getValidLine(Point* validLine, Point neighbor, Board board, 
									int* lineLength, Point point, Field piece) {
	int x = neighbor.x, y = neighbor.y, dX = x - point.x, dY = y - point.y;
		
	Point potentialTrophies[BOARD_SIZE - 1];
	int trophyCounter = 0;
		
	while(y < BOARD_SIZE && y >= 0 && x < BOARD_SIZE && x >= 0 
			&& board.fields[x][y] != EMPTY) {
		potentialTrophies[trophyCounter].x = x;
		potentialTrophies[trophyCounter++].y = y;
		if(board.fields[x][y] == piece) break;
		x += dX;
		y += dY;
	}
	
	int lastX = potentialTrophies[trophyCounter - 1].x;
	int lastY = potentialTrophies[trophyCounter - 1].y;
	
	if(board.fields[lastX][lastY] == piece) {
		printf("DEBUGGING GET LINES: ");
		for(int i = 0; i < trophyCounter; i++) {
			validLine[i] = potentialTrophies[i];
			printf(" %c%d ", validLine[i].x + 65, validLine[i].y + 1);
		}
		*lineLength = trophyCounter;
	} 
}
