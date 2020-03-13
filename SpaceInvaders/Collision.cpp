#include "Collision.h"
#include "Plutonien.h"
#include "UIKit.h"
#include "Statistic.h"
#include "Config.h"
#include "ExtraTerrestre.h"

bool Collision::detectEnnemie(LaserNiv1* laser, ExtraTerrestre* ennemie[], const int MAX_ENNEMIE)
{
	int compteurBoucle = 0;
	int compteurExtraterrestre = 0;
	bool ennemieTrouver = false;
	while(ExtraTerrestre::nombreExtraTerrestre > compteurExtraterrestre)
	{
		if (ennemie[compteurBoucle] != NULL)
		{
			for (int i = 0; i < Plutonien::LAREGEUR_PLUTONIEN; i++)
			{
				if (UIKit::getCharXY(ennemie[compteurBoucle]->coord.getPositionX() + i, ennemie[compteurBoucle]->coord.getPositionY() + (Plutonien::HAUTEUR_PLUTONIEN) + 1) == '|')
				{
 					((Plutonien*)ennemie[compteurBoucle])->removeExtraTerrestre();
					ennemie[compteurBoucle]->isAlive = false;
					return true;
				}
			}
			compteurExtraterrestre++;
		}
		compteurBoucle++;
	}
	return false;
}

bool Collision::detectPlayer(LaserEnnemie* laser, Player* player)
{
	if (UIKit::getCharXY(laser->coord.getPositionX(), laser->coord.getPositionY() + 1) == '9')
	{
		player->recevoirDegat();
		player->putVaisseau();
		Statistic::barVie(player->getPv());
		return true;
	}
	return false;
}
int Collision::itemDetection(Item* item[], Player* player)
{
	for (int i = 0; i < 10; i++)
	{
		if (item[i] != NULL && item[i]->isAlive)
		{
			if (UIKit::getCharXY(item[i]->coord.getPositionX() - 1, item[i]->coord.getPositionY() + 1) == '9' || UIKit::getCharXY(item[i]->coord.getPositionX() + 4, item[i]->coord.getPositionY() + 1) == '9')
			{
				item[i]->removeItem();
				item[i]->isAlive = false;
				return item[i]->getType();
			}
		}
	}
	return -1;
}
bool Collision::detectOtherEnnemie(Plutonien* plutonien)
{
	UIKit::color(17);
	switch (plutonien->getDirection())
	{
	case 0:
		for (int i = 0; i < plutonien->LAREGEUR_PLUTONIEN; i++)
		{
			if (UIKit::getCharXY(plutonien->coord.getPositionX() + i, plutonien->coord.getPositionY() - 1) == '8' || plutonien->coord.getPositionY() - 1 < 4)
			{
				return true;
			}
		}
		break;
	case 1:
		for (int i = 0; i < plutonien->LAREGEUR_PLUTONIEN; i++)
		{
			if (UIKit::getCharXY(plutonien->coord.getPositionX() + i, plutonien->coord.getPositionY() + plutonien->HAUTEUR_PLUTONIEN) == '8' || plutonien->coord.getPositionY() + plutonien->HAUTEUR_PLUTONIEN + 1 > 40)
			{
				return true;
			}
		}
		break;
	case 2:
		for (int i = 0; i < plutonien->HAUTEUR_PLUTONIEN; i++)
		{
			if (UIKit::getCharXY(plutonien->coord.getPositionX() - 1, plutonien->coord.getPositionY() + i) == '8' || plutonien->coord.getPositionX() - 1 < 4)
			{
				return true;
			}
		}
		break;
	case 3:
		for (int i = 0; i < plutonien->HAUTEUR_PLUTONIEN; i++)
		{
			if (UIKit::getCharXY(plutonien->coord.getPositionX() + plutonien->LAREGEUR_PLUTONIEN + 1, plutonien->coord.getPositionY() + i) == '8' || plutonien->coord.getPositionX() + plutonien->LAREGEUR_PLUTONIEN + 1 > 169)
			{
				return true;
			}
		}
		break;
	}
	return false;
}