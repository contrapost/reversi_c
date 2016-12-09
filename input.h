#ifndef _INPUT_H_
#define _INPUT_H_

#include "util.h"

void getPlayerChoise(bool *withComputer, char* playerChiosePrompt);
int getLine (char* prmpt, char* buff, size_t sz);
void getName(char* prmpt, char* name, size_t sz);
void getMove(Point* move);
#endif // _INPUT_H_
