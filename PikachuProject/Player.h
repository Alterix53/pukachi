#pragma once
#include "ConsoleSetting.h"	
#include "Struct.h"				// player
#include <iostream>		
#include <fstream>			// read file
#include <string>			// username, password
#include <conio.h>
#include <sstream>
using namespace std;

// function for player: info (username, password), point achieve,....
bool check_highest_point(player* p, int point);									// check peak point (for leaderboard)
void input_player_in4(string& username, string& password);						// get player info (username & password)
bool check_password(player* p, string password);								// check player's password
player* check_name(player* head, string name);									// check player's username
player* add_player(player*& head, string name, string password);				// add new player
void rearrange(player*& head, player* new_player);								// swap player by player's point

// function for player's leaderboard
void readLeaderBoard(player*& head, ifstream& ifs, const string& filename);		// read leaderboard from file
void writeLeaderBoard(player* head, ofstream& ofs, const string& filename);		// write leaderboard into file
void printLeaderBoard(player* head);											// print the leaderboard