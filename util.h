#ifndef MAGICSORT_H_INCLUDED
#define MAGICSORT_H_INCLUDED

#include "board.h"

#define OK       0
#define TOO_SHORT 1
#define TOO_LONG 2

int getLine (char* prmpt, char* buff, size_t sz);
void getName(char* prmpt, char* name, size_t sz);
void getMove(int* rowIndex, int* columnIndex);
bool makeMove(Board* board, bool blackMove, int rowIndex, int columnIndex);

#endif // MAGICSORT_H_INCLUDED 