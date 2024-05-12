#include "DifficultMode.h"
#include<iostream>
using namespace std;

char BG[20][81];

/// Referrences: https://github.com/PhVanMin/Pikachuuu 


void deleteNode(CELL_2** arr, int y, int x, char BG[][81]) 
{
    //this function is to check if there is any box on the right side of a deleted box
    //  and delete it by pushing the remaining boxes on the right side of it on the row leftwards and delete the last block
    CELL_2* p = findTheNode(arr, y, x);
    if (x == 0)     //first col
    {
        if (arr[y]->next == NULL) //only a box valid
        {
            arr[y]->deleteBox();
            
                displayBackground(BG, arr[y]->j, y);
            arr[y] = NULL;
            return;
        }
        arr[y]->c = p->next->c;

        p = arr[y]->next;
        if (p->next == NULL)    //only 2 boxes valid
        {
            p->deleteBox();
            displayBackground(BG, p->j, y);
            delete p;
            arr[y]->next = NULL;
        }
        else {
            while (p->next->next != NULL)
            {
                p->c = p->next->c;
                p = p->next;
            }
            p->c = p->next->c;
            p->next->deleteBox();
            displayBackground(BG, p->next->j, p->next->i);
            delete p->next;
            p->next = NULL;
        }
    }
    else if (p->next != NULL) {
        while (p->next->next != NULL)
        {
            p->c = p->next->c;
            p = p->next;
        }
        p->c = p->next->c;
        p->next->deleteBox();
       displayBackground(BG, p->next->j, p->next->i);
        delete p->next;
        p->next = NULL;
    }
    else {
        p->deleteBox();
       displayBackground(BG, p->j, p->i);
        delete p;
        p = findTheNode(arr, y, x - 1);
        p->next = NULL;         //find the new last node and make it point to null

    }
}

void DifMode(CELL_2** arr, int y1, int x1, int y2, int x2, char BG[][81]) 
{
    if (x1 > x2)
    {
        deleteNode(arr, y1, x1, BG);
        deleteNode(arr, y2, x2, BG);
    }
    else {
        deleteNode(arr, y2, x2, BG);
        deleteNode(arr, y1, x1, BG);
    }
}



void initList(CELL_2**& board)
{
    for (int i = 0; i < BOARDHEIGHT; i++)
    {
        board[i] = NULL;
        for (int j = 0; j < BOARDWIDTH; j++)
        {
            CELL_2* node = new CELL_2;
            node->i = i;		//saving location of each node
            node->j = j;
            node->next = nullptr;
            if (board[i] == nullptr)
                board[i] = node;
            else
            {
                CELL_2* temp = board[i];
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = node;
            }
        }
    }

    int flagNum = (BOARDHEIGHT * BOARDWIDTH) / 2;
    while (flagNum)
    {
        int time = 2;
        char c = 65 + rand() % 26;
        while (time)
        {
            int i = rand() % 5;
            int j = rand() % 8;
            CELL_2* p = findTheNode(board, i, j);		//chose a random position
            if (p->c == ' ')
            {
                p->c = c;
                time--;		//put a random character in 2 random boxes
            }
        }
        flagNum--;
    }

}

void deleteList(CELL_2** arr) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        CELL_2* temp;
        while (arr[i] != NULL)
        {
            temp = arr[i];
            arr[i] = arr[i]->next;
            temp->deleteBox();
            if (temp->j < 4) displayBackground(BG, temp->j, i);
            Sleep(500);
            delete temp;
        }
    }
    delete[]arr;
}

void renderList(CELL_2** arr) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        CELL_2* temp = arr[i];
        while (temp != NULL)
        {
            temp->drawBox(112);
            temp = temp->next;
        }
    }
}

void move(CELL_2** arr, position& pos, int& status, player*& p, position selectedPos[], int& couple, int& point)
{
    int temp, key;
    position cor[2];
    temp = _getch();
    if (temp && temp != 224)
    { // neu ko phai la dau mui ten
        if (temp == ESC_KEY)
        { // neu la ESC
            status = 2;
        }

        else if (temp == 109 || temp == 77)
        {
            PlaySound(TEXT("hint.wav"), NULL, SND_FILENAME | SND_ASYNC);

            // annouce player use hint
            goToXY(117, 17);
            cout << "Hint use! - 30 points.";
            goToXY(117, 14);
            cout << "Point: " << point << " - 30 ";

            // show a valid move for player and update player's point
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            suggest(arr);
            point -= 30;
            goToXY(117, 14);
            cout << "Point: " << point << "         ";
            goToXY(117, 17);
            cout << "                        ";
        }


        else if (temp == ENTER_KEY) // neu la Enter
        {
            PlaySound(TEXT("lock.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y)
            {
                PlaySound(TEXT("wrong ans.wav"), NULL, SND_FILENAME | SND_ASYNC);
                CELL_2* temp = findTheNode(arr, pos.y, pos.x);
                temp->drawBox(70);
                Sleep(500);

                temp->isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p->life--;
                goToXY(117, 13);
                cout << "Life: " << p->life;
            } // check if chosing the same box twice
            else
            {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                findTheNode(arr, pos.y, pos.x)->isSelected = 1;
                couple--;

                if (couple == 0) //picking a pair
                {
                    CELL_2* p1, * p2;
                    p1 = findTheNode(arr, selectedPos[0].y, selectedPos[0].x);
                    p2 = findTheNode(arr, selectedPos[1].y, selectedPos[1].x);
                    if (p1->c == p2->c)     //match
                    {
                        if (allCheck(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x,cor[0].y,cor[0].x,cor[1].y, cor[1].x))
                        {
                            // increase the player's current point and display into the monitor
                            PlaySound(TEXT("correct ans.wav"), NULL, SND_FILENAME | SND_ASYNC);

                            int typeMatch = allCheck(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, cor[0].y, cor[0].x, cor[1].y, cor[1].x);
                            point += 20 * typeMatch;
                            goToXY(124, 15);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                            cout << "+" << 20 * typeMatch; // point player just got
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

                            // draw the line that matched two cells by current pattern match
                            switch (typeMatch)
                            {
                            case 1: // I type
                                drawSingleLine(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y);
                                goToXY(117, 17);
                                cout << "I-type ";
                                break;
                            case 2: // L type
                                drawLMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, cor[0].y, cor[0].x);
                                goToXY(117, 17);
                                cout << "L-type ";
                                break;
                            case 3: // U type
                                drawZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, cor[0].y, cor[0].x, cor[1].y, cor[1].x);
                                goToXY(117, 17);
                                cout << "U-type ";
                                break;
                            case 4: // Z type
                                drawZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, cor[0].y, cor[0].x, cor[1].y, cor[1].x);
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
                                deleteLMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, cor[0].y, cor[0].x);
                                goToXY(117, 17);
                                cout << "                    ";
                                break;
                            case 3: // U type
                                deleteZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, cor[0].y, cor[0].x, cor[1].y, cor[1].x);
                                goToXY(117, 17);
                                cout << "                    ";
                                break;
                            case 4: // Z type
                                deleteZorUMatchLines(selectedPos[0].x, selectedPos[0].y, selectedPos[1].x, selectedPos[1].y, cor[0].y, cor[0].x, cor[1].y, cor[1].x);
                                goToXY(117, 17);
                                cout << "                    ";
                                break;
                            }

                            // update point
                            goToXY(117, 14);
                            cout << "Point: " << point;
                            goToXY(124, 15);
                            cout << "        ";

                            // change the two blocks' color into green (for a valid move):
                            p1->drawBox(40);
                            p2->drawBox(40);

                            DifMode(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, BG);
                        }
                        else
                        {
                            PlaySound(TEXT("wrong ans.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            p1->drawBox(70);
                            p2->drawBox(70);
                            Sleep(500);

                            p->life--;
                            goToXY(117, 13);
                            cout << "Life: " << p->life;
                        }
                    }
                    else
                    {
                        PlaySound(TEXT("wrong ans.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        p1->drawBox(70);
                        p2->drawBox(70);
                        Sleep(500);

                        p->life--;
                        goToXY(117, 13);
                        cout << "Life: " << p->life;
                    }
                    // tra ve noi san xuat
                    p1->isSelected = 0;
                    p2->isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < BOARDHEIGHT; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (findTheNode(arr, i, j) != NULL) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++) { // chuyen den CELL_1 o tren
                        for (int j = 0; j <= pos.x; j++) {
                            if (findTheNode(arr, i, j) != NULL) {
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
    else //neu la dau mui ten
    {
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            findTheNode(arr, pos.y, pos.x)->isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
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
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
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
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
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
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
        default:
            break;
        }
    }
}

void difficultMode(player*& head, player*& p, ofstream& ofs, const string& filename)
{
    srand(time(0));
    getBackground(BG);

    int point = 0;
    p->life = 3;

    CELL_2** board = new CELL_2 * [BOARDHEIGHT];
    initList(board);
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
        findTheNode(board, curPosition.y, curPosition.x)->isSelected = 1;

        renderList(board);


        move(board, curPosition, status, p, selectedPos, couple, point);

        if ((!checkValidPairs(board)))
            status = 1;
    }

    renderList(board);
    deleteList(board);
    Sleep(500);
    system("cls");

    if (check_highest_point(p, point))
    {
        rearrange(head, p);
        writeLeaderBoard(head, ofs, filename);     //update highest point of the player
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
            difficultMode(head, p, ofs, filename);
        else
            writeLeaderBoard(head, ofs, filename);
    }
    else if (p->life == 0)
    {
        displayEndGameStatus(0);
        writeLeaderBoard(head, ofs, filename);
        Sleep(500);
    }
    system("cls");
}
