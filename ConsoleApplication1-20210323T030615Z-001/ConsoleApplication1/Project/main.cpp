#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>

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
GameManager* gm;
CPlayer* p;
int key;
int resetTime;
int currentTime;

int getKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

void initGame()
{
	currentTime = 0;
	resetTime = 150;
	units.clear();
	myBulletes.clear();
	setTextColor(15);

	gm = new GameManager();
	p = new CPlayer();

	gm->startGame();
	gm->setColors();
	p->SetPlayer();
}

void saveHighscore();

void checkDirection(CPlayer*);
void checkCollision();

int main() {
	srand((unsigned)time(NULL));
	setConsoleView();

	initGame();

	while (1) {
		key = tolower(getKeyDown());
		if (key == 'q') {
			saveHighscore();
			exit(0);
		}
		else if (key == 'r') {
			initGame();
		}
		else if (key == 'a') {// 디버그 코드
			//gm->setColors();
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
		checkCollision();
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

		if (gm->checkGameOver())
		{
			//파일 입력
			string sScore = to_string(gm->getScore());
			saveHighscore();

			clrscr();
			gotoXY(12, 10);
			cout << "GAME OVER";
			gotoXY(12, 11);
			cout << "SCORE: "+sScore;
			gotoXY(10, 12);
			cout << "RESTART: R, QUIT: Q";
			while (1)
			{
				int k;
				k = tolower(getKeyDown());
				if (k == 'q') {
					exit(0);
				}
				else if (k == 'r') {
					initGame();
					break;
				}
			}
		}
		resetTime = 150-(gm->getResetSpeed()*10);
		currentTime++;
		if (currentTime >= resetTime)
		{
			currentTime = 0;
			gm->setColors();
		}
		Sleep(1000 / 10);
		clrscr();
	}
	return 0;
}

void saveHighscore()
{
	string sScore = to_string(gm->getScore());
	if (gm->checkHighscore())
	{
		ofstream writeFile;
		writeFile.open("highscore.txt");
		if (writeFile.is_open())
		{
			writeFile << sScore;
		}
	}
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
void checkCollision() {
	bool bCollision;
	do {
		bCollision = false;
		for (int i = 0; i < (int)units.size(); i++)
		{
			for (int j = 0; j < (int)myBulletes.size(); j++)
			{
				if (units[i].checkBullet(myBulletes[j].getX(), myBulletes[j].getY())) {
					if (units[i].getisEnemy())
					{
						gm->setResetSpeed();
					}
					else
					{
						gm->onDamage();
					}
					units.erase(units.begin() + i);
					myBulletes.erase(myBulletes.begin() + j);

					bCollision = true;
					break;
				}
			}
			if (bCollision)
				break;
		}
	} while (bCollision);
}