#pragma once
#include "Plutonien.h"
#include "Player.h"
#include "Statistic.h"
#include "Item.h"
class Partie {
	const int MAX_LASER = 11;
	LaserEnnemie** laserEnnemie;
	const int MAX_EXTRATERRESTRE = 10;
	ExtraTerrestre** extraTerrestre;
	Player* player;
	Statistic* stats;
	Item** item;
	time_t dureeDebutPartie;
	time_t dureeActuel;
	double diffTemps;
	void calculDuree();
	double decomptePartie;
	void randomizeTimeSpawn();
	int nbTempAvantSpawn;
	bool pause();
	time_t tempsEnPause;
	int partieScore;
public:
	Partie();
	void demarrerPartie();
	void spawnEnnemie(int &timeAfterLastSpawn);
	void moveExtraterrestre();
	void moveItem();

	void verifyIfDropItem(int x, int y);
	void bougerLaserEnnemie();
	void verifierEnnemieTir(Plutonien* plutonien);
	~Partie();
};