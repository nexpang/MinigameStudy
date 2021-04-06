#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

using namespace std;

const int Tone[8] = { 523, 587, 659, 698, 784, 880, 988, 1046 };
const string name[8] = { "도", "레", "미", "파", "솔", "라", "시", "도" };

int main()
{
	srand((unsigned)time(NULL));

	int selectTone = 0;
	int select = 0;

	_getch();

	while (true)
	{
		for (int i = 0; i < 8; i++)
		{
			cout << name[i] << "(" << i + 1 << ") ";
			Beep(Tone[i], 500);
		}

		Sleep(1000);

		selectTone = rand() % 8;

		Beep(Tone[selectTone], 1000);
		select = _getch() - '1';

		if (selectTone == select)
		{
			cout << "GOOD" << endl;
		}
		else
		{
			cout << "NO : ";

			cout << name[selectTone] << endl;
			Beep(Tone[selectTone], 500);
		}

		_getch();

	}

	return 0;
}