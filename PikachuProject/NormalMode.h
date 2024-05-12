#pragma once

#include "CheckNormal.h"
#include <conio.h>
#include <time.h>
#include "ConsoleSetting.h"
#include "Utility.h"
#include "DrawAndDelete.h"	
#include "Struct.h"
#include <iostream>
#include "MMsystem.h"
#include "Player.h"
using namespace std;

#pragma comment(lib, "Winmm.lib")

void initBoard(CELL_1** board);				// create the board for game
void renderBoard(CELL_1**);					// reprint the board (after any changes occur while playing the game)
void deleteBoard(CELL_1**);					// delete if finishing the game (or stop)

// move function: run the game and print the current board base on player's key input
void move(CELL_1** board, position& pos, int& status, player*& p, position selectedPos[], int& couple, int& point);
// The overall function for the normal mode 
void normalMode(player*& head, player*& p, ofstream& ofs, const string& filename);
