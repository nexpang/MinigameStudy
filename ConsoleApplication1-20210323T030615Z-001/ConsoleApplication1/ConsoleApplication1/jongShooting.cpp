//20303 김경혁
//과제구현완료 - 적 총알과 자신 충돌시 게임 종료
#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>

#include "Console.h"
#include "CEnemy.h"
#include "CBullet.h"

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

using namespace std;

int x, y, myBulletCount;

vector<CEnemy> enemies;
vector<CBullet> myBullets, enemiesBullets;

void setConsoleView()
{
	system("mode con:cols=40 lines=40");
	system("title SHOOTING GAME #2");
}

void initData()
{
	srand((unsigned)time(NULL));

	x = 10;
	y = 38;

	myBulletCount = 0;

	enemies.clear();
	myBullets.clear();
}

void checkDirection()
{
	int key = _getch();

	switch (key)
	{
	case UP:
		if (y > 0)
		{
			y--;
		}
		break;
	case DOWN:
		if (y < 38)
		{
			y++;
		}
		break;
	case LEFT:
		if (x > 0)
		{
			x--;
		}
		break;
	case RIGHT:
		if (x < 19)
		{
			x++;
		}
		break;

	default:
		break;
	}
}

void checkCollision() {
	bool bCollision1;
	bool bCollision2;
	do {
		bCollision1 = false;

		for (int i = 0; i < (int)myBullets.size(); i++)
		{
			for (int j = 0; j < (int)enemies.size(); j++)
			{
				if (myBullets[i].checkCollision(enemies[j].getX(), enemies[j].getY())) {
					myBullets.erase(myBullets.begin() + i);
					enemies.erase(enemies.begin() + j);

					bCollision1 = true;
					break;
				}
			}
			if (bCollision1)
				break;
		}
	} while (bCollision1);

	do {
		bCollision2 = false;

		for (int i = 0; i < (int)enemiesBullets.size(); i++)
		{
			for (int j = 0; j < (int)myBullets.size(); j++)
			{
				if (enemiesBullets[i].checkCollision(myBullets[j].getX(), myBullets[j].getY())) {
					enemiesBullets.erase(enemiesBullets.begin() + i);
					myBullets.erase(myBullets.begin() + j);

					bCollision2 = true;
					break;
				}
			}
			if (bCollision2)
				break;
			if (enemiesBullets[i].checkCollision(x, y)) {
				enemiesBullets.erase(enemiesBullets.begin() + i);
				exit(0);

				bCollision2 = true;
				break;
			}
		}
	} while (bCollision2);
}


void drawPlayer()
{
	gotoXY(x, y);
	cout << "▲";

	gotoXY(19, 39);
}

int main()
{
	setConsoleView();

	initData();

	while (1)
	{
		int key = getKeyDown();
		key = tolower(key);

		if (key == 0xE0)
		{
			checkDirection();
		}
		else if (key == 'a')
		{
			if (myBulletCount == 0) {
				myBulletCount = 3;
				CBullet bullet;

				bullet.setBullet(x, y);

				myBullets.push_back(bullet);
			}
		}

		if (rand() % 100 < 5) {
			CEnemy enemy;
			enemy.setEnemy();

			enemies.push_back(enemy);
		}

		for (int i = 0; i < (int)enemies.size(); i++)
		{
			if (rand() % 100 < 5) {
				CBullet bullet;
				bullet.setBullet(enemies[i].getX(), enemies[i].getY()+1, true);

				enemiesBullets.push_back(bullet);
			}
		}

		checkCollision();

		for (int i = 0; i < (int)enemies.size(); i++)
		{
			enemies[i].drawEnemy();
		}

		for (int i = 0; i < (int)myBullets.size(); i++)
		{
			myBullets[i].darwBullet();
		}
		for (int i = 0; i < (int)enemiesBullets.size(); i++)
		{
			enemiesBullets[i].darwBullet();
		}

		drawPlayer();
		for (int i = 0; i < (int)enemies.size(); i++)
		{
			if (enemies[i].checkEnd())
			{
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < (int)enemiesBullets.size(); i++)
		{
			if (enemiesBullets[i].checkEnd())
			{
				enemiesBullets.erase(enemiesBullets.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < (int)myBullets.size(); i++)
		{
			if (myBullets[i].checkEnd())
			{
				myBullets.erase(myBullets.begin() + i);
				i--;
			}
		}

		if (myBulletCount > 0)
			myBulletCount--;

		Sleep(100);
		clrscr();
	}

	return 0;
}