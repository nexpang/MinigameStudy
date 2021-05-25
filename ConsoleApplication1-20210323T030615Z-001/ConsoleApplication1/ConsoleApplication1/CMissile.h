#pragma once

class CMissile
{
public:
	void setMissile(int);

	int getX();
	int getY();

	void moveMissile();
	void drawMissile();

	bool checkEnd();
private:
	int x;
	int y;

	bool bMoveLeft;
};