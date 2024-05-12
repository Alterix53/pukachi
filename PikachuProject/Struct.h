#pragma once

#include <string>
#include <Windows.h>
#include "ConsoleSetting.h"
#include <iostream>
#pragma comment(lib, "Winmm.lib")
using namespace std;

// the size of the game board
#define BOARDWIDTH 8
#define BOARDHEIGHT 5

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13
#define HINT 77


struct position
{
	int x, y;
};

struct player
{
	string name = "";				// player's username
	string password = "";			// player's password
	int point = 0, life = 3;		// in game status
	player* next = nullptr;			// linked list
};

struct CELL_1
{
	int i, j;					// location of the row and collumn of a box respectively
	char c = ' ';				// character put in each box
	bool isValid = 1, isSelected = 0;
	// isValid: show status that the cell still existed on the game board
	// isSelected: show status that the cell is chosen by player or not

	void drawBox(int);			// print the cell to the board 
	void deleteBox();			// delete the cell on the board
};

struct CELL_2 {
	int i, j;
	char c = ' ';
	bool isSelected = 0;
	CELL_2* next /*= nullptr*/;

	void drawBox(int);
	void deleteBox();
};
