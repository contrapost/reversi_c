#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "util.h"
#include "logging.h"

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
	
	fprintf(log, "%s%s", "\n=========================================", 
						 "================================================\n");
	fprintf(log, "Match between %s(BLACK) and %s(WHITE) /started at %s/", 
							black, white,  stringTime);
	fprintf(log, "%s%s", "\n=========================================", 
						 "================================================\n");
	
	fclose(log);
}

void saveMoveToLog(bool blackMove, char* black, char* white, 
												Point move, bool wrongMove) {
							
	char stringTime[100];
	setTime(stringTime);
	
	FILE *log = fopen("logfile.txt", "at");
    if (!log) 
    	log = fopen("logfile.txt", "wt");
    if (!log) {
        printf("can not open logfile.txt for writing.\n");
        return;   
    }
    
    
   	fprintf(log, "%s made move: %d-%c at %s, the move was %s.\n", 
   				blackMove ? black : white, move.y + 1, move.x + 65, stringTime, 
    			wrongMove ? "wrong" : "correct");

    fclose(log);
}

void endGameLog(int blackScore, int whiteScore, char* black, char* white) {

	FILE *log = fopen("logfile.txt", "at");
    if (!log) 
    	log = fopen("logfile.txt", "wt");
    if (!log) {
        printf("can not open logfile.txt for writing.\n");
        return;   
    }
	
	fprintf(log, "%s%s", "=========================================", 
						 "================================================\n");
	if(blackScore == whiteScore) {
		fprintf(log, "The game ended in a draw.");
	} else {
		fprintf(log, "The winner is %s. Final score %d (%s) : %d (%s).\n", 
			blackScore > whiteScore ? black : white, 
			blackScore > whiteScore ? blackScore : whiteScore, 
			blackScore > whiteScore ? black : white, 
			blackScore > whiteScore ? whiteScore : blackScore,
			blackScore > whiteScore ? white : black);
	}
	fprintf(log, "%s%s", "=========================================", 
					"================================================\n\n\n");
	
	fclose(log);
}
