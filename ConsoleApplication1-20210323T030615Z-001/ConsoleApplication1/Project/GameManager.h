#pragma once
class GameManager
{
private:
	int score;
	int highscore;
	int hp;
	int gameResetSpeed;
	int maxResetSpeed;
	bool highChange;

	int enemyColor[3] = {4,5,6};
	int teamColor[3] = {1,2,3};

	int wall[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
public:
	void startGame();
	bool checkGameOver();

	void setColors();
	void setResetSpeed();

	void onDamage();
	void DestroyWall(int, bool);

	void showUI();
	void drawWall();
	void drawDisplay();
	
	bool checkHighscore();

	int getScore();
	int getResetSpeed();
	int getEnemyColorArr();
	int getTeamColorArr();
};

