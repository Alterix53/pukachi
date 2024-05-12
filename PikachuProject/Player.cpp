#include "Player.h"


player* add_player(player*& head, string name, string password)
{
    player* cur = head;
    if (!head)
    {
        head = new player;
        head->name = name;
        head->password = password;
        return head;
    }
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = new player{ name,password };
    return cur->next;
}

void rearrange(player*& head, player* new_player)
{
    if (!head->next || !head)    //only a player or no player
        return;
    player* cur = head;
    while (cur->next != new_player && cur->next)
    {
        cur = cur->next;
    }
    cur->next = cur->next->next;
    cur = head;

    if (new_player->point >= cur->point)
    {
        new_player->next = head;
        head = new_player;
        return;
    }

    while (cur->next && cur->next->point > new_player->point)
    {
        cur = cur->next;
    }
    new_player->next = cur->next;
    cur->next = new_player;
}

void printLeaderBoard(player* head)
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    goToXY(29, 2);
    cout << "'||'     '||''''|     |   '||''|. '||''''| '||''|.  '||''|.   ..|''||     |   '||''|.  '||''|.  ";
    goToXY(29, 3);
    cout << " ||       ||  .      |||   ||   || ||  .    ||   ||  ||   || .|'    ||   |||   ||   ||  ||   || ";
    goToXY(29, 4);
    cout << " ||       ||''|     |  ||  ||    ||||''|    ||''|'   ||'''|. ||      || |  ||  ||''|'   ||    ||";
    goToXY(29, 5);
    cout << " ||       ||       .''''|. ||    ||||       ||   |.  ||    ||'|.     ||.''''|. ||   |.  ||    ||";
    goToXY(29, 6);
    cout << ".||.....|.||.....|.|.  .||.||...|'.||.....|.||.  '|'.||...|'  ''|...|'.|.  .||.||.  '|'.||...|' ";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    // draw the border for the leaderboard board:
    goToXY(40, 10);
    cout << (char)218;

    goToXY(41, 10);
    for (int i = 0; i < 75; i++) {
        cout << (char)196;
    }
    goToXY(41, 14);
    for (int i = 0; i < 75; i++) {
        cout << (char)196;
    }
    for (int i = 0; i < 26; i++) {
        goToXY(40, 11 + i);
        cout << (char)179;
    }
    for (int i = 0; i < 26; i++) {
        goToXY(115, 11 + i);
        cout << (char)179;
    }
    goToXY(115, 10);
    cout << (char)191;

    goToXY(40, 14);
    cout << (char)195;

    goToXY(115, 14);
    cout << (char)180;

    // set up the score board 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    goToXY(47, 12);
    cout << "NO.";
    goToXY(60, 12);
    cout << "PLAYER'S NAME";
    goToXY(100, 12);
    cout << "POINT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    goToXY(60, 40);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "Press any key to return to menu";
    int i = 0;
    int countP = 0;
    while (head) // write all the players
    {
        countP++;
        switch (countP) {
        case 1: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); break;
        case 2: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;
        case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); break;
        default: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break;
        }
        goToXY(47, 16 + i);
        cout << countP << ".";
        goToXY(60, 16 + i);
        cout << head->name;
        goToXY(100, 16 + i);
        cout << head->point;
        goToXY(45, 17 + i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        for (int i = 0; i < 65; i++) {
            cout << (char)196;
        }

        i += 2;
        head = head->next;

    }
    if (countP < 10) {
        goToXY(58, 16 + i);
        cout << "More players will be written down here..";
    }
    goToXY(40, 36);
    cout << (char)192;
    for (int i = 0; i < 74; i++) {
        cout << (char)196;
    }
    cout << (char)217;

    _getch(); // back to menu
    system("cls");
}

void readLeaderBoard(player*& head, ifstream& ifs, const string& filename)
{
    ifs.open(filename);
    player* cur = head;
    if (!ifs.is_open())
    {
        cout << "Failed to open Leader Board file!";
        return;
    }
    string line;

    while (getline(ifs, line))
    {
        if (!head)
        {
            head = new player;
            cur = head;
        }
        else
        {
            cur->next = new player;
            cur = cur->next;
        }
        istringstream is(line);

        getline(is, cur->name, ',');
        getline(is, cur->password, ',');
        string point = "";
        getline(is, point);
        cur->point = stoi(point);

    }

    ifs.close();
}

void writeLeaderBoard(player* head, ofstream& ofs, const string& filename)
{
    ofs.open(filename);
    if (!ofs)
    {
        goToXY(50, 17);
        cout << "Error when opening file player info";
        return;
    }
    while (head)
    {
        ofs << head->name << "," << head->password << "," << head->point;
        ofs << endl;
        head = head->next;
    }
    ofs.close();
}

bool check_highest_point(player* p, int point)  //save the highest point of the player
{
    if (p->point < point)
    {
        p->point = point;
        return true;
    }
    return false;
}

void input_player_in4(string& username, string& password)
{
    goToXY(60, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "Enter your username: ";
    cin >> username;
    goToXY(60, 19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "Enter your password: ";
    cin >> password;
}

player* check_name(player* head, string name) //check name and return the node of that player (if the player is already exists)
{
    if (!head)
        return nullptr;
    while (head)
    {
        if (head->name == name)
            return head;
        head = head->next;
    }
    return nullptr;
}

bool check_password(player* p, string password)
{
    if (p->password == password)
        return true;
    return false;
}
