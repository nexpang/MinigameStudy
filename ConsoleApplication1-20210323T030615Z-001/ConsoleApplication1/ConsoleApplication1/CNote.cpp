#include <iostream>

#include "CNote.h"
#include "Console.h"

using namespace std;

void CNote::initNote()
{
	index = rand() % 7 + 1;
	x = index * 2;
	y = 0;
}

void CNote::drawNote()
{
	gotoXY(x, y);
	setTextColor(14);
	cout << "Q";
	setTextColor(15);
}

void CNote::downNote()
{
	y++;
}

void CNote::checkCorrect(int key)
{
	if (y >= 10 && y <= 12)
	{
		if (key == index)
			playSound();

		initNote();
	}
}

void CNote::checkEnd()
{
	if (y == 12)
	{
		//playSound();

		initNote();
	}
}

void CNote::playSound()
{
	int data[7] = { 523, 587, 659,698,784,880,988 };

	beep(data[index - 1], 500);
}