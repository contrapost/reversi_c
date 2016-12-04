#ifndef _UTIL_H_
#define _UTIL_H_

#include "util.h"

void startGameLog(char* black, char* white);

void saveMoveToLog(bool blackMove, char* black, char* white,
													 Point move, bool wrongMove);
#endif // _UTIL_H_
