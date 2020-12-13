#pragma once
#include<Windows.h>
#include<iostream>
using namespace std;

static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
static void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}



static void change_color(int color_id)
{
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, color_id);

}
static void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
    if (size == 0)
    {
        size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

