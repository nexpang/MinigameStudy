#pragma once
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

	bool checkEnd();
};

