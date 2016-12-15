#ifndef _AI_UTIL_H_
#define _AI_UTIL_H_

#include "game_util.h"

// struct using as return type in minimax function
typedef struct Result{
	int score;
	Point move;
} Result;

void getComputerMove(Board* board, Point *move);

#endif // _AI_UTIL_H_
