#pragma once
#include "Coord.h"
class Item
{
	const int TEMP_AVANT_DISPARITION = 200;
	const int VITESSE_DROP = 1;
	//0 = vie 1 = energie;
	void putItem();
	
	int type;
public:
	void removeItem();
	int isAlive;
	Coord coord;
	Item(int departX, int departY);
	int getType() const;
	void moveItem();
};

