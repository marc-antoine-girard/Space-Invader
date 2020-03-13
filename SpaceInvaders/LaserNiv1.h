#pragma once
#include "Laser.h"
#include "ExtraTerrestre.h"
class LaserNiv1 : public Laser
{
public:
	static int nbLaser;
	LaserNiv1(int x, int y);
	void startLaser();
	void removeLaser() const;
	void putLaser(bool hyperMode) const;
	void moveLaser(ExtraTerrestre* extraterrestre[], bool hyperMode);
};
