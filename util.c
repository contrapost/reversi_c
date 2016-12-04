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

void getMove(Move* move) {
	
	char input[30] = "";
    
    int firstChar = 0, firstNumber = 0;
    
    bool firstInput = true;
    
    while(!(firstChar == 1 && firstNumber == 1)) {
    		
    	if(!firstInput) {
    		printf("%s %s", "Your input was invalid,",
    			"please enter the digit for row and the letter for column: ");
    		firstChar = 0;
    		firstNumber = 0;
    		for(int i = 0; i < 30; i++) input[i] = ' ';
    	}
    	
    	fgets(input, sizeof(input), stdin);
    
		for(int i = 0; i < 30; i++) {
			if(isdigit(input[i])) {
				move->y = (int)input[i] - 49;
				firstNumber++;
			}
			if(isalpha(input[i])) {
				move->x = (int)(tolower(input[i])) - 'a';
				firstChar++;
			}
		}
		firstInput = false;
    } 
}

bool makeMove(Board* board, bool* blackMove, Move move) {
	
	Field piece = (*blackMove ? BLACK : WHITE);

	Point neighborsWithOtherColor[BOARD_SIZE];
	int counter = 0;

	// 1. Check if move is outside the board
	if(move.x > BOARD_SIZE - 1 || move.y > BOARD_SIZE - 1) return false;
	
	// 2. Check if position is already occupied
	if(board->fields[move.x][move.y] != EMPTY) return false;
	
	// 3. check if the field has no occupied neighbors or all neighbors have
	// same color
	bool isAlone = true;
	bool onlySameColorNeighbors = true;
		
	for(int dy = -1; dy <= 1; dy++) {
		for(int dx = -1; dx <= 1; dx++) {
		
			if(dy == 0 && dy == dx) continue; // Already been checked in 1.
			
			int newX = move.x + dx, newY = move.y + dy;
			// ignoring positions beyond the edges
			if(newY < 0 || newY > BOARD_SIZE - 1 
						|| newX < 0 || newX > BOARD_SIZE - 1) continue; 
			
			// check for existing neighbors
			if(board->fields[newX][newY] != EMPTY) 
				isAlone = false;
			
			// check for neighbors' color
			if((*blackMove && board->fields[newX][newY] == WHITE) || 
				(!*blackMove && board->fields[newX][newY] == BLACK)) {
				onlySameColorNeighbors = false;
				neighborsWithOtherColor[counter].x = newX;
				neighborsWithOtherColor[counter++].y = newY;
			}
		}
	}
		
	if(isAlone) return false;
	if(onlySameColorNeighbors) return false;

	// 4. check lines and change color if possible
	
	bool canDrawLine = false;
	
	for(int i = 0; i < counter; i++){
	
		int x = neighborsWithOtherColor[i].x, 
			y = neighborsWithOtherColor[i].y,
			dX = x - move.x, dY = y - move.y;
		
		Point potentialTrophies[BOARD_SIZE - 1];
		int trophyCounter = 0;
			
		while(y < BOARD_SIZE && y >= 0 && x < BOARD_SIZE && x >= 0 
				&& board->fields[x][y] != EMPTY) {
			potentialTrophies[trophyCounter].x = x;
			potentialTrophies[trophyCounter++].y = y;
			if(board->fields[x][y] == piece) break;
			x += dX;
			y += dY;
		}
		
		int lastX = potentialTrophies[trophyCounter - 1].x;
		int lastY = potentialTrophies[trophyCounter - 1].y;
		
		if(board->fields[lastX][lastY] == piece) {
			board->fields[move.x][move.y] = piece;
			for(int i = 0; i < trophyCounter; i++) {
				board->fields[potentialTrophies[i].x][potentialTrophies[i].y] 
																		= piece;
				printf(" %c%d ", potentialTrophies[i].x + 65, 
												potentialTrophies[i].y + 1);
				canDrawLine = true;
			}
		} 
		
		printf("\n"); 		
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
	//	checkIfLineIsValid(blackMove, playersFields[i].x, playersFields[i].y);
	}
	
	return true;
}
