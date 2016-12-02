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

void getMove(bool* isBlackMove) {
	
	char move[10];
	
	fgets(move, sizeof(move), stdin);
	
	int rowIndex, columnIndex;
    
    int firstChar = 0;
    int firstNumber = 0;
    
    for(int i = 0; i < 10; i++) {
    	if(isdigit(move[i])) {
    		rowIndex = (int)move[i] - 48;
    		firstNumber++;
    	}
    	if(isalpha(move[i])) {
    		columnIndex = (int)(tolower(move[i])) - 'a';
    		firstChar++;
    	}
    }
    
    while(firstChar != 1 || firstNumber != 1 || rowIndex < 1 || rowIndex > 8
    			|| columnIndex > 7) {
    			
    	fgets(move, sizeof(move), stdin);
    	
    	 int firstChar = 0;
   		 int firstNumber = 0;
    
    for(int i = 0; i < 10; i++) {
    	if(isdigit(move[i])) {
    		rowIndex = (int)move[i] - 48;
    		firstNumber++;
    	}
    	if(isalpha(move[i])) {
    		columnIndex = (int)(tolower(move[i])) - 'a';
    		firstChar++;
    	}
    }
    } 
    
   	printf("\n%d %d\n", rowIndex, columnIndex);
	
	*isBlackMove = !*isBlackMove;
}
