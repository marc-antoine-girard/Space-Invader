#pragma once
#include <time.h>
#include "Config.h"
#include "UIKit.h"
class Statistic
{
	int score;
	int playerVie;
	int playerEnergie;
	static int statsX;
	static int statsY;
	static const int MAX_VIE;
	static const int MAX_ENERGIE;
public:
	Statistic();
	
	time_t tempsDebutPartie;
	void initStats();
	static void afficherDuree(double temps, int posX, int posY);
	static void barVie(int nbvie);
	static void barEnergie(int nbEnergie);
	static void afficherScore(int score, int posX, int posY);
	static int tabScoreDigit[15];
	static bool pauseWindow();
	~Statistic();
};

