#ifndef _UTIL_H_
#define _UTIL_H_

#include "board.h"

#define OK       0
#define TOO_SHORT 1
#define TOO_LONG 2

typedef struct Move{
	int x, y;
} Move;

typedef struct Point{
	int x, y;
} Point;

int getLine (char* prmpt, char* buff, size_t sz);
void getName(char* prmpt, char* name, size_t sz);
void getMove(Point* move);
bool makeMove(Board* board, bool* blackMove, Point move);
bool possibleToMakeMove(Board board, bool blackMove);

#endif // _UTIL_H_
