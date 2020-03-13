#include "Plutonien.h"
#include "UIKit.h"
#include "Config.h"
#include "Collision.h"

Plutonien::Plutonien(Coord fenetreXY) : ExtraTerrestre(0, 0)
{
	this->nbTempAvantTire = 10;
	do
	{
		coord.setPositionX(rand() % ((fenetreXY.getPositionX() - this->LAREGEUR_PLUTONIEN - Config::separationEcran) - 5) + 2);
		coord.setPositionY(rand() % (fenetreXY.getPositionY() - 30) + 2);
	}while (spawnPossible());
	isAlive = true;
	ExtraTerrestre::nombreExtraTerrestre++;

	this->randomizeDirection();
	this->putExtraTerrestre();
}
void Plutonien::removeExtraTerrestre() const
{
	UIKit::color(Config::B_BLACK + Config::T_BLACK);
	UIKit::gotoXY(this->coord.getPositionX(), this->coord.getPositionY());
	cout << "       ";
	UIKit::gotoXY(this->coord.getPositionX(), this->coord.getPositionY() + 1);
	cout << "       ";
	UIKit::gotoXY(this->coord.getPositionX() + 1, this->coord.getPositionY() + 2);
	cout << "     ";
	UIKit::gotoXY(this->coord.getPositionX() + 2, this->coord.getPositionY() + 3);
	cout << "   ";
}
void Plutonien::putExtraTerrestre() const
{
	UIKit::color(Config::B_D_RED + Config::T_D_RED);
	UIKit::gotoXY(this->coord.getPositionX(), this->coord.getPositionY());
	cout << "888";
	UIKit::gotoXY(this->coord.getPositionX() + 4, this->coord.getPositionY());
	cout << "888";
	UIKit::gotoXY(this->coord.getPositionX() + 3, this->coord.getPositionY() + 1);
	cout << "8";
	UIKit::gotoXY(this->coord.getPositionX() + 2, this->coord.getPositionY() + 3);
	cout << "888";

	UIKit::color(Config::B_GREY + Config::T_GREY);
	UIKit::gotoXY(this->coord.getPositionX(), this->coord.getPositionY() + 1);
	cout << "8888888";
	UIKit::gotoXY(this->coord.getPositionX() + 1, this->coord.getPositionY() + 2);
	cout << "88888";


	UIKit::color(Config::B_L_RED + Config::T_L_RED);
	UIKit::gotoXY(this->coord.getPositionX() + 1, this->coord.getPositionY());
	cout << "8";
	UIKit::gotoXY(this->coord.getPositionX() + 5, this->coord.getPositionY());
	cout << "8";
	UIKit::gotoXY(this->coord.getPositionX() + 2, this->coord.getPositionY() + 1);
	cout << "8";
	UIKit::gotoXY(this->coord.getPositionX() + 4, this->coord.getPositionY() + 1);
	cout << "8";
	UIKit::gotoXY(this->coord.getPositionX() + 3, this->coord.getPositionY() + 3);
	cout << "8";

	UIKit::color(Config::B_L_YELLOW + Config::T_L_YELLOW);
	UIKit::gotoXY(this->coord.getPositionX() + 1, this->coord.getPositionY() + 1);
	cout << "8";
	UIKit::gotoXY(this->coord.getPositionX() + 5, this->coord.getPositionY() + 1);
	cout << "8";


	UIKit::color(Config::B_BLACK + Config::T_BLACK);
}

void Plutonien::move()
{
	
	if (Collision::detectOtherEnnemie(this) || this->nbTourInSameWay <= 0)
	{
		this->randomizeDirection();
	}
	if (nbTourInSameWay > 0)
	{
		this->removeExtraTerrestre();
		switch (this->direction)
		{
		case 0:
			this->coord.setPositionY(this->coord.getPositionY() - 1);
			break;
		case 1:
			this->coord.setPositionY(this->coord.getPositionY() + 1);
			break;
		case 2:
			this->coord.setPositionX(this->coord.getPositionX() - 1);
			break;
		case 3:
			this->coord.setPositionX(this->coord.getPositionX() + 1);
			break;
		}
		this->putExtraTerrestre();
	}
	this->nbTourInSameWay--;
}

void Plutonien::recevoirDegats()
{
	
}

bool Plutonien::spawnPossible()
{
	for (int i = 0; i < this->HAUTEUR_PLUTONIEN; i++)
	{
		for (int j = -1; j < this->LAREGEUR_PLUTONIEN + 1; j++)
		{
			if (UIKit::getCharXY(this->coord.getPositionX() + j, this->coord.getPositionY() + i) == char('8'))
				return true;
		}
	}
	return false;
}
void Plutonien::randomizeDirection()
{
	int compteur = 0;
	do
	{
		this->nbTourInSameWay = rand() % 40 + 10;
		this->direction = rand() % 5 - 1;
		compteur++;
	} while (Collision::detectOtherEnnemie(this) && compteur < 30);
	if (compteur >= 30)
	{
		this->direction = -1;
	}
}
Plutonien::~Plutonien()
{

}
int Plutonien::getDirection() const
{
	return this->direction;
}
int Plutonien::getNbTempAvantTire() const
{
	return this->nbTempAvantTire;
}
void Plutonien::setNbTempAvantTire(int temp)
{
	this->nbTempAvantTire = temp;
}
void Plutonien::randomizeTempAvantTir()
{
	if (Config::difficulter == 1)
		this->nbTempAvantTire = rand() % 30 + 40;
	else if (Config::difficulter == 2)
		this->nbTempAvantTire = rand() % 20 + 30;
	else
		this->nbTempAvantTire = rand() % 10 + 20;
}