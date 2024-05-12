#include "CheckNormal.h"

// function to check the cells in the line between two main cells, excluding the two main cells
bool linecheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y) {

    // check two cell on the same column
    if (pos1X == pos2X) {
        // create two indexes represent the first and last indexes between two cells
        int x = min(pos1Y, pos2Y);
        int y = max(pos1Y, pos2Y);

        // check if any cells are still valid on that line
        // if there is a cell -> cannot match 
        for (int i = x + 1; i < y; i++) {
            if (board[pos1X][i].isValid) {
                return false;
            }
        }
        return true;
    }

    // check two cell on the same row
    // code idea is similar to the code above

    if (pos1Y == pos2Y) {

        // create two indexes represent the first and last indexes between two cells
        int x = min(pos1X, pos2X);
        int y = max(pos1X, pos2X);

        // check if any cells are still valid on that line
        // if there is a cell -> cannot L match -> false; else true
        for (int i = x + 1; i < y; i++) {
            if (board[i][pos1Y].isValid) {
                return false;
            }
        }

        return true;
    }

    // not in the same column or column -> not in the same line
    return false;
}

// function to check the I-type match
bool Icheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y)
{
    // I-type check is the same as the line check function:
    return linecheck(board, pos1X, pos1Y, pos2X, pos2Y);
}

// function to check the L-type match
// if true, update the corner position to draw line
bool Lcheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& cornerX, int& cornerY) {

    bool line1, line2; // two variable to represent the status of each line (blank or not)

    // check if the corner cell is valid or not:
    // if yes, check if the two lines are valid
    // the first line is between the corner cell and the first cell, the second line is between the corner cell and the second cell

    if (!board[pos1X][pos2Y].isValid) {
        line1 = linecheck(board, pos1X, pos1Y, pos1X, pos2Y);
        line2 = linecheck(board, pos2X, pos2Y, pos1X, pos2Y);
        if (line1 && line2) {

            // update the corner position
            cornerX = pos1X;
            cornerY = pos2Y;
            return true;
        }
    }
    if (!board[pos2X][pos1Y].isValid) {
        line1 = linecheck(board, pos1X, pos1Y, pos2X, pos1Y);
        line2 = linecheck(board, pos2X, pos2Y, pos2X, pos1Y);
        if (line1 && line2) {
            // update the corner position
            cornerX = pos2X;
            cornerY = pos1Y;
            return true;
        }
    }
    return false;
}

// function to check the Z-type match
bool Zcheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& corX1, int& corY1, int& corX2, int& corY2) {
    // return false if two cell is on the same column/ column:
    if (pos1X == pos2X || pos1Y == pos2Y) {
        return false;
    }

    // create three bool variable for check 3 lines:
    bool line1, line2;

    // first case: two cells are matched by Z-line (or upside-down Z-line)
    // lines need to check are ranged from x + 1 to y - 1:
    int x = min(pos2Y, pos1Y);
    int y = max(pos1Y, pos2Y);

    // run a for loop to find the blank middle line:
    for (int i = x + 1; i < y; i++) {

        // check if the vertical line and two corner cell of that line is blank or not:
        if ((linecheck(board, pos1X, i, pos2X, i) == true) &&
            (!board[pos1X][i].isValid) &&  // corner cell 1
            (!board[pos2X][i].isValid))    // corner cell 2
        {
            // check the two lines, the first line is the horizontal line between first cell and first corner cell
            // the second line is the horizontal line between the second cell and second corner cell
            line1 = linecheck(board, pos1X, pos1Y, pos1X, i);
            line2 = linecheck(board, pos2X, pos2Y, pos2X, i);
            if (line1 && line2) {

                // save the location of two corners
                corX1 = pos1X;
                corY1 = i;

                corX2 = pos2X;
                corY2 = i;
                return true;
            }

        }

    }

    // second case: two cells are matched by horizontal Z-line:

    // lines need to check are ranged from x + 1 to y - 1:
    x = min(pos1X, pos2X);
    y = max(pos1X, pos2X);
    // run a loop to find the blank middle line:
    for (int i = x + 1; i < y; i++) {

        // check if the honrizontal line and two corner cell on that line is blank or not:
        if ((linecheck(board, i, pos1Y, i, pos2Y) == true) &&
            (!board[i][pos1Y].isValid) &&  // corner cell 1
            (!board[i][pos2Y].isValid))    // corner cell 2
        {
            // check the two lines, the first line is the vertical line between first cell and first corner cell
            // the second line is the vertical line between the second cell and second corner cell
            line1 = linecheck(board, pos1X, pos1Y, i, pos1Y);
            line2 = linecheck(board, pos2X, pos2Y, i, pos2Y);
            if (line1 && line2) {
                // save the location of two corners
                corX1 = i;
                corY1 = pos1Y;

                corX2 = i;
                corY2 = pos2Y;
                return true;
            }

        }
    }

    // if all cases are passed, the function return false as two cells cannot be Z-type matched
    return false;
}

// function to check the U-type match
bool Ucheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& corX1, int& corY1, int& corX2, int& corY2) {

    // check if both cells are in the same column/column and both locate at the border of the board
    // U-type check can be performed if these two cells match the condition above
    if ((pos1X == pos2X) && ((pos1X == 0) || (pos1X == BOARDHEIGHT - 1))) 
    {
        corX1 = (pos1X == 0) ? -1 : BOARDHEIGHT;
        corY1 = pos1Y;

        corX2 = (pos1X == 0) ? -1 : BOARDHEIGHT;
        corY2 = pos2Y;
        return true;
    }
    else if ((pos1Y == pos2Y) && ((pos1Y == 0) || (pos1Y == BOARDWIDTH - 1))) 
    {
        corX1 = pos1X;
        corY1 = (pos2Y == 0) ? -1 : BOARDWIDTH;

        corX2 = pos2X;
        corY2 = (pos2Y == 0) ? -1 : BOARDWIDTH;
        return true;

    }

    // remaining cases:
    else 
    {
        bool line1, line2;
        int x, y;


        // check U-type (and reverse U-type)
        x = min(pos1X, pos2X);
        y = max(pos1X, pos2X);

        for (int i = 0; i < BOARDHEIGHT; i++) {
            // x < i < y -> the Z, I, L type check
               // i <= x  or  i >= y  -> U type check
            if (i <= x || i >= y) 
            {

                // check if two corner cells and the line between are blank
                if ((linecheck(board, i, pos1Y, i, pos2Y)) &&     // the line
                    (!board[i][pos1Y].isValid) &&              // corner cell 1
                    (!board[i][pos2Y].isValid))                // corner cell 2
                {
                    // check the two remain lines
                    line1 = linecheck(board, pos1X, pos1Y, i, pos1Y);   // line 1
                    line2 = linecheck(board, pos2X, pos2Y, i, pos2Y);   // line 2
                    if (line1 && line2) {
                        corX1 = i;
                        corY1 = pos1Y;

                        corX2 = i;
                        corY2 = pos2Y;
                        return true;
                    }
                }


                // if the i index is right at the border of the board, 
                // the U-type check can be checked outside of the board by checking two lines:
                else if (i == 0 || i == (BOARDHEIGHT - 1)) {
                    // check if the corner cell is still valid and is one of two input cell. 
                    // If not, check two remaining lines:
                    if (!((board[i][pos1Y].isValid && i != pos1X) || (board[i][pos2Y].isValid && i != pos2X))) {
                        line1 = linecheck(board, pos1X, pos1Y, i, pos1Y);
                        line2 = linecheck(board, pos2X, pos2Y, i, pos2Y);

                        // if both lines are blank, or if one line is blank and the other cell locate
                        // right at the border of the board -> can be U-type matched
                            if ((line1 && line2) || (line1 && pos2X == i) || (pos1X == i && line2)) {
                                corX1 = (i == 0) ? -1 : BOARDHEIGHT;
                                corY1 = pos1Y;

                                corX2 = (i == 0) ? -1 : BOARDHEIGHT;
                                corY2 = pos2Y;
                            return true;
                        }
                    }
                }
            }
        }


        // check horizontal U-type
        // code idea is the same as above
        x = min(pos1Y, pos2Y);
        y = max(pos1Y, pos2Y);

        for (int i = 0; i < BOARDWIDTH; i++) {


            if (i <= x || i >= y) {
                if ((linecheck(board, pos1X, i, pos2X, i)) &&
                    (!board[pos1X][i].isValid) &&
                    (!board[pos2X][i].isValid))
                {
                    line1 = linecheck(board, pos1X, pos1Y, pos1X, i);
                    line2 = linecheck(board, pos2X, pos2Y, pos2X, i);
                    if (line1 && line2) {
                        corX1 = pos1X;
                        corY1 = i;

                        corX2 = pos2X;
                        corY2 = i;
                        return true;
                    }
                }

                else if (i == 0 || i == (BOARDWIDTH - 1)) {
                    if ((board[pos1X][i].isValid && i != pos1Y) || (board[pos2X][i].isValid && i != pos2Y))
                        continue;
                    line1 = linecheck(board, pos1X, pos1Y, pos1X, i);
                    line2 = linecheck(board, pos2X, pos2Y, pos2X, i);
                    if ((line1 && line2) || (line1 && pos2Y == i) || (pos1Y == i && line2)) {
                        corX1 = pos1X;
                        corY1 = (i == 0) ? -1 : BOARDWIDTH;

                        corX2 = pos2X;
                        corY2 = (i == 0) ? -1 : BOARDWIDTH;
                        return true;
                    }
                }
            }
        }

        // return false (already passing all cases of U-type matched)
        return false;

    }
}

// fuction to check if 
int allcheck(CELL_1** board, int pos1X, int pos1Y, int pos2X, int pos2Y, int& corX1, int& corY1, int& corX2, int& corY2) {

    // check all match type, from the simpliest to the most complicated
    if (Icheck(board, pos1X, pos1Y, pos2X, pos2Y)) {
        return 1;
    }
    else if (Lcheck(board, pos1X, pos1Y, pos2X, pos2Y, corX1, corY1)) {
        return 2;
    }
    else if (Ucheck(board, pos1X, pos1Y, pos2X, pos2Y, corX1, corY1, corX2, corY2)) {
        return 3;
    }
    else if (Zcheck(board, pos1X, pos1Y, pos2X, pos2Y, corX1, corY1, corX2, corY2)) {
        return 4;
    }

    return 0;
}

// function to check if any possible match pairs is still on the board
bool checkAnyValidPairs(CELL_1** board) {


    // idea: save and put all the cell adresses (i, j) that have the same character into an array
    // then each pairs will be check if they can be matched or not
    // continue to check all characters, from A to J, and stop whether a pair can be matched)

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0; // trash value to run code

    int* posXY = new int[8];
    char pair = 'A';
    while (pair <= 'J') {
        int cnt = 0;
        for (int i = 0; i < BOARDHEIGHT; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].isValid && board[i][j].c == pair) {
                    posXY[cnt++] = i; // column
                    posXY[cnt++] = j; // column
                }
            }
        }
        for (int i = 0; i < cnt - 2; i += 2) {
            for (int j = i + 2; j < cnt; j += 2) {
                if (allcheck(board, posXY[i], posXY[i + 1], posXY[j], posXY[j + 1], c1, c2, c3, c4) != 0) {
                    delete[] posXY;
                    return true;
                }
            }
        }
        pair++;
    }

    delete[] posXY;
    return false;
}

// function to show the move suggestion while playing the game
// note: the function always work, as the function check valid pairs run first.
void moveSuggestion(CELL_1** board)
{

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0; // trash value to run code

    int* posXY = new int[8];
    char suggest = 'A';
    while (suggest <= 'J') {

        int cnt = 0;
        // save all the address(row,column) of all the current cells that still exists and has the same character
        for (int i = 0; i < BOARDHEIGHT; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].isValid && board[i][j].c == suggest) {
                    posXY[cnt++] = i; // column
                    posXY[cnt++] = j; // column
                }
            }
        }

        // find the first two cell that can be matched 
        // display two cell (by changing the cell color) on the screen
        for (int i = 0; i < cnt - 2; i += 2) {
            for (int j = i + 2; j < cnt; j += 2) {
                if (allcheck(board, posXY[i], posXY[i + 1], posXY[j], posXY[j + 1], c1, c2, c3, c4) != 0) {

                    // note: change the status here for displaying color only
                    board[posXY[i]][posXY[i + 1]].isSelected = 1;
                    board[posXY[j]][posXY[j + 1]].isSelected = 1;
                    board[posXY[i]][posXY[i + 1]].drawBox(50);
                    board[posXY[j]][posXY[j + 1]].drawBox(50);
                    Sleep(850);

                    // return the original value after that
                    board[posXY[i]][posXY[i + 1]].isSelected = 0;
                    board[posXY[j]][posXY[j + 1]].isSelected = 0;
                    delete[] posXY;
                    return;
                }
            }
        }

        suggest++;
    }

}
