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

bool makeMove(Board* board, bool blackMove, Point move);
bool possibleToMakeMove(Board* board, bool blackMove);
void getScore(int* blackScore, int* whiteScore, Board board);

#endif // _UTIL_H_
