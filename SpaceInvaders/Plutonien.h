#pragma once
#include "ExtraTerrestre.h"
#include "LaserEnnemie.h"
class Plutonien : public ExtraTerrestre
{
	const int MAX_LASER = 10;
	int nbVie;
	int nbTempAvantTire;
	int nbTourInSameWay;
	//0=haut, 1=bas, 2=gauche, 3=droite
	int direction;
public:
	static const int LAREGEUR_PLUTONIEN = 7;
	static const int HAUTEUR_PLUTONIEN = 4;
	Plutonien(Coord fenetreXY);
	int getNbTempAvantTire() const;
	void setNbTempAvantTire(int temp);
	bool spawnPossible();
	void removeExtraTerrestre() const;
	void putExtraTerrestre() const;
	void move();
	void recevoirDegats();
	void randomizeDirection();
	int getDirection() const;
	void randomizeTempAvantTir();
	~Plutonien();
};

