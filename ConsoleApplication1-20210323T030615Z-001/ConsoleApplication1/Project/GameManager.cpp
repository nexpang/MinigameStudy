#include "GameManager.h"
#include "Console.h"
#include "Cplayer.h"
#include <stdlib.h>
#include <iostream>

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


void GameManager::showColors(int x, int y) {
	gotoXY(x, y);
	std::cout << "ENEMY:";
	for (int i = 0; i < sizeof(enemyColor)/sizeof(int); i++)
	{
		setTextColor(enemyColor[i]);
		std::cout << "■";
	}
	setTextColor(15);
	gotoXY(x, y+1);
	std::cout << "TEAM :";
	for (int i = 0; i < sizeof(teamColor) / sizeof(int); i++)
	{
		setTextColor(teamColor[i]);
		std::cout << "■";
	}
	setTextColor(15);
	gotoXY(x, y + 3);
	std::cout << "스코어: "<<0;
	gotoXY(x, y + 4);
	std::cout << "종료: Q";
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
	showColors(30, 1);
	gotoXY(30, 26);
}


int GameManager::getEnemyColorArr() {
	return enemyColor[rand() % 3];
}

int GameManager::getTeamColorArr() {
	return teamColor[rand() % 3];
}