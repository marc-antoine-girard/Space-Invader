#pragma once
#include "Laser.h"
#include "Player.h"
class LaserEnnemie : public Laser
{
public:
	void bougerLaser(Player* player);
	LaserEnnemie(int x, int y);
	void removeLaser() const;
	void putLaser() const;
};

