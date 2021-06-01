#include <Windows.h>
#include "Console.h"

void setConsoleView()
{
	system("mode con:cols=70 lines=30");
	system("title COLOR SHOOTER");
}

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x*2;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clrscr()
{
	system("cls");
}

void beep(int tone, int delay) {
	Beep(tone, delay);
}