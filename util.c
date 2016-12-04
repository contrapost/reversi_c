#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "util.h"

void getName(char *prmpt, char *name, size_t sz) {

	int result = getLine(prmpt, name, sz);

	while(result == TOO_LONG || result == TOO_SHORT) {
		if (result == TOO_SHORT) {
		    printf ("\nName is empty, please enter name again.\n");
		}

		if (result == TOO_LONG) {
		    printf ("Input too long, please enter name again\n");
		}
		result = getLine(prmpt, name, sz);
	}
}

int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    
    fgets (buff, sz, stdin);
    
    int index = strlen(buff) - 1;
    
    if (index == 0 && buff[index] == '\n')
        return TOO_SHORT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';
    return OK;
}

void getMove(int* columnIndex, int* rowIndex) {
	
	char move[30] = "";
    
    int firstChar = 0, firstNumber = 0;
    
    bool firstInput = true;
    
    while(!(firstChar == 1 && firstNumber == 1)) {
    		
    	if(!firstInput) {
    		printf("%s %s", "Your input was invalid,",
    			"please enter the digit for row and the letter for column: ");
    		firstChar = 0;
    		firstNumber = 0;
    		for(int i = 0; i < 30; i++) move[i] = ' ';
    	}
    	
    	fgets(move, sizeof(move), stdin);
    
		for(int i = 0; i < 30; i++) {
			if(isdigit(move[i])) {
				*rowIndex = (int)move[i] - 49;
				firstNumber++;
			}
			if(isalpha(move[i])) {
				*columnIndex = (int)(tolower(move[i])) - 'a';
				firstChar++;
			}
		}
		firstInput = false;
    } 
}

bool makeMove(Board* board, bool blackMove, int columnIndex, int rowIndex) {
	
	// Set piece
	Field piece;
	int neighborsWithOtherColor[BOARD_SIZE][2];
	int counter = 0;
	
	if(blackMove)
		piece = BLACK;
	else
		piece = WHITE;

	// 1. Check if move is outside the board
	if(rowIndex > BOARD_SIZE - 1 || columnIndex > BOARD_SIZE - 1) return false;
	
	// 2. Check if position is already occupied
	if(board->fields[columnIndex][rowIndex] != EMPTY) return false;
	
	// 3. check if the field has no occupied neighbors or all neighbors have
	// same color
	bool isAlone = true;
	bool onlySameColorNeighbors = true;
		
	for(int dy = -1; dy <= 1; dy++) {
		for(int dx = -1; dx <= 1; dx++) {
		
			if(dy == 0 && dy == dx) continue; // Already been checked in 1.
			
			int newX = columnIndex + dx, newY = rowIndex + dy;
			// ignoring positions beyond the edges
			if(newY < 0 || newY > BOARD_SIZE - 1 
						|| newX < 0 || newX > BOARD_SIZE - 1) continue; 
			
			// check for existing neighbors
			if(board->fields[newX][newY] != EMPTY) 
				isAlone = false;
			
			// check for neighbors' color
			if((blackMove && board->fields[newX][newY] == WHITE) || 
				(!blackMove && board->fields[newX][newY] == BLACK)) {
				onlySameColorNeighbors = false;
				neighborsWithOtherColor[counter][0] = newX;
				neighborsWithOtherColor[counter++][1] = newY;
			}
		}
	}
		
	if(isAlone) return false;
	if(onlySameColorNeighbors) return false;

	// 4. check lines
	
	for(int i = 0; i < counter; i++){
	
		int x = neighborsWithOtherColor[i][0], 
			y = neighborsWithOtherColor[i][1],
			dX = x - columnIndex, dY = y - rowIndex;
		
		int potentialTrophies[7][2];
		int trophyCounter = 0;
			
		while(y < BOARD_SIZE && y >= 0 && x < BOARD_SIZE && x >= 0 
				&& board->fields[x][y] != EMPTY) {
			potentialTrophies[trophyCounter][0] = x;
			potentialTrophies[trophyCounter++][1] = y;
			if(board->fields[x][y] == piece) break;
			x += dX;
			y += dY;
		}
		
		int lastX = potentialTrophies[trophyCounter - 1][0];
		int lastY = potentialTrophies[trophyCounter - 1][1];
		
		if(board->fields[lastX][lastY] == piece) {
			for(int i = 0; i < trophyCounter; i++) {
				printf(" %c%d ", potentialTrophies[i][0] + 65, potentialTrophies[i][1] + 1);
			}
		}
		
		printf("\n"); 		
	}
	
	return true;
}
