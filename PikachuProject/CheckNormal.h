#pragma once
#include "Struct.h"

// all pattern check in normal mode
bool linecheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y);
bool Icheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y);
bool Lcheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& cornerX, int& cornerY);
bool Zcheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& corX1, int& corY1, int& corX2, int& corY2);
bool Ucheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& corX1, int& corY1, int& corX2, int& corY2);

// function to check all possible pattern
int allcheck(CELL_1**, int pos1X, int pos1Y, int pos2X, int pos2Y, int& corX1, int& corY1, int& corX2, int& corY2);
bool checkAnyValidPairs(CELL_1** board);		// check valid pairs to stop the game
void moveSuggestion(CELL_1** board);			// show hint for player


