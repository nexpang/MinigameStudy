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

char ShowMap[20][21] =
{
	"++++++++++++++++++++",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"++++++++++++++++++++"
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
int _x[10], _y[10];

void randMap() {
	bool isSame = false;
	for (int i = 0; i < 10; i++)
	{
		do {
			_x[i] = rand() % 18 + 1;
			_y[i] = rand() % 18 + 1;
			for (int j = 0; j < 10; j++)
			{
				if (i != j) {
					if (_x[i] == _x[j] && _y[j] == _y[i])
					{
						isSame = true;
					}
					else
					{
						isSame = false;
					}
				}
			}
		} while (isSame);

		for (int i = 0; i < 10; i++)
		{
			ShowMap[_y[i]][_x[i]] = '+';
		}
	}
}
void displayScreen()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			gotoXY(x, y);
			_putch(ShowMap[y][x]);
		}
	}

	gotoXY(CurrentX, CurrentY);
	_putch('O');
	gotoXY(22, 19);
	cout << "Z.Áö·Ú";
	gotoXY(30, 19);
	cout << "A.ÆøÅº";
	gotoXY(38, 19);
	cout << "Q.Á¾·á";
}

void move(int dir)
{
	int dir_x = 0, dir_y = 0;
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
	if (ShowMap[CurrentY + dir_y][CurrentX + dir_x] != '+')
	{
		if (ShowMap[CurrentY + dir_y][CurrentX + dir_x] == ' ') {
			if (dir_x < 0) {
				CurrentX = 18;
			}else if (dir_x > 0) {
				CurrentX = 1;
			}
			else if (dir_y < 0) {
				CurrentY = 18;
			}
			else if (dir_y > 0) {
				CurrentY = 1;
			}
		}
		else {
			CurrentX += dir_x;
			CurrentY += dir_y;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int ch;
	CurrentX = CurrentY = 1;

	randMap();

	while (true)
	{
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
			if (ch == 'q')
			{
				exit(0);
			}
			else if (ch == 'z')
			{
				ShowMap[CurrentY][CurrentX] = 'X';
			}
			else if (ch == 'a')
			{
				if (ShowMap[CurrentY + 1][CurrentX] == '+' && CurrentY != 18)
				{
					ShowMap[CurrentY + 1][CurrentX] = '.';
				}
				if (ShowMap[CurrentY][CurrentX + 1] == '+' && CurrentX != 18)
				{
					ShowMap[CurrentY][CurrentX + 1] = '.';
				}
				if (ShowMap[CurrentY - 1][CurrentX] == '+' && CurrentY != 1)
				{
					ShowMap[CurrentY - 1][CurrentX] = '.';
				}
				if (ShowMap[CurrentY][CurrentX - 1] == '+' && CurrentX != 1)
				{
					ShowMap[CurrentY][CurrentX - 1] = '.';
				}
			}
			else if (ch == 'b')
			{
				if (ShowMap[CurrentY + 1][CurrentX] == '+' && CurrentY == 18)
				{
					ShowMap[CurrentY + 1][CurrentX] = ' ';
					ShowMap[0][CurrentX] = ' ';
				}
				if (ShowMap[CurrentY][CurrentX + 1] == '+' && CurrentX == 18)
				{
					ShowMap[CurrentY][CurrentX + 1] = ' ';
					ShowMap[CurrentY][0] = ' ';
				}
				if (ShowMap[CurrentY - 1][CurrentX] == '+' && CurrentY == 1)
				{
					ShowMap[CurrentY - 1][CurrentX] = ' ';
					ShowMap[19][CurrentX] = ' ';
				}
				if (ShowMap[CurrentY][CurrentX - 1] == '+' && CurrentX == 1)
				{
					ShowMap[CurrentY][CurrentX - 1] = ' ';
					ShowMap[CurrentY][19] = ' ';
				}
			}
		}
	}
	return 0;
}