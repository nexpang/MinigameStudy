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
#include "CSound.h"

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

using namespace std;

vector<CEnemy> units, myBulletes; // ���ӳ��� ���ְ� �Ѿ��� ������ vector
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
	CSound::Init(); // ���� ����

	currentTime = 0;
	resetTime = 150;
	units.clear();
	myBulletes.clear();
	setTextColor(15);

	gm = new GameManager(); // ���Ӹ޴��� ��ü ���� ������ ���ھ�, ��, hp �� ���� ������ å����
	p = new CPlayer(); // �÷��̾� ��ü ���� �÷��̾��� �̵� ���� å����

	gm->startGame(); //���� ����
	gm->setColors(); //��ó�� ��, �Ʊ� ������
	p->SetPlayer(); // �÷��̾� ó����ġ�� �̵�
}

void saveHighscore();

void checkDirection(CPlayer*);
void checkCollision();

int main() {
	srand((unsigned)time(NULL));
	setConsoleView();

	initGame(); // ���ӿ� �ʿ��� ���� �ʱ�ȭ �� ����

	CSound* m_bgm = new CSound("sounds/m_bgm.mp3", true);
	CSound* shoot = new CSound("sounds/shoot.mp3", false);
	CSound* wall = new CSound("sounds/wall.mp3", false);
	CSound* changeColor = new CSound("sounds/changeColor.mp3", false);
	m_bgm->play();

	while (1) {
		key = tolower(getKeyDown()); //Ű���� �޾ƿ�
		if (key == 'q') { // ������ Ű
			saveHighscore();
			delete m_bgm;
			delete wall;
			delete shoot;
			delete changeColor;
			CSound::Release();
			exit(0);
		}
		else if (key == 'r') { // ����� Ű
			initGame();
		}
		//else if (key == 'a') {// ����� �ڵ�
			//gm->setColors();
		//}
		else if (key == 'w') { // �Ҹ�Ű��� Ű
			m_bgm->volumeUp();

			wall->volumeUp();
			shoot->volumeUp();
			changeColor->volumeUp();
		}
		else if (key == 's') { // �Ҹ����̱� Ű
			m_bgm->volumeDown();

			wall->volumeDown();
			shoot->volumeDown();
			changeColor->volumeDown();
		}
		else if (key == ' ') { // �Ѿ˹߻� Ű
			CEnemy bullet;
			bullet.setEnemy(p->GetX(), gm->getEnemyColorArr(), gm->getTeamColorArr());

			myBulletes.push_back(bullet);
			shoot->play();
		}
		else if (key == 0xE0)
		{
			checkDirection(p);
		}if (key == 107) {//����
			p->Move(-1);
		}
		else if(key == 109) {//������
			p->Move(1);
		}

		if (rand() % 100 < 10) { //10�ۼ�Ʈ�� �� �Ǵ� �Ʊ�����
			CEnemy unit;
			unit.setEnemy(-1, gm->getEnemyColorArr(), gm->getTeamColorArr()); // �� �Ǵ� �Ʊ����� ����

			units.push_back(unit);
		}


		gm->drawDisplay(); // �ʱ׸���
		gm->drawWall(); // �� �׸���
		for (int i = 0; i < (int)units.size(); i++) // ���� �Ʊ� �����̰� �׸�
		{
			units[i].moveEnemy();
			units[i].drawEnemy();
		}
		for (int i = 0; i < (int)myBulletes.size(); i++) // �ڽ��� �Ѿ� �����̰� �׸�
		{
			myBulletes[i].moveEnemy();
			myBulletes[i].drawEnemy();
		}
		p->ShowPlayer(); // �÷��̾� �׸�
		gm->showUI();// UI�׸���
		// �浹
		checkCollision(); // �Ѿ��� ���� �浹������ �Ѵ� ���ִ� �Լ�
		for (int i = 0; i < (int)units.size(); i++) 
		{
			if (units[i].checkEnd()) { // ���� �Ʊ��� �� ���� ������ ���� ������ ���ְ� ���μ���, ��ġ��, ������ �Ա� �� ����
				gm->DestroyWall(units[i].getX(), units[i].getisEnemy());
				units.erase(units.begin() + i);
				i--;

				wall->play();
			}
		}
		for (int i = 0; i < (int)myBulletes.size(); i++) // �ڽ��� �Ѿ��� ������ �������� �����
		{
			if (myBulletes[i].checkEnd()) {
				myBulletes.erase(myBulletes.begin() + i);
				i--;
			}
		}

		if (gm->checkGameOver()) // ���ӿ����� ������ ���ھ ���ؼ� �ִ뽺�ھ ���� �� ���ӿ��� ȭ�� ����
		{
			//���� �Է�
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
					delete m_bgm;
					delete wall;
					delete shoot;
					delete changeColor;
					CSound::Release();
					exit(0);
				}
				else if (k == 'r') {
					initGame();
					break;
				}
			}
		}
		resetTime = 150-(gm->getResetSpeed()*10); // ��, �Ʊ� ���� �ٲ�� �ð��� ����� Ȯ�� �� �ٲٱ�
		currentTime++;
		if (currentTime >= resetTime)
		{
			currentTime = 0;
			gm->setColors();
			changeColor->play();
		}

		m_bgm->Update();
		shoot->Update();
		wall->Update();
		changeColor->Update();

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