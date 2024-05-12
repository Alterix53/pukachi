#pragma once
#ifndef _CHECK2_H_
#define _CHECK2_H_

#include "Struct.h"
#include "Utility.h"

CELL_2* findTheNode(CELL_2** arr, int y, int x);
bool Icheck(CELL_2**, int, int, int, int);
bool Lcheck(CELL_2**, int, int, int, int, int&, int&);
bool Ucheck(CELL_2**, int, int, int, int);
bool Zcheck(CELL_2** arr, int y1, int x1, int y2, int x2, int& cory1, int& corx1, int& cory2, int& corx2);
int allCheck(CELL_2** arr, int y1, int x1, int y2, int x2, int cory1, int corx1, int cory2, int corx2);
bool checkValidPairs(CELL_2**);
void suggest(CELL_2** arr);

#endif