#include "CPlayer.h"
#include "Console.h"
#include <iostream>

void CPlayer::ShowPlayer()
{
	gotoXY(x, y);
	std::cout << "бу";
	gotoXY(69, 29);
}

void CPlayer::Move(int dir_x)
{
	if (x + dir_x < 1 || x + dir_x > 27)
		return;

	x += dir_x;
}
void CPlayer::SetPlayer()
{
	x = 13;
	y = 25;
}
int CPlayer::GetX()
{
	return x;
}

void CPlayer::OnDamage()
{

}