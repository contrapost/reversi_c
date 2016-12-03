#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

void setTime(char* timeString) {
	time_t t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(timeString, 1000, "%X %A, %B %d %Y", p);
}

void startGameLog(char* black, char* white) {

	char stringTime[100];
	setTime(stringTime);
	
	FILE *log = fopen("logfile.txt", "at");
    if (!log) 
    	log = fopen("logfile.txt", "wt");
    if (!log) {
        printf("can not open logfile.txt for writing.\n");
        return;   
    }
	
	fprintf(log, "\n=========================================================================================\n");
	fprintf(log, "Match between %s(BLACK) and %s(WHITE) /started at %s/", 
							black, white,  stringTime);
	fprintf(log, "\n=========================================================================================\n");
	
	fclose(log);
}

void saveMoveToLog(bool blackMove, char* black, char* white, 
							int rowIndex, int columnIndex, bool wrongMove){
							
	char stringTime[100];
	setTime(stringTime);
	
	FILE *log = fopen("logfile.txt", "at");
    if (!log) 
    	log = fopen("logfile.txt", "wt");
    if (!log) {
        printf("can not open logfile.txt for writing.\n");
        return;   
    }
    
    
    if(blackMove) {
    	fprintf(log, "%s made move: %d-%c at %s, the move was %s.\n", black, 
    	rowIndex + 1, columnIndex + 65, stringTime, 
    										wrongMove ? "wrong" : "correct");
    } else {
    	fprintf(log, "%s made move: %d-%c at %s, the move was %s.\n", white, 
    	rowIndex + 1, columnIndex + 65, stringTime, 
    										wrongMove ? "wrong" : "correct");
    }

    fclose(log);
}
