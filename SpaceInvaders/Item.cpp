#include "Item.h"
#include "Config.h"
#include "UIKit.h"
#include <stdlib.h>  
#include <time.h> 


Item::Item(int departX, int departY) 
{
	int temp = rand() % 100;
	if (temp > 65)
		this->type = 0;
	else
		this->type = 1;

	this->coord.setPositionX(departX);
	this->coord.setPositionY(departY);
	this->isAlive = true;
	this->putItem();
}
void Item::putItem()
{
	UIKit::color(this->type == 1? Config::T_L_TURQUOISE : Config::T_L_GREEN);
	UIKit::gotoXY(this->coord.getPositionX(), this->coord.getPositionY());
	cout << " * ";

}
void Item::removeItem()
{
	UIKit::gotoXY(this->coord.getPositionX(), this->coord.getPositionY());
	cout << "  ";

}
void Item::moveItem()
{
	this->removeItem();
	if (this->coord.getPositionY() + 3 < Config::fenetreXY.getPositionY() - 1)
		this->coord.setPositionY(this->coord.getPositionY() + 1);
	this->putItem();
}
int Item::getType() const
{
	return this->type;
}