#include "GOMenu.h"
#include "UIKit.h"
#include "Config.h"
#include <conio.h>
#include "Score.h"
#include <string>

int GOMenu::nbChar = 0;
int GOMenu::scoreFieldX = 89;
int GOMenu::textFieldX = 81;
int GOMenu::textFieldY = 0;
int GOMenu::tabScoreDigit[15] = { NULL };
bool GOMenu::enterPress = false;

char GOMenu::tabInput[5] = { NULL };
int GOMenu::cursorText = GOMenu::textFieldX + 2;

void GOMenu::initGOMenu(int partieScore) {
	GOMenu::enterPress = false;
	for (int i = 0; i < 5; i++) {
		GOMenu::tabInput[i] = '\0';
	}
	GOMenu::textFieldX = 81;
	GOMenu::textFieldY = 23;
	GOMenu::nbChar = 0;
	GOMenu::cursorText = GOMenu::textFieldX + 2;
	GOMenu::gameOver();
	GOMenu::putScore(partieScore, 100, 19);
	bool retour = false;
	do {
		retour = GOMenu::buttonMainMenu();
		if (!retour) {
			GOMenu::zoneTextInput();
		}
	} while (!retour);


	Score::initScore(std::string(tabInput), partieScore);
}
GOMenu::GOMenu()
{


}
bool GOMenu::buttonMainMenu() {
	int x = 79;
	int y = 30;
	UIKit::color(enterPress ? Config::T_L_PURPLE : Config::T_WHITE);
	UIKit::gotoXY(x, y++); cout << "  __  __       _       __  __                  \n";
	UIKit::gotoXY(x, y++); cout << " |  \\/  |     (_)     |  \\/  |                 \n";
	UIKit::gotoXY(x, y++); cout << " | \\  / | __ _ _ _ __ | \\  / | ___ _ __  _   _ \n";
	UIKit::gotoXY(x, y++); cout << " | |\\/| |/ _` | | '_ \\| |\\/| |/ _ \\ '_ \\| | | |\n";
	UIKit::gotoXY(x, y++); cout << " | |  | | (_| | | | | | |  | |  __/ | | | |_| |\n";
	UIKit::gotoXY(x, y++); cout << " |_|  |_|\\__,_|_|_| |_|_|  |_|\\___|_| |_|\\__,_|\n";
	int key = 0;
	if (GOMenu::enterPress) {
		while (enterPress) {
			while (_kbhit()) {}
			int key = tolower(_getch());
			if (key == 13) {
				enterPress = false;
				return true;
			}
			else if (GetKeyState(VK_ESCAPE) & 0x8000) {
				enterPress = false;
				GOMenu::buttonMainMenu();
			}
		}
	}

	return false;
}


void GOMenu::gameOver() {
	int x = 44;
	int y = 10;
	UIKit::color(Config::B_BLACK + Config::T_GREY);
	UIKit::gotoXY(x, y++); cout << "  ,ad8888ba,         db         88b           d88  88888888888  ,ad8888ba,   8b           d8  88888888888  88888888ba   ";
	UIKit::gotoXY(x, y++); cout << " d8\"'    `\"8b       d88b        888b         d888  88          d8\"'    `\"8b  `8b         d8'  88           88      \"8b  ";
	UIKit::gotoXY(x, y++); cout << "d8'                d8'`8b       88`8b       d8'88  88         d8'        `8b  `8b       d8'   88           88      ,8P  ";
	UIKit::gotoXY(x, y++); cout << "88                d8'  `8b      88 `8b     d8' 88  88aaaaa    88          88   `8b     d8'    88aaaaa      88aaaaaa8P'  ";
	UIKit::gotoXY(x, y++); cout << "88      88888    d8YaaaaY8b     88  `8b   d8'  88  88\"\"\"\"\"    88          88    `8b   d8'     88\"\"\"\"\"      88\"\"\"\"88'    ";
	UIKit::gotoXY(x, y++); cout << "Y8,        88   d8\"\"\"\"\"\"\"\"8b    88   `8b d8'   88  88         Y8,        ,8P     `8b d8'      88           88    `8b    ";
	UIKit::gotoXY(x, y++); cout << " Y8a.    .a88  d8'        `8b   88    `888'    88  88          Y8a.    .a8P       `888'       88           88     `8b   ";
	UIKit::gotoXY(x, y++); cout << "  `\"Y88888P\"  d8'          `8b  88     `8'     88  88888888888  `\"Y8888Y\"'         `8'        88888888888  88      `8b  ";
	UIKit::color(00);

}
void GOMenu::zoneTextInput() {
	enterPress = false;
	int x = GOMenu::textFieldX;
	int y = GOMenu::textFieldY;
	int hauteur = 5;
	int largeur = 41;
	UIKit::cadre(x, y, x + largeur, y + hauteur, Config::B_BLACK + Config::T_L_TURQUOISE);
	while (!enterPress) {
		while (!_kbhit()) {}
		int key = toupper(_getch());
		if (key != 13)
		{
			if (key >= 65 && key <= 90 && nbChar < 4) {
				tabInput[nbChar] = key;
				nbChar++;
				putChar(key - 65);
			}
			else if (key == 8 && nbChar > 0) {
				nbChar--;
				tabInput[nbChar] = NULL;

				removeChar();
			}
		}
		else {
			enterPress = true;
		}


	}
}
void GOMenu::putChar(int key) {

	int y = 24;
	UIKit::color(Config::T_L_PURPLE);
	for (int i = 0; i < 4; i++) {
		UIKit::gotoXY(GOMenu::cursorText, y + i);
		for (int j = 0; j < 8; j++)
			cout << Config::ASCII_TABLE[key][i][j];
	}
	GOMenu::cursorText += 10;

}
void GOMenu::removeChar() {

	int y = 24;

	UIKit::color(0);
	for (int i = 0; i < 4; i++) {
		UIKit::gotoXY(GOMenu::cursorText - 10, y + i);
		for (int j = 0; j < 8; j++)
			cout << " ";
	}
	GOMenu::cursorText -= 10;


}
void GOMenu::putScore(int score, int x, int y) {

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
		GOMenu::tabScoreDigit[i] = (score % (acc * 10)) / acc;
		acc /= 10;
	}
	x -= (2 * (nombreUnite - 1));
	for (int k = 0; k < nombreUnite; k++) {
		for (int i = 0; i < 3; i++) {
			UIKit::gotoXY(x, y + i);
			for (int j = 0; j < 3; j++)
				cout << Config::DIGITAL_TABLE[GOMenu::tabScoreDigit[k]][i][j];
		}
		x += 4;
	}
}
void GOMenu::removeScore() {

}

GOMenu::~GOMenu()
{
}
