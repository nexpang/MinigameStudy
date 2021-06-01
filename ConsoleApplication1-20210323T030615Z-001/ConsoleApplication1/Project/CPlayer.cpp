#include "CPlayer.h"
#include "Console.h"
#include <iostream>

void CPlayer::ShowPlayer()
{
	gotoXY(x, y);
	std::cout << "бу";
	gotoXY(29, 29);
}

void CPlayer::Move(int dir_x)
{
	if (x + dir_x < 1 || x + dir_x > 13)
		return;

	x += dir_x;
}
void CPlayer::SetPlayer()
{
	x = 7;
	y = 25;
}
int CPlayer::GetX()
{
	return x;
}

void CPlayer::OnDamage()
{

}