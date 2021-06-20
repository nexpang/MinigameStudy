#include <iostream>
#include <fstream>
#include <string>

#include "Console.h"

using namespace std;

bool bStart;
int currentScore;
int highScore[5];

void setConsoleView() {
	system("mode con:cols=35 lines=28");
	system("title Score Test");
}

void saveFile() {
	ofstream writeToFile("score.txt");

	for (int i = 0; i < 5; i++)
	{
		string temp = to_string(highScore[i]);

		if (i < 4)
		{
			temp += "\n";
		}

		writeToFile.write(temp.c_str(), temp.size());
	}

	writeToFile.close();
}

void loadFile()
{
	ifstream readFromFile("score.txt");

	if (!readFromFile.is_open())
	{
		saveFile();
	}

	int i = 0;

	while (!readFromFile.eof())
	{
		string temp;
		getline(readFromFile, temp);

		highScore[i] = stoi(temp);
		i++;
	}

	readFromFile.close();
}

void InitData()
{
	bStart = false;

	currentScore = 0;
	for (int i = 0; i < 5; i++)
	{
		highScore[i] = 0;
	}
	loadFile();
}

void drawHighScore() {
	gotoXY(6, 10);
	cout << "HIGH SCORE";

	for (int i = 0; i < 5; i++)
	{
		gotoXY(5, 12 + i * 2);
		cout << i + 1 << " : " << highScore[i];
	}

	gotoXY(3, 22);
	cout << "-----------------------";
}

void drawScore() {
	gotoXY(5, 10);
	cout << "[a] ADD SCORE";
	gotoXY(3, 12);
	cout << "-----------------------";
	gotoXY(5, 14);
	cout << "SCORE : "<<currentScore;

}

void drawMenu()
{
	gotoXY(3, 2);
	cout << "-----------------------";
	gotoXY(6, 3);
	cout << "SCORE TEST";
	gotoXY(3, 4);
	cout << "-----------------------";

	gotoXY(5, 6);
	bStart ? cout << "[x] EXIT GAME" : cout << "[s] START GAME";
	gotoXY(3, 8);
	cout << "-----------------------";

	bStart ? drawScore() : drawHighScore();
}

void saveScore(int score)
{
	for (int i = 0; i < 5; i++)
	{
		if (score >= highScore[i])
		{
			for (int j = 3; j >= i; j--)
			{
				highScore[j + 1] = highScore[j];
			}

			highScore[i] = score;
			saveFile();
			break;
		}
	}
}

void checkKeyDown(int key)
{
	if (key == 's' && !bStart)
	{
		bStart = true;
		currentScore = 0;
	}
	else if (key == 'x' && bStart)
	{
		bStart = false;
		saveScore(currentScore);
	}
	else if (key == 'a' && bStart)
	{
		currentScore++;
	}
}


int main()
{
	setConsoleView();

	InitData();

	while (1)
	{
		checkKeyDown(getKeyDown());

		drawMenu();

		gotoXY(0, 27);

		Sleep(100);
		clrscr();
	}

	return 0;
}