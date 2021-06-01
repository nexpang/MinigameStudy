#pragma once
class GameManager
{
private:
	int score;
	int hp;

	int enemyColor[3] = {4,5,6};
	int teamColor[3] = {1,2,3};

	int wall[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
public:
	void startGame();

	void setColors();

	void DestroyWall(int, bool);

	void showUI();
	void drawWall();
	void drawDisplay();
	
	int getEnemyColorArr();
	int getTeamColorArr();
};

