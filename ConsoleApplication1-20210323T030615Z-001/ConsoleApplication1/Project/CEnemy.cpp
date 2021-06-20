#include <Windows.h>
#include <iostream>

#include "CEnemy.h"
#include "Console.h"

using namespace std;

void CEnemy::setEnemy(int _x, int enemy, int team) {
	if (_x == -1) {
		x = rand() % 13 + 1;
		y = 0;

		// 팀인지 적인지 랜덤
		int r = rand() % 2;
		if (r == 0)
			isEnemy = true;
		else
			isEnemy = false;

		// 색상 설정
		if (isEnemy)
			color = enemy;
		else
			color = team;

		bMoveDown = true;
	}
	else {
		x = _x;
		y = 25;

		bMoveDown = false;
	}
}

void CEnemy::moveEnemy() {
	if (bMoveDown) {
		y++;
	}
	else {
		y--;
	}
}
void CEnemy::drawEnemy() {
	gotoXY(x, y);
	if (bMoveDown) {
		setTextColor(color);
		cout << "▼";
	}
	else {
		setTextColor(15);
		cout << "☆";
	}
	setTextColor(15);
}

int CEnemy::getX()
{
	return x;
}
int CEnemy::getY()
{
	return y;
}
bool CEnemy::getisEnemy()
{
	return isEnemy;
}

bool CEnemy::checkBullet(int x, int y) {
	if (this->x == x && (this->y == y || this->y+1 == y)) {
		return true;
	}
	return false;
}
bool CEnemy::checkEnd() {
	if (bMoveDown) {
		if (y > 24) {
			return true;
		}
	}
	else {
		if (y < 1) {
			return true;
		}
	}
	return false;
}