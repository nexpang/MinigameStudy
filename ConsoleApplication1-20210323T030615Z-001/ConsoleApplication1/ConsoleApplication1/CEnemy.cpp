#include "CEnemy.h"
#include "Console.h"

#include<iostream>

using namespace std;

void CEnemy::setEnemy() {
	x = rand() % 20;
	y = 0;
}

void CEnemy::drawEnemy() {
	gotoXY(x, y);
	setTextColor(4);
	cout << "¡å";
	setTextColor(15);

	y++;
}

bool CEnemy::checkEnd() {
	if (y > 39)
	{
		return true;
	}
	return false;
}

int CEnemy::getX() {
	return x;
}
int CEnemy::getY() {
	return y;
}