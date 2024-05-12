#pragma once

#include<Windows.h>
// https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console
void goToXY(int, int);			// set cursor position
void setFullScreen();			// make the console open in full screen mode
void setCursor(bool);			// hide the cursor
void hideScrollBar();			// hide the scroll bar
void initWindow();				// initialized the console window
