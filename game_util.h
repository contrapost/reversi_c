#ifndef _UTIL_H_
#define _UTIL_H_

#include "board.h"

#define OK       0
#define TOO_SHORT 1
#define TOO_LONG 2

typedef struct Point{
	int x, y;
} Point;

void getNeighborsWithOtherColor(Point* neighbors, int* numberOfneighbors, 
									Point point, bool blackMove, Board* board);
									
void getValidLine(Point* validLine, Point neighbor, Board* board, 
	int* lineLength, Point point, Field piece);

bool makeMove(Board* board, bool blackMove, Point move);
bool possibleToMakeMove(Board* board, bool blackMove);
void getScore(int* blackScore, int* whiteScore, Board board);

#endif // _UTIL_H_
