#pragma once
class GameManager
{
private:
	int enemyColor[3] = {4,5,6};
	int teamColor[3] = {1,2,3};
public:
	void setColors();

	void showColors(int x, int y);
	void drawDisplay();
	
	int getEnemyColorArr();
	int getTeamColorArr();
};

