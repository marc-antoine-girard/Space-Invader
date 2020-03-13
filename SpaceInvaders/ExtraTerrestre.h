#ifndef EXTRATERRESTRE_H
#define EXTRATERRESTRE_H

#include "Coord.h"

class ExtraTerrestre
{
protected:
	int typeExtraTerrestre;
	int valeurExtraTerrestre;

public:
	static int nombreExtraTerrestre;
	Coord coord;
	bool isAlive;

	ExtraTerrestre(int,int);
	static void reduireNombreExtraTerrestre();
	static int getNombreExtraTerrestre();
	static void resetNombreExtraTerrestre();
	void removeExtraTerrestre() const;
	void putExtraTerrestre() const;
	int ajouterPoints() const;
	void resetExtraTerrestre();
};

#endif




