#include "DrawAndDelete.h"


// ---------------------------- LINE DRAWING FUNCTIONS --------------------------------------------------------
// draw the horizontal line by "-", and the vertical line by "|"
// Function to draw the horizontal line connect two cell
void drawHorizontalLine(int pos1X, int pos1Y, int pos2X, int pos2Y)
{
    int min_x = min(pos1X * 10 + 25, pos2X * 10 + 25);
    int max_x = max(pos1X * 10 + 25, pos2X * 10 + 25);
    int y = pos1Y * 4 + 10;
    for (int i = min_x; i <= max_x; i++) {
        goToXY(i, y);
        cout << "-";
    }
}

// Function to draw the vertical line connect two cell
void drawVerticalLine(int pos1X, int pos1Y, int pos2X, int pos2Y)
{
    int min_y = min(pos1Y * 4 + 10, pos2Y * 4 + 10);
    int max_y = max(pos1Y * 4 + 10, pos2Y * 4 + 10);
    int x = pos1X * 10 + 25;
    for (int i = min_y; i <= max_y; i++) {
        goToXY(x, i);
        cout << "|";
    }
}

// Draw a straight line connect two current position
void drawSingleLine(int pos1X, int pos1Y, int pos2X, int pos2Y) 
{
    if (pos1Y == pos2Y)
    {
        drawHorizontalLine(pos1X, pos1Y, pos2X, pos2Y);
    }
    else if (pos1X == pos2X) 
    {
        drawVerticalLine(pos1X, pos1Y, pos2X, pos2Y);
    }
}

void drawLMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int cornerX, int cornerY)
{
    drawSingleLine(pos1X, pos1Y, cornerX, cornerY);       // draw line from cell 1 -> corner block
    drawSingleLine(cornerX, cornerY, pos2X, pos2Y);       // draw line from corner block -> cell 2

}

void drawZorUMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int corX1, int corY1, int corX2, int corY2)
{
    drawSingleLine(pos1X, pos1Y, corX1, corY1);           // draw line from cell 1 -> corner block 1
    drawSingleLine(corX1, corY1, corX2, corY2);           // draw line from corner block 1 -> corner block 2
    drawSingleLine(corX2, corY2, pos2X, pos2Y);           // draw line form corner block 2 -> cell 2
}


// ---------------------------- LINE DELETE FUNCTIONS ---------------------------------------------------------
// The idea for the code is similar to the draw function, but print a white space character instead of the line
// Function to delete the horizontal line connect two cell 
void deleteHorizontalLine(int pos1X, int pos1Y, int pos2X, int pos2Y)
{
    int min_x = min(pos1X * 10 + 25, pos2X * 10 + 25);
    int max_x = max(pos1X * 10 + 25, pos2X * 10 + 25);
    int y = pos1Y * 4 + 10;
    for (int i = min_x; i <= max_x; i++) {
        goToXY(i, y);
        cout << " ";
    }
}

// Function to delete the vertical line connect two cell
void deleteVerticalLine(int pos1X, int pos1Y, int pos2X, int pos2Y)
{
    int min_y = min(pos1Y * 4 + 10, pos2Y * 4 + 10);
    int max_y = max(pos1Y * 4 + 10, pos2Y * 4 + 10);
    int x = pos1X * 10 + 25;
    for (int i = min_y; i <= max_y; i++) {
        goToXY(x, i);
        cout << " ";
    }
}

// Delete current line
void deleteSingleLine(int pos1X, int pos1Y, int pos2X, int pos2Y) {
    if (pos1Y == pos2Y) {
        deleteHorizontalLine(pos1X, pos1Y, pos2X, pos2Y);
    }
    else if (pos1X == pos2X) {
        deleteVerticalLine(pos1X, pos1Y, pos2X, pos2Y);
    }
}

void deleteLMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int cornerX, int cornerY) {
    deleteSingleLine(pos1X, pos1Y, cornerX, cornerY);       // delete line from cell 1 -> corner block
    deleteSingleLine(cornerX, cornerY, pos2X, pos2Y);       // delete line from corner block -> cell 2
}

void deleteZorUMatchLines(int pos1X, int pos1Y, int pos2X, int pos2Y, int corX1, int corY1, int corX2, int corY2) {
    deleteSingleLine(pos1X, pos1Y, corX1, corY1);           // delete line from cell 1 -> corner block 1
    deleteSingleLine(corX1, corY1, corX2, corY2);           // delete line from corner block 1 -> corner block 2
    deleteSingleLine(corX2, corY2, pos2X, pos2Y);           // delete line form corner block 2 -> cell 2
}

