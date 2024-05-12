#pragma once

#include <fstream>
#pragma once
#include <string>
#include "ConsoleSetting.h"
#include "Struct.h"
#include <iostream>
#include <thread>
#include <cstring>
#include <iostream>
#include <conio.h>
#include <sstream>
using namespace std;

// Ultilization for visual: background, menu selection, ...
void displayEndGameStatus(bool);												// print result after finishing the game
void getBackground(char[][81]);													// read background from file
void displayBackground(char[][81], int, int);									// print background
int mainMenu();																	// menu chosen in game
int In_game();																	// Choose menu when player play game (sign in, register)
void createOutsideBorder();														// the border of the game's board
void playerStatusBox(player* p);												// Player's status box, put on the top right side
void controlTutorialBox();														// tutorial box, shows how to play the game

// Ultilization for game: hint, stop game


