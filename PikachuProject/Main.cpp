#include "NormalMode.h"
#include "DifficultMode.h"

int main()
{
    initWindow();

    int status;
    int in_game;
    ifstream ifs;
    ofstream ofs;
    string filename = "Player_info.csv";
    string username;
    string password;
    player* head = nullptr;
    player* p;
    readLeaderBoard(head, ifs, filename);


    while ((status = mainMenu()) != 3)
    {
        switch (status)
        {
        case 0:
        {
            while ((in_game = In_game()) != 2)
            {
                if (!in_game)

                {
                    input_player_in4(username, password);
                    p = check_name(head, username);
                    if (!p || !check_password(p, password))
                    {
                        system("cls");
                        goToXY(40, 17);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "Ten tai khoan hoac mat khau khong dung!";
                        _getch();
                        system("cls");
                    }
                    else
                        normalMode(head, p, ofs, filename);
                }
                else
                {
                    input_player_in4(username, password);
                    p = check_name(head, username);
                    if (p)
                    {
                        system("cls");
                        goToXY(50, 17);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "ten tai khoan da duoc su dung";
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        p = add_player(head, username, password);
                        normalMode(head, p, ofs, filename);
                    }
                }
            }
            break;
        }

        case 1:
        {
            while ((in_game = In_game()) != 2)
            {
                if (!in_game)

                {
                    input_player_in4(username, password);
                    p = check_name(head, username);
                    if (!p || !check_password(p, password))
                    {
                        system("cls");
                        goToXY(40, 17);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "Ten tai khoan hoac mat khau khong dung!";
                        _getch();
                        system("cls");
                    }
                    else
                        difficultMode(head, p, ofs, filename);
                }
                else
                {
                    input_player_in4(username, password);
                    p = check_name(head, username);
                    if (p)
                    {
                        system("cls");
                        goToXY(50, 17);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "ten tai khoan da duoc su dung";
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        p = add_player(head, username, password);
                        difficultMode(head, p, ofs, filename);
                    }
                }
            }
            break;
        }

        case 2:
        {
            printLeaderBoard(head);
            break;
        }
        default:
            break;
        }
    }
}