//20303 김경혁 
// 과제 완료
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x*2;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

int getKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

vector<string> pastWord;
vector<string> strWords;

void setConsoleView()
{
	system("mode con:cols=50 lines=20");
	system("title WORD GAME");
}

void drawReadyGame()
{
	system("cls");
	gotoXY(4, 2);
	cout << "===============================";
	gotoXY(4, 3);
	cout << "========== WORD GAME ==========";
	gotoXY(4, 4);
	cout << "===============================";
	gotoXY(5, 6);
	cout << "시작하려면 's'를 눌러주세요";
	gotoXY(20, 18);
}

bool readyGame()
{
	drawReadyGame();

	while (1)
	{
		int key = getKeyDown();
		key = tolower(key);

		if (key == 's')
		{
			return true;
		}
	}
}

void setWords()
{
	string str[4] = { "apple", "banana", "code", "program" };

	ifstream readFromFile("words.txt");

	if (!readFromFile.is_open())
	{
		ofstream writeToFile("words.txt");

		for (int i = 0; i < 4; i++)
		{
			string temp = str[i];
			if (i < 3)
			{
				temp += "\n";
			}
			writeToFile.write(temp.c_str(), temp.size());
			strWords.push_back(str[i]);
		}

		writeToFile.close();
	}
	else
	{
		while (!readFromFile.eof())
		{
			string temp;
			getline(readFromFile, temp);
			strWords.push_back(temp);
		}

		readFromFile.close();
	}
}

void drawStartGame()
{
	system("cls");
	gotoXY(5, 8);
	cout << "past = ";
	for (int i = 0; i < (int)pastWord.size(); i++)
	{
		cout << pastWord[i] << " ";
	}
	gotoXY(5, 12);
	cout << "input = ";
}

void startGame()
{
	srand((unsigned)time(NULL));

	setWords();
	while (1)
	{
		int num = rand() % (int)strWords.size();

		string strQuestion;
		string strOriginal = strWords[num];
		int originalLen = (int)strOriginal.length();

		for (int i = 0; i < originalLen; i++)
		{
			strQuestion += "_";
		}

		while (1)
		{
			drawStartGame();

			gotoXY(5, 5);
			for (int i = 0; i < originalLen; i++)
			{
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			gotoXY(9, 12);
			string strInput;
			cin >> strInput;

			bool reset = false;
			for (int i = 0; i < pastWord.size(); i++)
			{
				if (pastWord[i] == strInput) {
					reset = true;
				}
			}
			if (reset) continue;
			pastWord.push_back(strInput);

			if (strInput.length() == 1)
			{
				for (int i = 0; i < originalLen; i++)
				{
					if (strOriginal[i] == strInput[0])
					{
						strQuestion[i] = strInput[0];
					}
				}
			}
			else if (strInput.length() > 1)
			{
				if (strOriginal == strInput)
				{
					pastWord.clear();
					break;
				}
			}
		}
	}
}
int main() 
{
	setConsoleView();

	while (1) {
		if (readyGame()) 
		{
			startGame();
		}
	}
	return 0;
}