#include "Struct.h"

using namespace std;

char box[5][12] = {
            {32,196,196,196,196,196,196,196,196,196,32},
            {179,32,32,32,32,32,32,32,32,32,179},
            {179,32,32,32,32,32,32,32,32,32,179},
            {179,32,32,32,32,32,32,32,32,32,179},
            {32,196,196,196,196,196,196,196,196,196,32}
};

void CELL_1::drawBox(int color)
{
    if (!isValid)
        return;

    int box_width = j + 2, box_length = i + 2;                  // x-y axis coordinate to draw on console

    for (int i = 0; i < 5; i++) {
        goToXY(box_width * 10, box_length * 4 + i);    // length and width
        cout << box[i];
    }

    if (isSelected)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (c % 6 + 1)); // add background colors when it is selected/pointed to
        for (int i = 1; i < 4; i++) {
            goToXY(box_width * 10 + 1, box_length * 4 + i);         // inside box
            cout << "         ";
        }

        goToXY(box_width * 10 + 5, box_length * 4 + 2);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else {
        goToXY(box_width * 10 + 5, box_length * 4 + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c % 6 + 1);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void CELL_1::deleteBox() {
    int x = j + 2, y = i + 2;

    for (int i = 0; i < 5; i++) {
        goToXY(x * 10, y * 4 + i);
        cout << "           ";          // basic black color -> blank
    }
}

void CELL_2::drawBox(int color) 
{
    int box_width = j + 2, box_length = i + 2;

    for (int i = 0; i < 5; i++) {
        goToXY(box_width * 10, box_length * 4 + i);    // length and width
        cout << box[i];
    }

    if (isSelected) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (c % 6 + 1)); // add background colors when it is selected/pointed to
        for (int i = 1; i < 4; i++) {
            goToXY(box_width * 10 + 1, box_length * 4 + i);         // inside box
            cout << "         ";
        }

        goToXY(box_width * 10 + 5, box_length * 4 + 2);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else {
        goToXY(box_width * 10 + 5, box_length * 4 + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c % 6 + 1);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void CELL_2::deleteBox() 
{
    int x = j + 2, y = i + 2;

    for (int i = 0; i < 5; i++) {
        goToXY(x * 10, y * 4 + i);
        cout << "           ";          // basic black color -> blank
    }
}