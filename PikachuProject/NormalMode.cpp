#include "NormalMode.h"



char bg[20][81];


/// Referrences: https://github.com/PhVanMin/Pikachuuu 

// initBoard with only 10 different elements
// each element is placed in a cell, up to 4 cells with the same element
void initBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT; i++) { // set up the position of each cells
        board[i] = new CELL_1[BOARDWIDTH];
        for (int j = 0; j < BOARDWIDTH; j++) {
            board[i][j].j = j;
            board[i][j].i = i;
        }
    }

    // setup the character
    for (int flagNum = 0; flagNum < (BOARDWIDTH * BOARDHEIGHT) / 2; flagNum++)
    {

        // charPrint number is the Nth + 1 character in the alphabet
        int charPrint = flagNum / 2;
        char c = 'A' + charPrint;

        // initialized character into two random cell:
        int index, timeInput = 2;
        while (timeInput) {

            // initialized all character randomly:
            index = rand() % 40; // total cell of the game is 40
            if (board[index / 8][index % 8].c == ' ') {
                board[index / 8][index % 8].c = c;
                timeInput--; // 
            }
        }
    }
}


void deleteBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            if (board[i][j].isValid) {
                board[i][j].deleteBox();
            }
        }
    }

    for (int i = 0; i < BOARDHEIGHT; i++) {
        delete[]board[i];
    }
    delete[]board;
}

// function to print the board after each moves: display the cell or display the background on deleted cell 
void renderBoard(CELL_1** board) {

    // each cell on the board share the same position of four border lines of the cell
    // must print the background first then print the remaining cells on top of the background
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            if (!board[i][j].isValid) {
                displayBackground(bg, j, i);
            }
        }
    }

    // draw cell if exist
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {

            if (board[i][j].isValid)
                board[i][j].drawBox(112);

        }
    }
}


// move function

void move(CELL_1** board, position& pos, int& status, player*& p, position selectedPos[], int& couple, int& point)
{
    position corner[2];
    int temp, key;
    temp = _getch();
    // if input key is not the arrow key :
    if (temp && temp != 224)
    {
        // esc key
        if (temp == ESC_KEY)
        {
            status = 2; // stop the game
        }

        // key type in is M: display a hint
        else if (toupper(temp) == HINT)
        {
            PlaySound(TEXT("hint.wav"), NULL, SND_FILENAME | SND_ASYNC);

            // annouce player use hint
            goToXY(117, 17);
            cout << "Hint use! - 30 points.";
            goToXY(117, 14);
            cout << "Point: " << point << " - 30 ";

            // show a valid move for player and update player's point
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            moveSuggestion(board);
            point -= 30;
            goToXY(117, 14);
            cout << "Point: " << point << "         ";
            goToXY(117, 17);
            cout << "                        ";
        }

        // case when player insert enter key:
        else if (temp == ENTER_KEY)
        {
            PlaySound(TEXT("lock.wav"), NULL, SND_FILENAME | SND_ASYNC);

            // player choose the same selected block
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {

                PlaySound(TEXT("wrong ans.wav"), NULL, SND_FILENAME | SND_ASYNC);
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70); //change cell's color into red (invalid move):
                Sleep(400);

                // deselect and stop marking that block:
                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;

                // reset the variable:
                couple = 2;
                p->life--;
                goToXY(117, 13);
                cout << "Life: " << p->life;
                selectedPos[0] = { -1, -1 };
            }

            // player chooses the first block, or player chooses the second block, which is different from the first block
            else {

                // save the position of the block, and mark the block as being selected:
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                // if the player has chosen 2 different block
                if (couple == 0) {

                    // check if two cells have the same character:
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) {

                        // check if two cells can be matched:
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, corner[0].x, corner[0].y, corner[1].x, corner[1].y) != 0) {

                            // change blocks' color into green (valid move):
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);

                            // increase the player's current point and display into the monitor
                            PlaySound(TEXT("correct ans.wav"), NULL, SND_FILENAME | SND_ASYNC);

                            int typeMatch = allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, corner[0].x, corner[0].y, corner[1].x, corner[1].y);
                            point += 20 * typeMatch;
                            goToXY(124, 15);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                            cout << "+" << 20 * typeMatch; // point player just got
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

                            // draw the line that matched two cells by current pattern match
                            switch (typeMatch) {
                            case 1: // I type
                                drawSingleLine(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                goToXY(117, 17);
                                cout << "I-type ";
                                break;
                            case 2: // L type
                                drawLMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, corner[0].y, corner[0].x);
                                goToXY(117, 17);
                                cout << "L-type ";
                                break;
                            case 3: // U type
                                drawZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, corner[0].y, corner[0].x, corner[1].y, corner[1].x);
                                goToXY(117, 17);
                                cout << "U-type ";
                                break;
                            case 4: // Z type
                                drawZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, corner[0].y, corner[0].x, corner[1].y, corner[1].x);
                                goToXY(117, 17);
                                cout << "Z-type ";
                                break;
                            }
                            cout << "+ " << 20 * typeMatch << " points!";
                            Sleep(700);

                            // delete the match lines after finish matching
                            switch (typeMatch) {
                            case 1: // I type
                                deleteSingleLine(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                goToXY(117, 17);
                                cout << "                    "; // delete the type match annoucement
                                break;
                            case 2: // L type
                                deleteLMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, corner[0].y, corner[0].x);
                                goToXY(117, 17);
                                cout << "                    ";
                                break;
                            case 3: // U type
                                deleteZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, corner[0].y, corner[0].x, corner[1].y, corner[1].x);
                                goToXY(117, 17);
                                cout << "                    ";
                                break;
                            case 4: // Z type
                                deleteZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, corner[0].y, corner[0].x, corner[1].y, corner[1].x);
                                goToXY(117, 17);
                                cout << "                    ";
                                break;
                            }

                            // update point
                            goToXY(117, 14);
                            cout << "Point: " << point;
                            goToXY(124, 15);
                            cout << "        ";
                            // change two blocks' status into invalid and delete
                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();

                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                        }

                        // if there is no matches can perform: 
                        else {
                            PlaySound(TEXT("wrong ans.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            // change two blocks' color into red (represent invalid move):
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                            Sleep(500);

                            // decrease player's life for a invalid move
                            p->life--;
                            goToXY(117, 13);
                            cout << "Life: " << p->life;
                        }
                    }
                    // if this is an invalid move (two different character):
                    else {
                        PlaySound(TEXT("wrong ans.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        // change two blocks' color into red (represent invalid move):
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                        Sleep(500);

                        // decrease player's life for a invalid move
                        p->life--;
                        goToXY(117, 13);
                        cout << "Life: " << p->life;
                    }
                    // after executed, deselect and stop marking two blocks:
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;

                    // return the couple variable
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    // find the valid block to represent the player's current position:
                    for (int i = pos.y; i < BOARDHEIGHT; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++) {
                        for (int j = 0; j <= pos.x; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    else // if the input key is the arrow key
    {
        // check if the current block is being chosen or not:
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x))
            board[pos.y][pos.x].isSelected = 0;
        switch (key = _getch())
        {
            // move the current postion base on the arrow key input:

        case KEY_UP:
            PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC); // move sound

            // First, find the exist cell that is above the current cell:
            // find the exited cell that above the current cell on the right (top right quadrant)
            for (int i = pos.x; i < BOARDWIDTH; i++) {      // right side
                for (int j = pos.y - 1; j >= 0; j--) {      // start from the row above the current cell's row
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            // find the exited cell that above the current cell on the left (top left quadrant)
            for (int i = pos.x - 1; i >= 0; i--) {          // left side
                for (int j = pos.y - 1; j >= 0; j--) {      // start from the row above the current cell's row
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            //  if there is no more exist cell above, find the cells that located on the furthest row behind current cell
            // find the exited cell that behind the current cell on the right (bottom right quadrant)
            for (int i = pos.x; i < BOARDWIDTH; i++) {          // right side 
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) { // start from furthest row
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }


            for (int i = pos.x; i >= 0; i--) {                  // left side 
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) { // start from furthest row
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            break;
        case KEY_DOWN:
            PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;
        case KEY_LEFT:
            PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);

            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;
        case KEY_RIGHT:
            PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);

            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}


void normalMode(player*& head, player*& p, ofstream& ofs, const string& filename)
{
    srand(time(0));
    getBackground(bg);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    CELL_1** board = new CELL_1 * [BOARDHEIGHT];
    int point = 0;
    p->life = 3;

    initBoard(board);
    createOutsideBorder();
    playerStatusBox(p);
    controlTutorialBox();

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };
    int status = 0;
    //0. playing the game
    //1. game is ended 
    //2. player quits the game

    while (!status && p->life)
    {
        board[curPosition.y][curPosition.x].isSelected = 1;

        renderBoard(board);

        move(board, curPosition, status, p, selectedPos, couple, point);

        if ((!checkAnyValidPairs(board))) status = 1;
    }

    renderBoard(board);
    deleteBoard(board);
    Sleep(500);
    system("cls");

    if (check_highest_point(p, point))
    {
        rearrange(head, p);
        writeLeaderBoard(p, ofs, filename);     //update highest point of the player
    }

    if (p->life && status == 1)
    {
        displayEndGameStatus(1);
        goToXY(50, 17);
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y')
            normalMode(head, p, ofs, filename);
    }
    else if (p->life == 0)
    {
        displayEndGameStatus(0);
        Sleep(2000);
    }
    system("cls");
}