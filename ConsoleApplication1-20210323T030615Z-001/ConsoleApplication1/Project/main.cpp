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

vector<CEnemy> units, myBulletes; // 게임내의 유닛과 총알을 저장할 vector
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
	CSound::Init(); // 사운드 세팅

	currentTime = 0;
	resetTime = 150;
	units.clear();
	myBulletes.clear();
	setTextColor(15);

	gm = new GameManager(); // 게임메니져 객체 생성 게임의 스코어, 벽, hp 등 거의 모든것을 책임짐
	p = new CPlayer(); // 플레이어 객체 생성 플레이어의 이동 등을 책임짐

	gm->startGame(); //게임 시작
	gm->setColors(); //맨처음 적, 아군 색지정
	p->SetPlayer(); // 플레이어 처음위치로 이동
}

void saveHighscore();

void checkDirection(CPlayer*);
void checkCollision();

int main() {
	srand((unsigned)time(NULL));
	setConsoleView();

	initGame(); // 게임에 필요한 변수 초기화 및 세팅

	CSound* m_bgm = new CSound("sounds/m_bgm.mp3", true);
	CSound* shoot = new CSound("sounds/shoot.mp3", false);
	CSound* wall = new CSound("sounds/wall.mp3", false);
	CSound* changeColor = new CSound("sounds/changeColor.mp3", false);
	m_bgm->play();

	while (1) {
		key = tolower(getKeyDown()); //키값을 받아옴
		if (key == 'q') { // 나가는 키
			saveHighscore();
			delete m_bgm;
			delete wall;
			delete shoot;
			delete changeColor;
			CSound::Release();
			exit(0);
		}
		else if (key == 'r') { // 재시작 키
			initGame();
		}
		//else if (key == 'a') {// 디버그 코드
			//gm->setColors();
		//}
		else if (key == 'w') { // 소리키우기 키
			m_bgm->volumeUp();

			wall->volumeUp();
			shoot->volumeUp();
			changeColor->volumeUp();
		}
		else if (key == 's') { // 소리줄이기 키
			m_bgm->volumeDown();

			wall->volumeDown();
			shoot->volumeDown();
			changeColor->volumeDown();
		}
		else if (key == ' ') { // 총알발사 키
			CEnemy bullet;
			bullet.setEnemy(p->GetX(), gm->getEnemyColorArr(), gm->getTeamColorArr());

			myBulletes.push_back(bullet);
			shoot->play();
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

		if (rand() % 100 < 10) { //10퍼센트로 적 또는 아군생성
			CEnemy unit;
			unit.setEnemy(-1, gm->getEnemyColorArr(), gm->getTeamColorArr()); // 적 또는 아군으로 설정

			units.push_back(unit);
		}


		gm->drawDisplay(); // 맵그리기
		gm->drawWall(); // 벽 그리기
		for (int i = 0; i < (int)units.size(); i++) // 적과 아군 움직이고 그림
		{
			units[i].moveEnemy();
			units[i].drawEnemy();
		}
		for (int i = 0; i < (int)myBulletes.size(); i++) // 자신의 총알 움직이고 그림
		{
			myBulletes[i].moveEnemy();
			myBulletes[i].drawEnemy();
		}
		p->ShowPlayer(); // 플레이어 그림
		gm->showUI();// UI그리기
		// 충돌
		checkCollision(); // 총알이 적과 충돌했으면 둘다 없애는 함수
		for (int i = 0; i < (int)units.size(); i++) 
		{
			if (units[i].checkEnd()) { // 적과 아군들 중 끝에 도달한 것이 있으면 없애고 벽부수기, 고치기, 데미지 입기 중 실행
				gm->DestroyWall(units[i].getX(), units[i].getisEnemy());
				units.erase(units.begin() + i);
				i--;

				wall->play();
			}
		}
		for (int i = 0; i < (int)myBulletes.size(); i++) // 자신의 총알이 마지막 까지가면 지우기
		{
			if (myBulletes[i].checkEnd()) {
				myBulletes.erase(myBulletes.begin() + i);
				i--;
			}
		}

		if (gm->checkGameOver()) // 게임오버가 됬으면 스코어를 비교해서 최대스코어를 저장 및 게임오버 화면 띄우기
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
		resetTime = 150-(gm->getResetSpeed()*10); // 적, 아군 색이 바뀌는 시간이 됬는지 확인 및 바꾸기
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