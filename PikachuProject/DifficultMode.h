#pragma once
#include "CheckHard.h"
#include<conio.h>
#include<time.h>
#include "ConsoleSetting.h"
#include "Utility.h"
#include "Player.h"
#include "DrawAndDelete.h"

void deleteNode(CELL_2**, int, int, char[][81]);
void DifMode(CELL_2**, int, int, int, int, char[][81]);

void initList(CELL_2**&);
void deleteList(CELL_2**);
void renderList(CELL_2**);
void move(CELL_2** arr, position& pos, int& status, player*& p, position selectedPos[], int& couple, int& point);
void difficultMode(player*& head, player*& p, ofstream& ofs, const string& filename);