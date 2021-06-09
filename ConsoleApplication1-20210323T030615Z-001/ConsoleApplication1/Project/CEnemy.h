#pragma once
#include <vector>

class CEnemy
{
private:
	int x;
	int y;
	int color;

	bool isEnemy;
	bool bMoveDown;
public:
	void setEnemy(int, int, int);

	void moveEnemy();
	void drawEnemy();

	int getX();
	int getY();
	bool getisEnemy();

	bool checkBullet(int x, int y);
	bool checkEnd();
};

