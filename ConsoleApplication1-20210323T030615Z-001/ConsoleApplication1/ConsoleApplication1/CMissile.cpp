#include<iostream>

#include"CMissile.h"
#include"console.h"

using namespace std;

void CMissile::setMissile(int _y) {
	if (_y == -1) {
		x = 59;
		y = rand() % 20;
		bMoveLeft = true;
	}
	else {
		x = 3;
		y = _y;
		bMoveLeft = false;
	}
}

int CMissile::getX() {
	return x;
}
int CMissile::getY() {
	return y;
}


void CMissile::moveMissile() {
	if (bMoveLeft)
		x--;
	else
		x++;
}
void CMissile::drawMissile() {
	if (x < 1 || x>58) return;

	gotoXY(x, y);
	if (bMoveLeft) {
		setTextColor(4);
		cout << "¢¸";
	}
	else {
		setTextColor(1);
		cout << "¡æ";
	}
	setTextColor(15);
	gotoXY(59, 19);
}

bool CMissile::checkEnd() {
	if (bMoveLeft) {
		if (x < 1) {
			return true;
		}
	}
	else {
		if (x > 58) {
			return true;
		}
	}
	return false;
}