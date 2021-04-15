#include <iostream>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int CurrentX, CurrentY;
char BackGrdMap[10][16];
char ShowMap[10][16] =
{
	"++++++++++++++",
	"++++++++++++++",
	"++++&  +++++++",
	"++++ 00+++++++",
	"++++ 0 +++.+++",
	"++++++ +++.+++",
	"++++++    .+++",
	"+++++   +  +++",
	"+++++   ++++++",
	"++++++++++++++",
};

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

bool isinit = true;
int beforeX = 0;
int beforeY = 0;
int TotalMove = 0;
void displayScreen()
{
	if (isinit) {
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 15; x++)
			{
				gotoXY(x, y);
				_putch(BackGrdMap[y][x]);
			}
		}
		gotoXY(CurrentX, CurrentY);
		_putch('&');
		gotoXY(20, 2);
		cout << "PushPush";
		gotoXY(20, 4);
		cout << "Q.종료";
		isinit = false;
	}
	else {
		if (ShowMap[beforeY][beforeX] == '.') {
			gotoXY(beforeX, beforeY);
			_putch('.');
		}
		else {
			gotoXY(beforeX, beforeY);
			_putch(' ');
		}
	}
	gotoXY(CurrentX, CurrentY);
	_putch('&');
	gotoXY(20, 6);
	cout << "횟수 : " << TotalMove;
}

void move(int dir)
{
	int dir_x = 0, dir_y = 0;
	beforeX = CurrentX;
	beforeY = CurrentY;
	switch (dir)
	{
	case LEFT:
		dir_x = -1;
		break;
	case RIGHT:
		dir_x = 1;
		break;
	case UP:
		dir_y = -1;
		break;
	case DOWN:
		dir_y = 1;
		break;
	default:
		break;
	}
	if (BackGrdMap[CurrentY + dir_y][CurrentX + dir_x] != '+')
	{
		if (BackGrdMap[CurrentY + dir_y][CurrentX + dir_x] == '0') {
			if (BackGrdMap[CurrentY + (dir_y * 2)][CurrentX + (dir_x * 2)] == ' ' || BackGrdMap[CurrentY + (dir_y * 2)][CurrentX + (dir_x * 2)] == '.')
			{
				if (ShowMap[CurrentY + dir_y][CurrentX + dir_x] == '.') {
					BackGrdMap[CurrentY + dir_y][CurrentX + dir_x] = '.';
				}
				else {
					BackGrdMap[CurrentY + (dir_y)][CurrentX + (dir_x)] = ' ';
				}
				BackGrdMap[CurrentY + (dir_y * 2)][CurrentX + (dir_x * 2)] = '0';
				gotoXY(CurrentX + (dir_x * 2), CurrentY + (dir_y * 2));
				_putch('0');
			}
			else {
				return;
			}
		}
		CurrentX += dir_x;
		CurrentY += dir_y;
		TotalMove++;
	}
}

bool checkEnd() {
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (ShowMap[y][x] == '.' && BackGrdMap[y][x] != '0') {
				return false;
			}
		}
	}
	return true;
}

int main()
{
	srand((unsigned)time(NULL));
	int ch;
	while (true)
	{
		TotalMove = 0;
		memcpy(BackGrdMap, ShowMap, sizeof(BackGrdMap));
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 15; x++) {
				if (BackGrdMap[y][x] == '&') {
					CurrentX = x;
					CurrentY = y;
					BackGrdMap[y][x] = ' ';
				}
			}
		}
		while (true) {
			displayScreen();
			ch = _getch();
			if (ch == 0xE0 || ch == 0)
			{
				ch = _getch();
				switch (ch)
				{
				case LEFT:
				case RIGHT:
				case UP:
				case DOWN:
					move(ch);
					break;
				default:
					break;
				}
			}
			else
			{
				ch = tolower(ch);
				if (ch == 'r')
				{
					isinit = true;
					break;
				}
				if (ch == 'q')
				{
					exit(0);
				}
			}
			if (checkEnd()) {
				system("cls");
				gotoXY(10, 4);
				cout << "끝";
				_getch();
				exit(0);
				break;
			}
		}
	}
	return 0;
}