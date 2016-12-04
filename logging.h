#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "util.h"

void startGameLog(char* black, char* white);

void saveMoveToLog(bool blackMove, char* black, char* white,
													 Point move, bool wrongMove);
#endif // _LOGGING_H_
