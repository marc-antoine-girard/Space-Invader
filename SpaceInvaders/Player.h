#pragma once
#include "Vaisseau.h"
#include "Laser.h"
#include "ExtraTerrestre.h"
#include "Item.h"
class Player : public Vaisseau
{
	Laser** laser;
	int tempEntreTir;
	int compteurTemp;
	unsigned short niveauLaser;
	const int MAX_LASER = 6;
	const short VITESSE_DEPLACEMENT = 2;
	int pv;
	const int PV_MAX = 4;
	bool isDead;
	int energie;
	const int ENERGIE_MAX = 12;
	int timeOnHyperMode;
	const int MINIMUM_TIME_ON_HYPER_MODE = 10;
	bool hyperMode;
	

public:
	bool getIsDead() const;
	int getPv() const;
	const short HAUTEUR = 4;
	const short LARGEUR = 9;
	Player();
	void modifierPosition(char key);
	void bouger(Item* item[]);
	void tirer();
	void bougerLaser(ExtraTerrestre** extraterrestre, const int MAX_ENNEMIE);
	void removeVaisseau() const;
	void putVaisseau() const;
	void recevoirDegat();
	void recevoirVie();
	void recevoirEnergie();
	void checkHyperMode();
	~Player();
};

