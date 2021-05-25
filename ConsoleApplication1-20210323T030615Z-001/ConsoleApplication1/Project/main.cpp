#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <vector>

#include "Console.h"
#include "GameManager.h"
#include "CPlayer.h"
#include "CEnemy.h"

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
		else if (key == 107) {//왼쪽
			p->Move(-2);
		}
		else if(key == 109) {//오른쪽
			p->Move(2);
		}

		if (rand() % 100 < 10) {
			CEnemy unit;
			unit.setEnemy(-1, gm->getEnemyColorArr(), gm->getTeamColorArr());

			units.push_back(unit);
		}


		gm->drawDisplay();
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
		
		// 충돌
		for (int i = 0; i < (int)units.size(); i++)
		{
			if (units[i].checkEnd()) {
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

		Sleep(1000 / 20);
		clrscr();
	}
	return 0;
}