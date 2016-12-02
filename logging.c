#include <stdio.h>
#include <stdbool.h>

void startGameLog(char* black, char* white) {
	
	FILE *log = fopen("logfile.txt", "at");
    if (!log) 
    	log = fopen("logfile.txt", "wt");
    if (!log) {
        printf("can not open logfile.txt for writing.\n");
        return;   
    }
	
	fprintf(log, "\n===========================================\n");
	fprintf(log, "Match between %s(BLACK) and %s(WHITE)", black, white);
	fprintf(log, "\n===========================================\n");
	
	fclose(log);
}

void saveMoveToLog(bool blackMove, char* black, char* white, 
							int rowIndex, int columnIndex, bool wrongMove){
	FILE *log = fopen("logfile.txt", "at");
    if (!log) log = fopen("logfile.txt", "wt");
    if (!log) {
        printf("can not open logfile.txt for writing.\n");
        return;   
    }
    
    if(blackMove) {
    	fprintf(log, "%s made move: %d-%d, the move was %s\n", black, 
    				rowIndex, columnIndex, wrongMove ? "wrong" : "correct");
    } else {
    	fprintf(log, "%s made move: %d-%d, the move was %s\n", white, 
    				rowIndex, columnIndex, wrongMove ? "wrong" : "correct");
    }

    fclose(log);
}
