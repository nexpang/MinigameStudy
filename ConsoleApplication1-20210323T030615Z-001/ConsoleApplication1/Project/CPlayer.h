#pragma once
class CPlayer
{
private:
	int hp;
	int x;
	int y;

public:
	void ShowPlayer();

	void SetPlayer();
	void Move(int dir_x);
	int GetX();

	void OnDamage();
};

