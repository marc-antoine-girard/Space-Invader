#include "Partie.h"
#include "Menu.h"
#include "Player.h"
#include "UIKit.h"
#include <Windows.h>
#include <time.h>
#include "Config.h"
#include <chrono>
#include "Statistic.h"
#include "GOMenu.h"
#include "Plutonien.h"
#include <conio.h>
Partie::Partie() {
	//this->baseCharacterOnField();
	partieScore = 0;
	decomptePartie = 300;
	double diffTemps = 0;
	srand(time(0));
	system("Color 00");
	system("cls");

	UIKit::cadre(0, 0, (Config::fenetreXY.getPositionX() - 3) - Config::separationEcran, Config::fenetreXY.getPositionY() - 1, Config::B_D_PURPLE + Config::T_L_PURPLE);
	UIKit::cadre((Config::fenetreXY.getPositionX() - 2) - Config::separationEcran, 0, (Config::fenetreXY.getPositionX() - 3), Config::fenetreXY.getPositionY() - 1, Config::B_D_PURPLE + Config::T_D_PURPLE);
	this->player = new Player();
	this->extraTerrestre = new ExtraTerrestre*[this->MAX_EXTRATERRESTRE];
	for (int i = 0; i < this->MAX_EXTRATERRESTRE; i++)
	{
		extraTerrestre[i] = NULL;
	}
	this->laserEnnemie = new LaserEnnemie*[this->MAX_LASER];
	for (int i = 0; i < this->MAX_LASER; i++)
	{
		laserEnnemie[i] = NULL;
	}
	this->item = new Item*[10];
	for (int i = 0; i < 10; i++)
	{
 		item[i] = NULL;
	}
	this->stats = new Statistic();
	//GOMenu::GOMenu();l
	//this->demarrerPartie();
}

void Partie::demarrerPartie() {
	//this->initGame();
	bool GameRun = true;
	auto start = std::chrono::steady_clock::time_point();
	auto stop = std::chrono::steady_clock::time_point();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	int compteurBoucleSpawnExtraterrestre = 0;
	this->tempsEnPause = 0;
	this->dureeDebutPartie = time(0);
	//player->putVaisseau();
	while (GameRun && !player->getIsDead() && decomptePartie > 0)
	{
		//sert a reguler le Sleep calcule le temp en milliseconde maintenant et apres les instruction :)
		start = std::chrono::high_resolution_clock::now();
		
		GameRun = this->pause();
		this->player->bouger(item);
		//this->player->temp();
		this->player->tirer();
		this->player->bougerLaser(extraTerrestre, this->MAX_EXTRATERRESTRE);
		this->spawnEnnemie(compteurBoucleSpawnExtraterrestre);
		this->moveExtraterrestre();
		this->moveItem();
		this->calculDuree();
		this->bougerLaserEnnemie();
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		//UIKit::gotoXY(5, 5);
		//cout << duration.count() << "    " << endl;
		Statistic::afficherScore(this->partieScore, Config::fenetreXY.getPositionX() - 40, 1);
		Sleep(50 - duration.count() < 0 ? 0 : 50 - duration.count());
		
		compteurBoucleSpawnExtraterrestre++;
	}
	UIKit::cadre(0, 0, (Config::fenetreXY.getPositionX() - 3) - Config::separationEcran, Config::fenetreXY.getPositionY() - 1, player->getIsDead() ? Config::B_D_RED + Config::T_L_RED : Config::B_D_GREEN + Config::T_L_GREEN);
	UIKit::cadre((Config::fenetreXY.getPositionX() - 2) - Config::separationEcran, 0, (Config::fenetreXY.getPositionX() - 3), Config::fenetreXY.getPositionY() - 1, player->getIsDead() ? Config::B_D_RED + Config::T_L_RED : Config::B_D_GREEN + Config::T_L_GREEN);

	UIKit::color(Config::B_BLACK);
	Sleep(1000);
	system("cls");
	GOMenu::initGOMenu(this->partieScore);
	ExtraTerrestre::nombreExtraTerrestre = 0;

}
void Partie::spawnEnnemie(int &timeAfterLastSpawn)
{
	bool extraTerrestreCreer = false;
	int compteur = 0;
	if (ExtraTerrestre::nombreExtraTerrestre < 6)
	{
		if (timeAfterLastSpawn > nbTempAvantSpawn)
		{
			randomizeTimeSpawn();
			timeAfterLastSpawn = 0;
			while (!extraTerrestreCreer)
			{
				if (extraTerrestre[compteur] == NULL)
				{
					extraTerrestre[compteur] = new Plutonien(Config::fenetreXY);
					extraTerrestreCreer = true;
				}
				compteur++;
			}
		}
	}
}
void Partie::moveExtraterrestre()
{
	int compteur = 0;
	int compteurExtraTerrestre = 0;
	
	while (compteurExtraTerrestre < ExtraTerrestre::getNombreExtraTerrestre())
	{
		if (extraTerrestre[compteur] != NULL && extraTerrestre[compteur]->isAlive == true)
		{
			this->verifierEnnemieTir(((Plutonien*)extraTerrestre[compteur]));
			((Plutonien*)extraTerrestre[compteur])->move();
			
			
			//((Plutonien*)extraTerrestre[compteur])->tirer();
			//((Plutonien*)extraTerrestre[compteur])->bougerLaserEnnemie(player);
			//((Plutonien*)extraTerrestre[compteur])->recevoirDegats();
			compteurExtraTerrestre++;
		}
		if (extraTerrestre[compteur] != NULL && extraTerrestre[compteur]->isAlive == false)
		{
			this->verifyIfDropItem(extraTerrestre[compteur]->coord.getPositionX(), extraTerrestre[compteur]->coord.getPositionY());
			delete((Plutonien*)extraTerrestre[compteur]);
			extraTerrestre[compteur] = NULL;
			this->partieScore += 10;
			ExtraTerrestre::reduireNombreExtraTerrestre();
			compteurExtraTerrestre++;
			
		}
		compteur++;
	}
}
void Partie::verifyIfDropItem(int x, int y)
{
	bool itemCreer = false;
	int compteur = 0;
	int random = rand() % 100;
	if (random > 70)
	{
		while (!itemCreer)
		{
			if (this->item[compteur] == NULL)
			{
				item[compteur] = new Item(x, y);
				itemCreer = true;
			}
			compteur++;
		}
	}
}
void Partie::moveItem()
{
	for (int i = 0; i < 10; i++)
	{
		if (this->item[i] != NULL && item[i]->isAlive)
		{
			this->item[i]->moveItem();
		}
		else if (this->item[i] != NULL && !item[i]->isAlive)
		{
			delete(this->item[i]);
			this->item[i] = NULL;
		}
	}
}
void Partie::calculDuree() {
	double seconds;
	dureeActuel = time(0);
	seconds = difftime(dureeActuel, dureeDebutPartie) - this->tempsEnPause;
	if ((seconds - diffTemps) >= 1) {
		diffTemps = seconds;
		Partie::decomptePartie = 301 - seconds;
		Statistic::afficherDuree(Partie::decomptePartie, Config::fenetreXY.getPositionX() - 19, 1);
	}
}
void Partie::bougerLaserEnnemie()
{
	
	for (int i = 0; i < this->MAX_LASER; i++)
	{
		if (this->laserEnnemie[i] != NULL)
		{
			if (this->laserEnnemie[i]->isAlive)
			{
				this->laserEnnemie[i]->bougerLaser(this->player);
			}

			else
			{
				delete(this->laserEnnemie[i]);
				this->laserEnnemie[i] = NULL;
			}
		}
		
	}
}
void Partie::verifierEnnemieTir(Plutonien* plutonien)
{

	if (plutonien->getNbTempAvantTire() < 0)
	{
		plutonien->randomizeTempAvantTir();
		int compteur = 0;
		bool laserCreer = false;
		int compteurLaser = 0;
		while (!laserCreer)
		{
			if (this->laserEnnemie[compteur] == NULL)
			{
				this->laserEnnemie[compteur] = new LaserEnnemie(plutonien->coord.getPositionX() + (plutonien->LAREGEUR_PLUTONIEN / 2), plutonien->coord.getPositionY() + plutonien->HAUTEUR_PLUTONIEN);
				this->laserEnnemie[compteur]->isAlive = true;
				laserCreer = true;
			}
			compteur++;
		}
	}
	else
	{
		//this->nbTempAvantTire--;
		plutonien->setNbTempAvantTire(plutonien->getNbTempAvantTire() - 1);
	}
}
Partie::~Partie()
{
	//delete[] laserEnnemie;
	for (int i = 0; i < this->MAX_LASER; i++)
	{
		delete laserEnnemie[i];
	}
	delete[] laserEnnemie;
	//delete[]extraTerrestre;
	//delete(extraTerrestre);
	delete stats;
	for (int i = 0; i < 10; i++)
	{
		delete item[i];
	}
	delete[] item;
	//delete(item);
	delete player;
}
void Partie::randomizeTimeSpawn()
{
	if (Config::difficulter == 1)
	{
		this->nbTempAvantSpawn = rand() % 30 + 50;
	}
	else if (Config::difficulter == 2)
	{
		this->nbTempAvantSpawn = rand() % 20 + 40;
	}
	else
	{
		this->nbTempAvantSpawn = rand() % 10 + 30;
	}

}
bool Partie::pause() {
	bool gameOver = true;
	if (GetKeyState(toupper('p')) & 0x8000) {
		time_t debutPause = time(0);
		gameOver = Statistic::pauseWindow();
		time_t finPause = time(0);
		tempsEnPause += difftime(finPause, debutPause);
	}
	return gameOver;
}