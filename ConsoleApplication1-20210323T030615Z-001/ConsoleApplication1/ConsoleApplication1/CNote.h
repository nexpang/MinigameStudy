#pragma once

class CNote
{
private:
	int x;
	int y;
	int index;

public:
	void initNote();

	void drawNote();
	void downNote();

	void checkCorrect(int key);
	void checkEnd();

	void playSound();
};