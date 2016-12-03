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

void getMove(int* rowIndex, int* columnIndex) {
	
	char move[30] = "";
    
    int firstChar = 0, firstNumber = 0;
    
    bool firstInput = true;
    
    while(!(firstChar == 1 && firstNumber == 1) || *rowIndex < 0 
    		|| *rowIndex > 7 || *columnIndex > 7) {
    		
    	
    		
    	if(!firstInput) {
    		printf("%s %s", "Your input was invalid,",
    			"please enter the digit for row and the letter for column: ");
    		*rowIndex = -1;
    		*columnIndex = -1;
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

bool makeMove(Board* board, bool blackMove, int rowIndex, int columnIndex) {

	// 1. Check if position is already occupied
	if(board->fields[rowIndex][columnIndex] != EMPTY) return false;
	
	// 2. check if the field has no occupied neighbors
	bool isAlone = true;
		
	for(int dy = -1; dy <= 1; dy++) {
			for(int dx = -1; dx <= 1; dx++) {
			
				if(dy == 0 && dy == dx) continue; // Already been checked in 1.
				
				int newY = rowIndex + dy, newX = columnIndex + dx;
				// ignoring positions beyond the edges
				if(newY < 0 || newY > 7 || newX < 0 || newX > 7) continue; 
				
				if(board->fields[newY][newX] != EMPTY) 
					isAlone = false;
			}
		}
		
	if(isAlone) return false;

	// 3. All invalid moves were excluded
	
	return true;
}
