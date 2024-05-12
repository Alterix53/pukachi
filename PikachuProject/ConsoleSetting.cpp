#include "ConsoleSetting.h"

// function to set the cursor go to that position on the monitor
void goToXY(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = x;           // x-axis coordinate
    cursorPosition.Y = y;           // y-axis coordinate
    SetConsoleCursorPosition(console, cursorPosition); // set cursor position at the above coordinate
}

void setCursor(bool visible) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;    // = 0 -> hide cursor
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

// function to set the console window into full screen mode: 
// ref:  Nguyen Hieu Thuan - 23127125
void setFullScreen() {
    HWND Hwnd = GetForegroundWindow();

    // Resolution of the game
    int x = 1536;
    int y = 864;

    // Make the console get to the center of the screen
    int pos_x = abs(GetSystemMetrics(SM_CXSCREEN) - x) / 2;
    int pos_y = abs(GetSystemMetrics(SM_CYSCREEN) - y) / 2;

    // Avoid resize the wrong console
    UpdateWindow(GetParent(Hwnd));

    // Setting the console to the appropriate resolution
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    MoveWindow(Hwnd, pos_x, pos_y, x, y, TRUE);

}

// function to hide scroll bar
void hideScrollBar() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);

    COORD new_screen_buffer_size;

    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;

    SetConsoleScreenBufferSize(console, new_screen_buffer_size);
}

void initWindow() {
    setFullScreen();    // set full screen
    hideScrollBar();    // hide scroll bar (unnecessary, as all the game function fit in the console window)
    setCursor(0);       // stop showing the cursor (unnecessary in the game)
}