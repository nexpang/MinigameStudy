#include "GameManager.h"
#include "Console.h"
#include "Cplayer.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

void GameManager::startGame() {
	std::ifstream openFile;
	std::string s;
	openFile.open("highscore.txt");
	if (openFile.is_open())
	{
		openFile >> s;
		highscore = std::stoi(s);
	}
	else
	{
		highscore = 0;
	}
	score = 0;
	hp = 3;
	gameResetSpeed = 0;
	maxResetSpeed = 10;
	highChange = false;
}

bool GameManager::checkGameOver() {
	if (hp <= 0)
	{
		return true;
	}
	return false;
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
void GameManager::setResetSpeed() {
	int before = score;
	score++;
	if (score / 10 > before / 10) {
		gameResetSpeed++;
		if (gameResetSpeed > maxResetSpeed)
			gameResetSpeed = maxResetSpeed;
	}
	if (score > highscore)
	{
		highscore = score;
		highChange = true;
	}
}

void GameManager::onDamage() {
	hp--;
}
void GameManager::DestroyWall(int x, bool isEnemy) {
	if (isEnemy) {
		if (wall[x] == 0) {
			onDamage();
		}
		else
			wall[x] = 0;
	}
	else {
		wall[x] = 1;
		setResetSpeed();
	}
}



void GameManager::showUI() {
	int x = 15;
	int y = 3;
	char title[14] = "COLOR SHOOTER";
	setTextColor(15);
	gotoXY(x, 0);
	std::cout << "-------------------";
	gotoXY(x, 1);
	std::cout << "|  ";
	for (int i=0; i < sizeof(title) / sizeof(char); i++)
	{
		setTextColor(i+1);
		std::cout << title[i];
	}
	setTextColor(15);
	std::cout << "  |";
	gotoXY(x, 2);
	std::cout << "-------------------";
	gotoXY(x, y);
	setTextColor(15);
	std::cout << "ENEMY:";
	for (int i = 0; i < sizeof(enemyColor)/sizeof(int); i++)
	{
		setTextColor(enemyColor[i]);
		std::cout << "бс";
	}
	setTextColor(15);
	gotoXY(x, y+1);
	std::cout << "TEAM :";
	for (int i = 0; i < sizeof(teamColor) / sizeof(int); i++)
	{
		setTextColor(teamColor[i]);
		std::cout << "бс";
	}
	setTextColor(15);
	gotoXY(x, y+3);
	std::cout << "HP	: "<< hp;
	gotoXY(x, y+4);
	std::cout << "SOCRE	: " << score;
	gotoXY(x, y+5);
	std::cout << "HIGHSOCRE	: " << highscore;
	gotoXY(x, y+6);
	std::cout << "EXIT	: Q";

	gotoXY(x, y+8);
	std::cout << "HELP";
	gotoXY(x, y+9);
	std::cout << "ATTACK	: SPACE";
	gotoXY(x, y+10);
	std::cout << "MOVE	: RIGHT, LEFT ARROW";

	gotoXY(x, y+12);
	std::cout << "ENEMY	: destroy wall, kill them!";
	gotoXY(x, y+13);
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
}
void GameManager::drawWall() {
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


bool GameManager::checkHighscore() {
	return highChange;
}


int GameManager::getScore() {
	return score;
}
int GameManager::getResetSpeed() {
	return gameResetSpeed;
}
int GameManager::getEnemyColorArr() {
	return enemyColor[rand() % 3];
}

int GameManager::getTeamColorArr() {
	return teamColor[rand() % 3];
}