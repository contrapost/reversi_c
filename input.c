#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "input.h"

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

void getMove(Point* move) {
	
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
