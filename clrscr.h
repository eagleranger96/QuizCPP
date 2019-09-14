#ifndef _CLRSCR_H
#define _CLRSCR_H
#include <windows.h>

void clrscr()
{
    DWORD n;
    DWORD size;
    COORD coord = {0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h;
    h = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( h, &csbi );
    size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
    GetConsoleScreenBufferInfo ( h, &csbi );
    FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
    SetConsoleCursorPosition ( h, coord );
}

#endif