#include "CBullet.h"
#include "Console.h"

#include <iostream>

using namespace std;

void CBullet::setBullet(int _x, int _y, bool _isEnemy) {
	x = _x;
	y = _y;
	isEnemy = _isEnemy;
}
void CBullet::darwBullet() {
	gotoXY(x, y);

	setTextColor(2);
	cout << "¡Ü";
	setTextColor(15);

	if (!isEnemy) {
		y--;
	}
	else {
		y += 2;
	}
}

bool CBullet::checkEnd() {
	if (!isEnemy) {
		if (y < 0)
		{
			return true;
		}
	}
	else {
		if (y > 38)
		{
			return true;
		}
	}
	return false;
}
bool CBullet::checkCollision(int _x, int _y) {
	if (!isEnemy) {
		if (x == _x && (y == _y || y - 1 == _y)) {
			return true;
		}

		return false;
	}
	else {
		if (x == _x && (y == _y || y + 1 == _y)) {
			return true;
		}

		return false;
	}
}

int CBullet::getX()
{
	return x;
}
int CBullet::getY()
{
	return y;
}