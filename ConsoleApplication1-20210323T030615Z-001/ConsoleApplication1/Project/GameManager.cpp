#include "GameManager.h"
#include "Console.h"
#include "Cplayer.h"
#include <stdlib.h>
#include <iostream>

void GameManager::startGame() {
	score = 0;
	hp = 3;
}


void GameManager::setColors() {
	int arr[14] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };

	for (int i = 0; i < 3; i++)
	{
		int r = 0;
		int r1 = 0;
		while (1) {
			r1 = rand() % 14;
			r = arr[r1];
			if (r != 0) {
				break;
			}
		}
		enemyColor[i] = r;
		arr[r1] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		int r = 0;
		int r1 = 0;
		while (1) {
			r1 = rand() % 14;
			r = arr[r1];
			if (r != 0) {
				break;
			}
		}
		teamColor[i] = r;
		arr[r1] = 0;
	}
}


void GameManager::DestroyWall(int x, bool isEnemy) {
	if (isEnemy) {
		if (wall[x] == 0) {
			hp--;
		}
		else
			wall[x] = 0;
	}
	else {
		wall[x] = 1;
		score++;
	}
}



void GameManager::showUI() {
	int x = 15;
	gotoXY(x, 0);
	std::cout << "ENEMY:";
	for (int i = 0; i < sizeof(enemyColor)/sizeof(int); i++)
	{
		setTextColor(enemyColor[i]);
		std::cout << "бс";
	}
	setTextColor(15);
	gotoXY(x, 1);
	std::cout << "TEAM :";
	for (int i = 0; i < sizeof(teamColor) / sizeof(int); i++)
	{
		setTextColor(teamColor[i]);
		std::cout << "бс";
	}
	setTextColor(15);
	gotoXY(x, 3);
	std::cout << "HP	: "<< hp;
	gotoXY(x, 4);
	std::cout << "SOCRE	: " << score;
	gotoXY(x, 5);
	std::cout << "EXIT	: Q";

	gotoXY(x, 8);
	std::cout << "HELP";
	gotoXY(x, 9);
	std::cout << "ATTACK	: SPACE";
	gotoXY(x, 10);
	std::cout << "MOVE	: RIGHT, LEFT ARROW";

	gotoXY(x, 12);
	std::cout << "ENEMY	: destroy wall, kill them!";
	gotoXY(x, 13);
	std::cout << "TEAM	: repair wall, don't Shoot!";
}

void GameManager::drawDisplay() {
	gotoXY(0, 0);
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	std::cout << "|                            |" << std::endl;
	gotoXY(29, 26);
}void GameManager::drawWall() {
	gotoXY(0, 26);
	for (int i = 0; i < sizeof(wall)/sizeof(int); i++)
	{
		if (wall[i] == 1) {
			std::cout << "б┘";
		}
		else {
			std::cout << "  ";
		}
	}
	gotoXY(32, 26);
}


int GameManager::getEnemyColorArr() {
	return enemyColor[rand() % 3];
}

int GameManager::getTeamColorArr() {
	return teamColor[rand() % 3];
}