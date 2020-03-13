#include "LaserNiv1.h"
#include "UIKit.h"
#include "Collision.h"
#include "Config.h"
#include <mmsystem.h>
int LaserNiv1::nbLaser = 0;
LaserNiv1::LaserNiv1(int x, int y): Laser()
{
	this->coord.setPositionX(x);
	this->coord.setPositionY(y - 2);
}
void LaserNiv1::startLaser()
{
	isAlive = true;
	PlaySound(TEXT("1.wav"), NULL, SND_FILENAME | SND_ASYNC);

}
void LaserNiv1::removeLaser() const
{
	UIKit::color(4);
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	std::cout << char(' ');
	coord.gotoXY(coord.getPositionX(), coord.getPositionY() + 1);
	std::cout << char(' ');
	UIKit::gotoXY(coord.getPositionX(), coord.getPositionY() + 2);
	std::cout << char(' ');
}

void LaserNiv1::putLaser(bool hyperMode) const
{
	UIKit::color(hyperMode ? Config::B_D_TURQUOISE + Config::T_L_TURQUOISE : Config::B_D_GREEN + Config::T_L_GREEN);
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	std::cout << char('|');
	UIKit::gotoXY(coord.getPositionX(), coord.getPositionY() + 1);
	std::cout << char('|');
	UIKit::color(hyperMode ? Config::T_D_YELLOW : Config::T_D_RED);
	UIKit::gotoXY(coord.getPositionX(), coord.getPositionY() + 2);
	std::cout << char('|');
	UIKit::color(Config::B_BLACK + Config::T_BLACK);
}

void LaserNiv1::moveLaser(ExtraTerrestre* extraterrestre[], bool hyperMode)
{
	removeLaser();
	if (coord.getPositionY() - 3 > 1)
	{
		this->coord.setPositionY(this->coord.getPositionY() - 3);
		this->putLaser(hyperMode);
	}
	else
	{
		this->isAlive = false;
	}
}
