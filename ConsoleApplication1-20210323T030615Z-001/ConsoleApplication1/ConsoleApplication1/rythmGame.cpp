#include <iostream>
#include <time.h>
#include <conio.h>

#include "Console.h"
#include "CNote.h"

using namespace std;

void drawScreen()
{
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "  1 2 3 4 5 6 7  " << endl;

	gotoXY(1, 10);
	setTextColor(1);
	cout << "---------------";
	setTextColor(15);
}

int getKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

int main()
{
	srand((unsigned)time(NULL));

	CNote* note = new CNote();

	bool isKeydown = false;
	char ch;

	note->initNote();

	while (1)
	{
		ch = getKeyDown();
		if (ch >= '1' && ch <= '7')
		{
			isKeydown = true;
		}
		drawScreen();
		note->drawNote();

		gotoXY(16, 12);

		if (isKeydown) {
			note->checkCorrect(ch - '0');
			isKeydown = false;
		}

		note->downNote();

		note->checkEnd();

		Sleep(50);
		clrscr();
	}

	return 0;
}