#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <vector>

#include "Console.h"
#include "GameManager.h"
#include "CPlayer.h"
#include "CEnemy.h"

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

using namespace std;

vector<CEnemy> units, myBulletes;

int getKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

void checkDirection(CPlayer*);

int main() {
	srand((unsigned)time(NULL));
	setConsoleView();

	units.clear();
	myBulletes.clear();

	for (int i = 1; i < 15; i++)
	{
		setTextColor(i);
		cout << i <<" ";
	}
	setTextColor(15);
	cout << endl;


	GameManager* gm = new GameManager();
	CPlayer *p = new CPlayer();
	int key;

	gm->startGame();
	gm->setColors();
	p->SetPlayer();
	while (1) {
		key = tolower(getKeyDown());
		if (key == 'r') {
			gm->setColors();
		}
		else if(key == 'q') {
			exit(0);
		}
		else if (key == ' ') {
			CEnemy bullet;
			bullet.setEnemy(p->GetX(), gm->getEnemyColorArr(), gm->getTeamColorArr());

			myBulletes.push_back(bullet);
		}
		else if (key == 0xE0)
		{
			checkDirection(p);
		}if (key == 107) {//왼쪽
			p->Move(-1);
		}
		else if(key == 109) {//오른쪽
			p->Move(1);
		}

		if (rand() % 100 < 10) {
			CEnemy unit;
			unit.setEnemy(-1, gm->getEnemyColorArr(), gm->getTeamColorArr());

			units.push_back(unit);
		}


		gm->drawDisplay();
		gm->drawWall();
		for (int i = 0; i < (int)units.size(); i++)
		{
			units[i].moveEnemy();
			units[i].drawEnemy();
		}
		for (int i = 0; i < (int)myBulletes.size(); i++)
		{
			myBulletes[i].moveEnemy();
			myBulletes[i].drawEnemy();
		}
		p->ShowPlayer();
		gm->showUI();
		// 충돌
		for (int i = 0; i < (int)units.size(); i++)
		{
			if (units[i].checkEnd()) {
				gm->DestroyWall(units[i].getX(), units[i].getisEnemy());
				units.erase(units.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < (int)myBulletes.size(); i++)
		{
			if (myBulletes[i].checkEnd()) {
				myBulletes.erase(myBulletes.begin() + i);
				i--;
			}
		}

		Sleep(1000 / 10);
		clrscr();
	}
	return 0;
}

void checkDirection(CPlayer* p)
{
	int key = _getch();

	switch (key)
	{
	case UP:
		break;
	case DOWN:
		break;
	case LEFT:
		if (p->GetX() > 0)
		{
			p->Move(-1);
		}
		break;
	case RIGHT:
		if (p->GetX() < 19)
		{
			p->Move(1);
		}
		break;

	default:
		break;
	}
}