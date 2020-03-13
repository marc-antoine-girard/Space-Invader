#pragma once
#include "ExtraTerrestre.h"
#include "LaserNiv1.h"
#include "Player.h"
#include "LaserEnnemie.h"
#include "Item.h"
#include "Plutonien.h"
class Collision
{
public:
	static bool detectEnnemie(LaserNiv1* laser, ExtraTerrestre* ennemie[], const int MAX_ENNEMIE);
	static bool detectPlayer(LaserEnnemie* laser, Player* Player);
	static int itemDetection(Item* item[], Player* player);
	static bool detectOtherEnnemie(Plutonien* plutonien);
};

