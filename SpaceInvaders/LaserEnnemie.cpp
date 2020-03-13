#include "LaserEnnemie.h"
#include "UIKit.h"
#include "Config.h"
#include "Collision.h"
LaserEnnemie::LaserEnnemie(int x, int y)
{
	this->coord.setPositionX(x);
	this->coord.setPositionY(y + 3);
}

void LaserEnnemie::removeLaser() const
{
	UIKit::color(4);
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	std::cout << char(' ');
	coord.gotoXY(coord.getPositionX(), coord.getPositionY() - 1);
	std::cout << char(' ');
	UIKit::gotoXY(coord.getPositionX(), coord.getPositionY() - 2);
	std::cout << char(' ');
}

void LaserEnnemie::putLaser() const
{
	UIKit::color(0x4b);
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	std::cout << char(186);
	UIKit::gotoXY(coord.getPositionX(), coord.getPositionY() - 1);
	std::cout << char(186);
	UIKit::color(0x0b);
	UIKit::gotoXY(coord.getPositionX(), coord.getPositionY() - 2);
	std::cout << char(186);
}
void LaserEnnemie::bougerLaser(Player* player)
{
	this->removeLaser();
	if (this->coord.getPositionY() + 3 < Config::fenetreXY.getPositionY() - 2)
	{
		this->coord.setPositionY(coord.getPositionY() + 3);
		if (Collision::detectPlayer(this, player))
		{
			this->isAlive = false;
		}
		else
		{
			this->putLaser();
		}
			
	}
	else
	{
		this->isAlive = false;
	}
}