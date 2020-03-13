#include "Player.h"
#include <Windows.h>
#include "UIKit.h"
#include "LaserNiv1.h"
#include "Config.h"
#include "Collision.h"
#include <conio.h>
#include "Statistic.h"

Player::Player(): tempEntreTir(10)
{
	this->pv = this->PV_MAX; 
	this->hyperMode = false;
	Vaisseau::removeVaisseau();
	this->coord.setPositionX((Config::fenetreXY.getPositionX() - Config::separationEcran) / 2);
	this->coord.setPositionY(Config::fenetreXY.getPositionY() - 5);
	this->compteurTemp = 0;
	this->laser = new Laser*[this->MAX_LASER];
	this->niveauLaser = 1;
	this->isDead = false;
	this->energie = 0;
	this->timeOnHyperMode = 0;
	for (int i = 0; i < this->MAX_LASER; i++)
	{
		this->laser[i] = NULL;
	}
	this->putVaisseau();

}
void Player::modifierPosition(char key)
{
	removeVaisseau();

	if (key == Config::customKey[0]) {
		if (coord.getPositionX() > 2)
		{
			coord.setPositionX(coord.getPositionX() - this->VITESSE_DEPLACEMENT);
		
		}
	}
	else if (key == Config::customKey[1]){
		if (coord.getPositionX() + this->LARGEUR < (Config::fenetreXY.getPositionX() - Config::separationEcran) - 4)
		{
			coord.setPositionX(coord.getPositionX() + this->VITESSE_DEPLACEMENT);
			
		}
	}
    putVaisseau();
}
void Player::bouger(Item* item[])
{
	int hitType;
	if (GetKeyState(toupper(Config::customKey[0])) & 0x8000)
	{
		this->modifierPosition(Config::customKey[0]);
	}
	else if (GetKeyState(toupper(Config::customKey[1])) & 0x8000)
	{
		this->modifierPosition(Config::customKey[1]);
	}
	hitType = Collision::itemDetection(item, this);
	if (hitType == 0)
	{
		this->recevoirVie();
	}
	else if (hitType == 1)
	{
		this->recevoirEnergie();
	}
	this->checkHyperMode();
}
void Player::tirer()
{
	int compteur = 0;
	bool laserCreer = false;
	int compteurLaser = 0;

	if (compteurTemp > tempEntreTir)
	{
		if (GetKeyState(toupper(Config::customKey[3])) & 0x8000)
		{
  			compteurTemp = 0;
			while (!laserCreer)
			{
				if (this->laser[compteur] == NULL)
				{
					if (this->hyperMode == false)
					{
						this->laser[compteur] = new LaserNiv1(this->coord.getPositionX() + this->LARGEUR / 2, this->coord.getPositionY() - 1);
						((LaserNiv1*)this->laser[compteur])->startLaser();
						laserCreer = true;
					}
					else
					{
						this->laser[compteur] = new LaserNiv1((this->coord.getPositionX()) + (compteurLaser * 4), compteurLaser == 1 ? this->coord.getPositionY() - 5 : this->coord.getPositionY() - 4);
						((LaserNiv1*)this->laser[compteur])->startLaser();
						if (compteurLaser < 2)
						{
							compteurLaser++;
						}
						else
						{
							laserCreer = true;
						}
					}
				}
				compteur++;
			}
		}
	}
	compteurTemp++;
}
Player::~Player()
{
	for (int i = 0; i < 6; i++)
	{
		delete laser[i];
	}
	delete[] laser;
}
void Player::bougerLaser(ExtraTerrestre** extraterrestre, const int MAX_ENNEMIE)
{
	for(int i = 0; i < this->MAX_LASER; i++)
	{
		if (this->laser[i] != NULL)
		{
			if (Collision::detectEnnemie(((LaserNiv1*)laser[i]), extraterrestre, MAX_ENNEMIE))
			{
				this->laser[i]->isAlive = false;
				((LaserNiv1*)this->laser[i])->removeLaser();
			}
			if (this->laser[i]->isAlive )
			{
				((LaserNiv1*)this->laser[i])->moveLaser(extraterrestre, this->hyperMode);
			}
			else
			{
				LaserNiv1::nbLaser--;
				delete(this->laser[i]);
				this->laser[i] = NULL;
			}
		}
	}
}
void Player::removeVaisseau() const
{
	UIKit::color(Config::B_BLACK + Config::T_BLACK);
	coord.gotoXY(coord.getPositionX(), coord.getPositionY() + 1);
	cout << "         ";
	coord.gotoXY(coord.getPositionX() + 1, coord.getPositionY());
	cout << "       ";
	coord.gotoXY(coord.getPositionX() + 2, coord.getPositionY() + 2);
	cout << "     ";
	coord.gotoXY(coord.getPositionX() + 3, coord.getPositionY() + 3);
	cout << "   ";
}
void Player::putVaisseau() const
{
	// POD VAISSEAU
	
	bool isPowerful = true;
	UIKit::color(this->hyperMode ? Config::B_L_TURQUOISE + Config::T_L_TURQUOISE : Config::B_D_RED + Config::T_D_RED);  // rouge foncé

	coord.gotoXY(coord.getPositionX(), coord.getPositionY() + 1);
	cout << "999999999";
	coord.gotoXY(coord.getPositionX() + 1, coord.getPositionY());
	cout << "9999999";
	UIKit::color(Config::B_GREY + Config::T_GREY);  // gris
	coord.gotoXY(coord.getPositionX() + 1, coord.getPositionY() + 1);
	cout << "9999999";
	coord.gotoXY(coord.getPositionX() + 2, coord.getPositionY());
	cout << "99999";

	//REACTEUR VAISSEAU
	UIKit::color(this->hyperMode ? Config::B_L_BLUE + Config::T_L_BLUE: Config::B_D_RED + Config::T_D_RED); //Rouge Foncé
	coord.gotoXY(coord.getPositionX() + 3, coord.getPositionY() + 3);
	cout << "999";
	coord.gotoXY(coord.getPositionX() + 2, coord.getPositionY() + 2);
	cout << "99999";
	UIKit::color(this->hyperMode ? Config::B_L_TURQUOISE + Config::T_L_TURQUOISE : Config::B_L_RED + Config::T_L_RED); // Rouge clair
	coord.gotoXY(coord.getPositionX() + 4, coord.getPositionY() + 3);
	cout << "9";
	coord.gotoXY(coord.getPositionX() + 3, coord.getPositionY() + 2);
	cout << "999";
	UIKit::color(this->hyperMode ? Config::B_WHITE + Config::T_WHITE : Config::B_L_YELLOW + Config::T_L_YELLOW); //Blanc
	coord.gotoXY(coord.getPositionX() + 4, coord.getPositionY() + 2);
	cout << "9";

	UIKit::color(this->hyperMode ? Config::B_L_TURQUOISE + Config::T_L_GREEN : Config::B_L_GREEN + Config::T_L_RED);

	coord.gotoXY(coord.getPositionX() + 4, coord.getPositionY());
	cout << "|";

	UIKit::color(Config::B_BLACK + Config::T_BLACK);
}
void Player::recevoirDegat()
{
	if (this->pv > 0)
	{
		if(Config::difficulter == 3)
			this->pv -= 2;
		else
			this->pv -= 1;
		if (this->pv <= 0)
		{
			this->isDead = true;
		}
	}
	else
	{
		this->isDead = true;
	}
}
int Player::getPv() const
{
	return this->pv;
}
void Player::recevoirVie()
{
	if (pv < this->PV_MAX)
	{
		this->pv+=1;
		Statistic::barVie(this->getPv());
	}
	else
	{
		this->pv = this->PV_MAX;
	}
}
void Player::recevoirEnergie()
{
	if (this->energie < this->ENERGIE_MAX)
	{
		this->energie += 2;
		Statistic::barEnergie(this->energie);
	}
}
bool Player::getIsDead() const
{
	return this->isDead;
}
void Player::checkHyperMode()
{
	char touche = 0;
	if (_kbhit())
	{
		touche = tolower(_getch());
		if (touche == Config::customKey[2])
		{
			this->hyperMode = !this->hyperMode;
			this->putVaisseau();
			if (this->timeOnHyperMode != 0)
			{
				this->energie -= timeOnHyperMode / 10;
				Statistic::barEnergie(this->energie);
			}
			timeOnHyperMode = 0;
		}
	}
	if (hyperMode == true)
	{
		this->timeOnHyperMode++;
		if (this->timeOnHyperMode > 10)
		{
			this->energie -= timeOnHyperMode / 10;
			Statistic::barEnergie(this->energie);
			this->timeOnHyperMode = 0;
		}
		if (this->energie == 0)
		{
			this->hyperMode = false;
			this->putVaisseau();
		}
	}
}