#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "util.h"

void startGameLog(char* black, char* white);

void saveMoveToLog(bool blackMove, char* black, char* white,
													 Point move, bool wrongMove);
													 
void endGameLog(int blackScore, int whiteScore, char* black, char* white);

#endif // _LOGGING_H_
