//20303 ±Ë∞Ê«ı
#include <iostream>
#include <time.h>
#include <vector>

#include "Console.h"
#include "CMissile.h"

using namespace std;

bool bMoveDown;
int y;

vector<CMissile> missiles, myMissiles;

void setConsoleView()
{
	system("mode con:cols=60 lines=20");
	system("title SHOOTING GAME");
}

int main() {
	srand((unsigned)time(NULL));
	bMoveDown = true;
	y = 0;

	setConsoleView();

	missiles.clear();
	myMissiles.clear();

	int keyCode;

	while (1)
	{
		keyCode = getKeyDown();
		keyCode = towlower(keyCode);

		if (keyCode == ' ') {
			CMissile myMissile;
			myMissile.setMissile(y);

			myMissiles.push_back(myMissile);
		}

		if (rand()%100<10) {
			CMissile missile;
			missile.setMissile(-1);

			missiles.push_back(missile);
		}

		for (int i = 0; i < (int)missiles.size(); i++)
		{
			missiles[i].moveMissile();
			missiles[i].drawMissile();
		}
		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			myMissiles[i].moveMissile();
			myMissiles[i].drawMissile();
		}

		gotoXY(2, y);
		cout << "¢∫";
		gotoXY(59, 19);

		if (bMoveDown)
		{
			y++;
			if (y > 19)
			{
				y = 19;
				bMoveDown = false;
			}
		}
		else
		{
			y--;
			if (y < 0)
			{
				y = 0;
				bMoveDown = true;
			}
		}

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			if (myMissiles[i].checkEnd()) {
				myMissiles.erase(myMissiles.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < (int)missiles.size(); i++)
		{
			if (missiles[i].checkEnd()) {
				missiles.erase(missiles.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < (int)missiles.size(); i++)
		{
			for (int j = 0; j < (int)myMissiles.size(); j++)
			{
				if ((missiles[i].getX() == myMissiles[j].getX() || missiles[i].getX() == myMissiles[j].getX()+1) && missiles[i].getY() == myMissiles[j].getY()) {
					missiles.erase(missiles.begin() + i);
					myMissiles.erase(myMissiles.begin() + j);
					i--;
					break;
				}
			}
		}

		Sleep(50);
		clrscr();
	}

	return 0;
}