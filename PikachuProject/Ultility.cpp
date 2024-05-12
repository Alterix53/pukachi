#include "Utility.h"




// function to switch between options when player select to play game (in either mode)
int In_game()
{
    int choice[3] = { 0,0,0 };
    int temp, key, curchoice = 0;

    // change the function
    // highlighted the current player's choice
    while (1)
    {
        choice[curchoice] = 1;
        if (choice[0])
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); // highlight using white color

            for (int i = 0; i < 3; i++)
            {
                goToXY(73, 19 + i);
                cout << "            ";
            }
            goToXY(75, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 5);
            cout << "SIGN IN";
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++)
            {
                goToXY(73, 19 + i);
                cout << "            ";
            }

            goToXY(75, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            cout << "SIGN IN";
        }

        if (choice[1])
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++)
            {
                goToXY(73, 22 + i);
                cout << "            ";
            }
            goToXY(75, 23);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 3);
            cout << "REGISTER";
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++)
            {
                goToXY(73, 22 + i);
                cout << "            ";
            }

            goToXY(75, 23);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            cout << "REGISTER";
        }

        if (choice[2])
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++)
            {
                goToXY(73, 25 + i);
                cout << "               ";
            }
            goToXY(75, 26);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 2);
            cout << "BACK TO MENU";
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++)
            {
                goToXY(73, 25 + i);
                cout << "               ";
            }

            goToXY(75, 26);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << "BACK TO MENU";
        }


        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if (temp = _getch())
        {
            if (temp != 224 && temp)    //not the arrow keys
            {
                if (temp == ENTER_KEY)
                {
                    system("cls");
                    return curchoice;
                }
            }
            else                // case arrow keys
            {
                key = _getch();
                switch (key)
                {
                case KEY_UP:
                    choice[curchoice] = 0;
                    if (curchoice > 0)
                        curchoice--;
                    else curchoice = 2;
                    break;
                case KEY_DOWN:
                    choice[curchoice] = 0;
                    if (curchoice < 2)
                        curchoice++;
                    else curchoice = 0;
                    break;
                default:
                    break;
                }
            }
        }
    }
}


void displayEndGameStatus(bool win) {
    if (win)
    {
        PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        goToXY(40, 8);
        cout << "  ____ ___  _   _  ____ ____      _  _____ _   _ _        _  _____ ___ ___  _   _ _ ";
        goToXY(40, 9);
        cout << " / ___/ _ \\| \\ | |/ ___|  _ \\    / \\|_   _| | | | |      / \\|_   _|_ _/ _ \\| \\ | | |";
        goToXY(40, 10);
        cout << "| |  | | | |  \\| | |  _| |_) |  / _ \\ | | | | | | |     / _ \\ | |  | | | | |  \\| | |";
        goToXY(40, 11);
        cout << "| |__| |_| | |\\  | |_| |  _ <  / ___ \\| | | |_| | |___ / ___ \\| |  | | |_| | |\\  |_|";
        goToXY(40, 12);
        cout << " \\____\\___/|_| \\_|\\____|_| \\_\\/_/   \\_\\_|  \\___/|_____/_/   \\_\\_| |___\\___/|_| \\_(_)";
        goToXY(40, 13);
        cout << "                      _    _ ___  _   _  __        _____  _   _";
        goToXY(40, 14);
        cout << "                      \\ \\ / / _ \\| | | | \\ \\      / / _ \\| \\ | |                    ";
        goToXY(40, 15);
        cout << "                       \\ V / | | | | | |  \\ \\ /\\ / / | | |  \\| |                    ";
        goToXY(40, 16);
        cout << "                        | || |_| | |_| |   \\ V  V /| |_| | |\\  |                    ";
        goToXY(40, 17);
        cout << "                        |_| \\___/ \\___/     \\_/\\_/  \\___/|_| \\_|                    ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else
    {
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        goToXY(42, 10);
        cout << " ____   _____  _____  _____  _____  ____         _     _   _   ____  _  __";
        goToXY(42, 11);
        cout << "| __ ) | ____||_   _||_   _|| ____||  _ \\       | |   | | | | / ___|| |/ /";
        goToXY(42, 12);
        cout << "|  _ \\ |  _|    | |    | |  |  _|  | |_) |      | |   | | | || |    | ' / ";
        goToXY(42, 13);
        cout << "| |_) || |___   | |    | |  | |___ |  _ <       | |___| |_| || |___ | . \\ ";
        goToXY(42, 14);
        cout << "|____/ |_____|  |_|    |_|  |_____||_| \\_\\      |_____|\\___/  \\____||_|\\_\\";
        goToXY(42, 16);
        cout << " _   _  _____ __  __ _____          _____  ___  __  __  _____             ";
        goToXY(42, 17);
        cout << "| \\ | || ____|\\ \\/ /|_   _|        |_   _||_ _||  \\/  || ____|            ";
        goToXY(42, 18);
        cout << "|  \\| ||  _|   \\  /   | |            | |   | | | |\\/| ||  _|              ";
        goToXY(42, 19);
        cout << "| |\\  || |___  /  \\   | |            | |   | | | |  | || |___             ";
        goToXY(42, 20);
        cout << "|_| \\_||_____|/_/\\_\\  |_|            |_|  |___||_|  |_||_____|            ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void getBackground(char bg[][81])
{
    ifstream fin("charizard2.txt");
    if (fin) {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 81; j++)
            {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        memset(bg, ' ', sizeof(bg));
    }
}

void displayBackground(char bg[][81], int x, int y) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for (int i = 0; i < 5; i++) {       // cell height
        for (int j = 0; j < 11; j++) {  // cell width
            goToXY((x + 2) * 10 + j, (y + 2) * 4 + i);
            cout << bg[y * 4 + i][x * 10 + j];
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int mainMenu()
{
    PlaySound(TEXT("1-01. Main Menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    int choice[4] = { 0,0,0,0 }, temp, key, curChoice = 0;

    while (1)
    {
        for (int j = 1; j < 7; j++)
        {
            goToXY(42, 2);

            // pikachu ascii art
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), j);
            cout << " ______    __   __  ___      ___       ______  __    __   __    __";
            goToXY(42, 3);
            cout << "|   _  \\  |  | |  |/  /     /   \\     /      ||  |  |  | |  |  |  |";
            goToXY(42, 4);
            cout << "|  |_)  | |  | |  '  /     /  ^  \\   |  ,----'|  |__|  | |  |  |  |";
            goToXY(42, 5);
            cout << "|   ___/  |  | |    <     /  /_\\  \\  |  |     |   __   | |  |  |  |";
            goToXY(42, 6);
            cout << "|  |      |  | |  .  \\   /  _____  \\ |  `----.|  |  |  | |  `--'  |";
            goToXY(42, 7);
            cout << "|__|      |__| |__|\\__\\ /__/     \\__\\ \\______||__|  |__|  \\______/";

            // matching game, ascii art
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), j + 3);
            goToXY(30, 9);
            cout << "   _____          __         .__    .__                                               ";
            goToXY(30, 10);
            cout << "  /     \\ _____ _/  |_  ____ |  |__ |__| ____    ____      _________    _____   ____  ";
            goToXY(30, 11);
            cout << " /  \\ /  \\\\__  \\\\   __\\/ ___\\|  |  \\|  |/    \\  / ___\\    / ___\\__  \\  /     \\_/ __ \\ ";
            goToXY(30, 12);
            cout << "/    Y    \\/ __ \\|  | \\  \\___|   Y  \\  |   |  \\/ /_/  >  / /_/  > __ \\|  Y Y  \\  ___/ ";
            goToXY(30, 13);
            cout << "\\____|__  (____  /__|  \\___  >___|  /__|___|  /\\___  /   \\___  (____  /__|_|  /\\___  >";
            goToXY(30, 14);
            cout << "        \\/     \\/          \\/     \\/        \\//_____/   /_____/     \\/      \\/     \\/ ";

            choice[curChoice] = 1;

            if (choice[0])
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 19 + i);
                    cout << "             ";
                }

                goToXY(76, 20);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 3);
                cout << "NORMAL";
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 19 + i);
                    cout << "             ";
                }

                goToXY(76, 20);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                cout << "NORMAL";
            }

            if (choice[1]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 22 + i);
                    cout << "             ";
                }

                goToXY(75, 23);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 4);
                cout << "DIFFICULT";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 22 + i);
                    cout << "             ";
                }

                goToXY(75, 23);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                cout << "DIFFICULT";
            }

            if (choice[2]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 25 + i);
                    cout << "             ";
                }

                goToXY(74, 26);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 2);
                cout << "LEADERBOARD";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 25 + i);
                    cout << "             ";
                }

                goToXY(74, 26);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "LEADERBOARD";
            }

            if (choice[3]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

                for (int i = 0; i < 3; i++) {
                    goToXY(73, 28 + i);
                    cout << "             ";
                }

                goToXY(77, 29);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 6);
                cout << "EXIT";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                for (int i = 0; i < 3; i++) {
                    goToXY(73, 28 + i);
                    cout << "             ";
                }

                goToXY(77, 29);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << "EXIT";
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            if (temp = _getch())
            {

                if (temp != 224 && temp)    //not the arrow keys
                {
                    if (temp == ENTER_KEY)
                    {
                        system("cls");
                        return curChoice;
                    }
                }
                else        //arrows key
                {
                    key = _getch();
                    switch (key)
                    {
                    case KEY_UP:
                        choice[curChoice] = 0;
                        if (curChoice > 0)
                            curChoice--;
                        else curChoice = 3;
                        break;
                    case KEY_DOWN:
                        choice[curChoice] = 0;
                        if (curChoice < 3)
                            curChoice++;
                        else curChoice = 0;
                    default:
                        break;
                    }
                }
            }
            if (j == 6)
                j = 1;
        }
    }

}

// function to print a tutorial box beside the game board:
void controlTutorialBox() {
    goToXY(115, 23);
    cout << "___________________________________";
    goToXY(115, 24);
    cout << "|                                 |";
    goToXY(115, 25);
    cout << "|            HOW TO PLAY:         |";
    goToXY(115, 26);
    cout << "|                                 |";
    goToXY(115, 27);
    cout << "| Press arrow key to move         |";
    goToXY(115, 28);
    cout << "| Press Enter to choose block     |";
    goToXY(115, 29);
    cout << "| Press ESC to quit               |";
    goToXY(115, 30);
    cout << "| Press M for hint                |";
    goToXY(115, 31);
    cout << "|_________________________________|";
}

// function to Print the Player's beginning stats:
void playerStatusBox(player* p)
{

    goToXY(115, 8);
    cout << "._________________________________.";
    goToXY(115, 9);
    cout << "|                                 |";
    goToXY(115, 10);
    cout << "|               STATS             |";
    goToXY(115, 11);
    cout << "|                                 |";
    goToXY(115, 12);
    cout << "| Name: " << p->name;                  // player's name
    goToXY(149, 12);
    cout << "|";
    goToXY(115, 13);
    cout << "| Life: " << p->life;                   // stating life is 3
    goToXY(149, 13);
    cout << "|";
    goToXY(115, 14);
    cout << "| Point: 0                        |";  // starting point is 0
    goToXY(115, 15);
    cout << "|                                 |";
    goToXY(115, 16);
    cout << "|                                 |";
    goToXY(115, 17);
    cout << "|                                 |";
    goToXY(115, 18);
    cout << "|_________________________________|";
}

// funtion to draw an outside border of the game:
void createOutsideBorder() {
    system("cls");
    goToXY(40, 15);
    cout << "Generating stage, please wait.   ";


    goToXY(10, 3); // top left corner
    cout << (char)218;

    // top line
    for (int i = 1; i < 100; i++) {
        goToXY(10 + i, 3);
        cout << (char)196;
        if (i == 50) {
            goToXY(40, 15);
            cout << "Generating stage, please wait.. ";
        }
        Sleep(9);
    }
    goToXY(110, 3); // top right corner
    cout << (char)191;

    // right line
    for (int i = 0; i <= 28; i++) {
        goToXY(110, 4 + i);
        cout << (char)179;
        if (i == 14) {
            goToXY(40, 15);
            cout << "Generating stage, please wait...";
        }
        Sleep(14);
    }

    goToXY(110, 33); // bottom right corner
    cout << (char)217;

    // bottom line
    for (int i = 0; i < 100; i++) {
        goToXY(109 - i, 33);
        cout << (char)196;
        if (i == 50) {
            goToXY(40, 15);
            cout << "Generating stage, please wait.  ";
        }
        Sleep(9);
    }

    goToXY(10, 33); // bottom left corner
    cout << (char)192;

    // left line
    for (int i = 28; i >= 0; i--) {
        goToXY(10, 4 + i);
        cout << (char)179;
        if (i == 14) {
            goToXY(40, 15);
            cout << "Generating stage, please wait..";
        }
        Sleep(14);
    }

}



