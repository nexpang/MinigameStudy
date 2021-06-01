#pragma once
class CBullet
{
private:
	int x;
	int y;

	bool isEnemy;
public:
	void setBullet(int _x, int _y, bool _isEnemy = false);
	void darwBullet();

	bool checkEnd();

	bool checkCollision(int _x, int _y);

	int getX();
	int getY();
};

