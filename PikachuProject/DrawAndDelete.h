#pragma once
#include <iostream>
#include "ConsoleSetting.h"
using namespace std;

// function to draw a single line
void drawHorizontalLine(int pos1X, int pos1Y, int pos2X, int pos2Y);
void drawVerticalLine(int pos1X, int pos1Y, int pos2X, int pos2Y);

// function to draw line(s) base on the input coordinate
void drawSingleLine(int pos1X, int pos1Y, int pos2X, int pos2Y);
void drawLMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int cornerX, int cornerY);
void drawZorUMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int corX1, int corY1, int corX2, int corY2);

// function to delete lines
void deleteHorizontalLine(int pos1X, int pos1Y, int pos2X, int pos2Y);
void deleteVerticalLine(int pos1X, int pos1Y, int pos2X, int pos2Y);

// function to delete line(s) base on the input coordinate
void deleteSingleLine(int pos1X, int pos1Y, int pos2X, int pos2Y);
void deleteLMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int cornerX, int cornerY);
void deleteZorUMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int corX1, int corY1, int corX2, int corY2);
