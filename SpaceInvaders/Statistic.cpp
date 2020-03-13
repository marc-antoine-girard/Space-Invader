#include "Statistic.h"
#include <conio.h>
#include <Windows.h>
//#include <iomanip>


int Statistic::statsX = 0;
int Statistic::statsY = 0;
const int Statistic::MAX_VIE = 4;
const int Statistic::MAX_ENERGIE = 12;
int Statistic::tabScoreDigit[15] = { NULL };
Statistic::Statistic()
{
	Statistic::statsX = Config::fenetreXY.getPositionX() - Config::separationEcran - 1;
	Statistic::statsY = Config::fenetreXY.getPositionY() - 2;
	this->score = 0;
	this->playerVie = 1;
	this->playerEnergie = 5;
	time_t tempsDebutPartie = time(0);
	this->initStats();
}

void Statistic::afficherScore(int score, int x, int y) {
	UIKit::color(Config::B_BLACK + Config::T_WHITE);
	int nombreUnite = 1;
	int acc = 10;

	while (score / acc >= 1) {
		acc *= 10;
		nombreUnite++;
	}
	acc /= 10;
	int result = 0;
	for (int i = 0; i < nombreUnite; i++) {
		Statistic::tabScoreDigit[i] = (score % (acc * 10)) / acc;
		acc /= 10;
	}
	for (int k = 0; k < nombreUnite; k++) {
		for (int i = 0; i < 3; i++) {
			UIKit::gotoXY(x, y + i);
			for (int j = 0; j < 3; j++)
				cout << Config::DIGITAL_TABLE[Statistic::tabScoreDigit[k]][i][j];
		}
		x += 4;
	}

}


void Statistic::afficherDuree(double temps, int posX, int posY) {
	UIKit::color(Config::B_BLACK + Config::T_WHITE);
	//UIKit::gotoXY(statsX + 2, 3);
	int tableChrono[3];
	tableChrono[0] = (int)temps / 60;
	tableChrono[1] = ((int)temps % 60) / 10;
	tableChrono[2] = ((int)temps % 60) % 10;

	//Affiche les minutes
	int cursorX = posX;

	for (int i = 0; i < 3; i++) {
		UIKit::gotoXY(cursorX + 2, posY + i);
		for (int j = 0; j < 3; j++)
			cout << Config::DIGITAL_TABLE[tableChrono[0]][i][j];
	}
	cursorX += 6;
	//Afiche les secondes
	for (int k = 1; k < 3; k++) {
		for (int i = 0; i < 3; i++) {
			UIKit::gotoXY(cursorX + 2, posY + i);
			for (int j = 0; j < 3; j++)
				cout << Config::DIGITAL_TABLE[tableChrono[k]][i][j];
		}
		cursorX += 4;
	}
	//Affiche les deux points
	for (int i = 0; i < 2; i++) {
		UIKit::gotoXY(posX + 6, posY + 1 + i); cout << "*";
	}
	//cout << "TEMPS : " <<((int)temps / 60)<< ":" << setfill('0') << setw(2) << ((int)temps % 60);
}

void Statistic::initStats() {
	this->barVie(Statistic::MAX_VIE);
	this->barEnergie(0);

}

void Statistic::barVie(int nbvie) {

	int hauteurVie = 3;
	int largeurVie = 15;
	int temp = Statistic::statsY;
	for (int i = 0; i < Statistic::MAX_VIE; i++) {
		UIKit::color(nbvie >= i + 1 ? Config::B_L_GREEN + Config::T_D_RED : Config::B_D_GREEN + Config::T_D_RED);

		UIKit::gotoXY(Statistic::statsX, temp);
		for (int j = 0; j < largeurVie; j++) {
			cout << "_";
		}
		for (int j = 1; j < hauteurVie; j++) {
			UIKit::gotoXY(Statistic::statsX, temp - j);
			for (int k = 0; k < largeurVie; k++) {
				cout << " ";
			}
		}
		temp -= hauteurVie;
		UIKit::color(Config::B_BLACK + Config::T_BLACK);

	}
	//Statistic::statsY = temp;
}

void Statistic::barEnergie(int nbEnergie) {

	int hauteurEnergie = 1;
	int largeurEnergie = 15;
	int maxStatsX = Config::fenetreXY.getPositionX() - 3;
	int maxStatsY = Config::fenetreXY.getPositionY() - 2;

	for (int i = 0; i < Statistic::MAX_ENERGIE; i++) {
		UIKit::color(nbEnergie > i ? Config::B_L_TURQUOISE + Config::T_BLACK : Config::B_D_TURQUOISE + Config::T_BLACK);

		UIKit::gotoXY(maxStatsX - largeurEnergie, maxStatsY);
		for (int k = 0; k < largeurEnergie; k++) {
			cout << "_";
		}
		for (int j = 1; j < hauteurEnergie; j++) {
			UIKit::gotoXY(maxStatsX - largeurEnergie, maxStatsY - j);
			for (int k = 0; k < largeurEnergie; k++) {
				cout << " ";
			}
		}
		maxStatsY -= hauteurEnergie;
		UIKit::color(Config::B_BLACK + Config::T_BLACK);
	}
}

Statistic::~Statistic()
{
}

bool Statistic::pauseWindow() {

	int x = 186, y = 10;
	UIKit::color(Config::B_BLACK + Config::T_L_PURPLE);
	UIKit::gotoXY(x, y);		cout << "  PAUSE";
	UIKit::color(Config::B_BLACK + Config::T_L_YELLOW);

	UIKit::gotoXY(x, y + 2);	cout << "Continuer";
	UIKit::gotoXY(x, y + 4);	cout << " Quitter";
	int key = -1;
	int choix = 1;
	UIKit::cadre(x - 1, y - 1 + (choix * 2), x + 9, y + 1 + (choix * 2), 3);
	do {
		if (_kbhit()) {
			key = _getch();
			if (key == 'w' && choix != 1) {
				UIKit::cadre(x - 1, y - 1 + (choix * 2), x + 9, y + 1 + (choix * 2), 0);
				choix--;
				UIKit::cadre(x - 1, y - 1 + (choix * 2), x + 9, y + 1 + (choix * 2), 3);
			}
			else if (key == 's' && choix != 2) {
				UIKit::cadre(x - 1, y - 1 + (choix * 2), x + 9, y + 1 + (choix * 2), 0);
				choix++;
				UIKit::cadre(x - 1, y - 1 + (choix * 2), x + 9, y + 1 + (choix * 2), 3);
			}
			if (key == 13) {
				for (int i = 0; i < 7; i++) {
					UIKit::gotoXY(x - 1, y + i); cout << "           ";
				}
				
				switch (choix) {
				case 1: return true;
					break;
				case 2: return false;
					break;
				}
			}
		}

	} while (true);
	return false;
}