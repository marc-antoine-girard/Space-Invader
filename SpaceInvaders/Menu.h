#pragma once
#include "Partie.h"
#include "Coord.h"
class Menu
{
	static char customKey[4];
	static short coucheMenu;
	const enum ECRAN {
		PRINCIPAL = 1,
		DIFFICULTE = 2,
		INSTRUCTION = 3,
		TOUCHE = 4
	};
	const enum DIFFICULTE {
		FACILE = 1,
		NORMAL = 2,
		DIFFICILE = 3
	};
	static int spaceBtwChoice;
	static Coord emplacementChoix;
	static void removeScrollBar();
	static int vaisseauMenuX, vaisseauMenuY;
	static int choixPosX, choixPosY;
	static int logoX, logoY;
	static int keyX, keyY;
	static void etoile(int fenetreX, int fenetreY);
	static void vaisseauMenu(int x, int y);
	static bool validEntry;
	static int choix;
	static int menuLvl; 
	static int maxChoix;
	static int keyPressed();
	static void changerTouche();
	static bool choixManager();
	static void clearMenu();
	static void showMenu();
	static void laser(int posLaserX, int posLaserY);
	static void playChoix(bool KillColor);
	static void menuChoix(bool killColor);
	static void instructionMenu(bool killColor, bool actif);
	static void instructionTextMenu(bool killColor);
	static void logo(int x, int y);
	static int partieDifficulte;
public:
	static void initGame();
	static bool initMenu();
};

