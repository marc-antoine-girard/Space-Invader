#include "Menu.h"
#include "Config.h"
#include "UIKit.h"
#include <conio.h>
#include <time.h>
#include "GOMenu.h"
#include "Score.h"

int Menu::choix = 1;
int Menu::menuLvl = Menu::PRINCIPAL;
int Menu::vaisseauMenuX = 70, Menu::vaisseauMenuY = 20;
int Menu::logoX = 20, Menu::logoY = 7;
int Menu::choixPosX = 150, Menu::choixPosY = 25;
int Menu::spaceBtwChoice = 7;
char Menu::customKey[4];
int Menu::maxChoix = 3;
int Menu::keyX = Menu::vaisseauMenuX - 50, Menu::keyY = Menu::vaisseauMenuY;

bool Menu::choixManager() {
	bool isOver = false;
	while (true) {
		int key = keyPressed();
		clearMenu();

		if (key == -1) {
			if (Menu::menuLvl == 1) {
				Menu::choix = 3;
			}
			else if (Menu::menuLvl == Menu::INSTRUCTION) {
				Menu::menuLvl = Menu::PRINCIPAL;
				Menu::choix = 1;
				Menu::maxChoix = 3;
			}
			else {
				Menu::choix = 1;
				Menu::menuLvl--;
			}
		}
		else if (key == 1) {
			if (Menu::menuLvl == Menu::PRINCIPAL) {
				switch (Menu::choix) {
				case 1: Menu::menuLvl = Menu::DIFFICULTE;
					break;
				case 2: Menu::menuLvl = Menu::INSTRUCTION;
					Menu::maxChoix = 5;

					break;
				case 3: return true;
					break;
				}
				Menu::choix = 1;
			}
			else if (Menu::menuLvl == Menu::DIFFICULTE) {
				Config::difficulter = Menu::choix;
				return false;
			}
			else if (Menu::menuLvl == Menu::INSTRUCTION) {
				if (Menu::choix == 5) {
					memcpy(Config::customKey, Config::CUSTOM_KEY, 4);
				}
				else {
					instructionMenu(true, true);
					changerTouche();
				}

			}
		}

		showMenu();
		Sleep(80);
	}
}
void Menu::changerTouche() {

	UIKit::curseurVisible(true);
	UIKit::gotoXY(Menu::keyX + 4, (Menu::keyY + 3) + ((Menu::choix - 1) * 7));
	cout << " ";
	char key = Config::customKey[Menu::choix - 1];
	char tempKey = Config::customKey[Menu::choix - 1];
	char newKey = Config::customKey[Menu::choix - 1];

	UIKit::color(Config::T_L_GREEN);
	//Config::customKey[Menu::choix - 1] = NULL;
	do {
		UIKit::gotoXY(Menu::keyX + 4, (Menu::keyY + 3) + ((Menu::choix - 1) * 7));
		tempKey = tolower(_getch());

		if (tempKey != 13) {
			cout << (char)toupper(tempKey);
			newKey = tempKey;
		}

	} while (tempKey != 13);
	for (int i = 0; i < (sizeof(Config::customKey) / sizeof(*Config::customKey)); i++) {
		if (newKey == Config::customKey[i] && i != Menu::choix - 1) {
			Config::customKey[Menu::choix - 1] = key;
			break;
		}
		else {
			Config::customKey[Menu::choix - 1] = newKey;
		}
	}

	UIKit::curseurVisible(false);

}
bool Menu::initMenu() {
	PlaySound("BackSound.wav", NULL, SND_FILENAME | SND_LOOP| SND_ASYNC);
	removeScrollBar();
	Score::afficherLesScores(25, 30, true);
	etoile(Config::fenetreXY.getPositionX(), Config::fenetreXY.getPositionY());
	logo(Menu::logoX, Menu::logoY);
	laser(Menu::vaisseauMenuX + 14, vaisseauMenuY - 4);
	vaisseauMenu(Menu::vaisseauMenuX, Menu::vaisseauMenuY);
	menuChoix(true);
	removeScrollBar();

	return choixManager();
}


void Menu::etoile(int fenetreX, int fenetreY) {
	const int NB_ETOILE = 100;
	int tabEtoileX[NB_ETOILE];
	int tabEtoileY[NB_ETOILE];
	UIKit::color(Config::T_WHITE);

	for (int i = 0; i < NB_ETOILE; i++) {
		tabEtoileX[i] = rand() % (fenetreX - 1) + 1;
		tabEtoileY[i] = rand() % (fenetreY - 1) + 1;
		UIKit::gotoXY(tabEtoileX[i], tabEtoileY[i]);
		cout << "*";
	}
	UIKit::color(Config::B_BLACK + Config::T_BLACK);

}
int Menu::keyPressed() {
	int niveauMenu = Menu::menuLvl;
	char touche = -1;
	while (!_kbhit()) {}
	touche = tolower(_getch());

	if (touche == 'w') {
		Menu::choix = Menu::choix <= 1 ? Menu::maxChoix : Menu::choix - 1;
	}
	else if (touche == 's') {
		Menu::choix = Menu::choix >= Menu::maxChoix ? 1 : Menu::choix + 1;
	}

	else if (GetKeyState(VK_ESCAPE) & 0x8000) {
		return -1;
	}
	else if (touche == Config::ENTER) {
		return 1;
	}
	return 0;

}
void Menu::clearMenu() {
	switch (Menu::menuLvl) {
	case Menu::PRINCIPAL: Menu::menuChoix(false);
		Score::afficherLesScores(25, 30, false);
		break;
	case Menu::DIFFICULTE: Menu::playChoix(false);
		break;
	case Menu::INSTRUCTION: Menu::instructionMenu(false, false);
		break;
	case Menu::TOUCHE: Menu::Menu::instructionMenu(false, false);
		break;
	}
}
void Menu::showMenu() {
	switch (Menu::menuLvl) {
	case Menu::PRINCIPAL: Menu::menuChoix(true);
		Score::afficherLesScores(25, 30, true);
		break;
	case Menu::DIFFICULTE: Menu::playChoix(true);
		break;
	case Menu::INSTRUCTION: Menu::instructionMenu(true, false);
		break;
	case Menu::TOUCHE: Menu::Menu::instructionMenu(true, false);
		break;
	}
}

void Menu::instructionMenu(bool killColor, bool actif) {
	int x = Menu::keyX;
	int y = Menu::keyY;
	int highlight = Config::T_L_PURPLE;
	if (actif) {
		highlight = Config::T_L_YELLOW;
	}
	for (int i = 0; i < Menu::maxChoix - 1; i++) {
		UIKit::color((Menu::choix == i + 1 ? highlight : Config::couleurTextBase) * killColor);
		UIKit::gotoXY(x, y++); cout << " _______ ";
		UIKit::gotoXY(x, y++); cout << "|\\     /|";
		UIKit::gotoXY(x, y++); cout << "| +---+ |";
		UIKit::gotoXY(x, y++); cout << "| | ";
		UIKit::color(Config::T_L_PURPLE* killColor);
		cout << (char)toupper(Config::customKey[i]);
		UIKit::color((Menu::choix == i + 1 ? highlight : Config::couleurTextBase) * killColor);
		cout << " | |";
		UIKit::gotoXY(x, y++); cout << "| +---+ |";
		UIKit::gotoXY(x, y++); cout << "|/_____\\|";

		y += 1;
	}
	UIKit::color((Menu::choix == 5 ? highlight : Config::T_WHITE) * killColor);
	UIKit::gotoXY(x, y++); cout << "REINITIALISER?";

	int textX = Menu::keyX + 12;
	int textY = Menu::keyY;

	UIKit::color((Menu::choix == 1 ? highlight : Config::T_GREY) * killColor);

	UIKit::gotoXY(textX, textY++); cout << "   _____                  _          ";
	UIKit::gotoXY(textX, textY++); cout << "  / ____|                | |         ";
	UIKit::gotoXY(textX, textY++); cout << " | |  __  __ _ _   _  ___| |__   ___ ";
	UIKit::gotoXY(textX, textY++); cout << " | | |_ |/ _` | | | |/ __| '_ \\ / _ \\";
	UIKit::gotoXY(textX, textY++); cout << " | |__| | (_| | |_| | (__| | | |  __/";
	UIKit::gotoXY(textX, textY++); cout << "  \\_____|\\__,_|\\__,_|\\___|_| |_|\\___|";

	textY += 1;
	UIKit::color((Menu::choix == 2 ? highlight : Config::T_GREY) * killColor);

	UIKit::gotoXY(textX, textY++); cout << "  _____            _ _       ";
	UIKit::gotoXY(textX, textY++); cout << " |  __ \\          (_) |      ";
	UIKit::gotoXY(textX, textY++); cout << " | |  | |_ __ ___  _| |_ ___ ";
	UIKit::gotoXY(textX, textY++); cout << " | |  | | '__/ _ \\| | __/ _ \\";
	UIKit::gotoXY(textX, textY++); cout << " | |__| | | | (_) | | ||  __/";
	UIKit::gotoXY(textX, textY++); cout << " |_____/|_|  \\___/|_|\\__\\___|";

	textY += 1;
	UIKit::color((Menu::choix == 3 ? highlight : Config::T_GREY) * killColor);

	UIKit::gotoXY(textX, textY++); cout << "  _______         _           ";
	UIKit::gotoXY(textX, textY++); cout << " |__   __|       | |          ";
	UIKit::gotoXY(textX, textY++); cout << "    | |_   _ _ __| |__   ___  ";
	UIKit::gotoXY(textX, textY++); cout << "    | | | | | '__| '_ \\ / _ \\ ";
	UIKit::gotoXY(textX, textY++); cout << "    | | |_| | |  | |_) | (_) |";
	UIKit::gotoXY(textX, textY++); cout << "    |_|\\__,_|_|  |_.__/ \\___/ ";

	textY += 1;
	UIKit::color((Menu::choix == 4 ? highlight : Config::T_GREY) * killColor);

	UIKit::gotoXY(textX, textY++); cout << "  _______ _               ";
	UIKit::gotoXY(textX, textY++); cout << " |__   __(_)              ";
	UIKit::gotoXY(textX, textY++); cout << "    | |   _ _ __ ___ _ __ ";
	UIKit::gotoXY(textX, textY++); cout << "    | |  | | '__/ _ \\ '__|";
	UIKit::gotoXY(textX, textY++); cout << "    | |  | | | |  __/ |   ";
	UIKit::gotoXY(textX, textY++); cout << "    |_|  |_|_|  \\___|_|   ";


	UIKit::color(Config::B_BLACK + Config::T_BLACK);
	Menu::instructionTextMenu(killColor);
}

void Menu::instructionTextMenu(bool killColor) {

	int x = Menu::vaisseauMenuX + 65;
	int y = Menu::vaisseauMenuY;

	UIKit::color((Config::B_BLACK + Config::T_L_YELLOW)*killColor);
	UIKit::gotoXY(x, y); cout << "  ___ _  _ ___ _____ ___ _   _  ___ _____ ___ ___  _  _ ";
	UIKit::gotoXY(x, y + 1); cout << " |_ _| \\| / __|_   _| _ | | | |/ __|_   _|_ _/ _ \\| \\| |";
	UIKit::gotoXY(x, y + 2); cout << "  | || .` \\__ \\ | | |   | |_| | (__  | |  | | (_) | .` |";
	UIKit::gotoXY(x, y + 3); cout << " |___|_|\\_|___/ |_| |_|_\\\\___/ \\___| |_| |___\\___/|_|\\_|";

	x = Menu::vaisseauMenuX + 60;
	y = Menu::vaisseauMenuY + 7;

	UIKit::color((Config::B_BLACK + Config::T_L_TURQUOISE)*killColor);
	UIKit::gotoXY(x, y); cout << " - Eviter les lasers ennemies avec les touches de gauche et droite";
	UIKit::gotoXY(x, y + 2); cout << "      - Detruiser le plus de vaisseau possible en 5 minutes";
	UIKit::gotoXY(x, y + 4); cout << "          - Utiliser le mode Turbo pour tirer 3 lasers";
	UIKit::gotoXY(x, y + 6); cout << "    - Activer le mode Turbo consomme de l'energie par seconde";
	UIKit::gotoXY(x, y + 8); cout << "         - Les ennemies peuvent laisser tomber des items";

	UIKit::color((Config::B_BLACK + Config::T_L_RED)*killColor);
	UIKit::gotoXY(x, y + 10); cout << "  - Survivre pour gagner, tuer pour gagner, gagner pour gagner. -";
	UIKit::color((Config::B_BLACK + Config::T_L_YELLOW)*killColor);

	int itemX = x + 24;
	UIKit::gotoXY(itemX, y + 12); cout << "  __  ____  ____  _  _ ";
	UIKit::gotoXY(itemX, y + 13); cout << " (  )(_  _)(  __)( \\/ )";
	UIKit::gotoXY(itemX, y + 14); cout << "  )(   )(   ) _) / \\/ \\";
	UIKit::gotoXY(itemX, y + 15); cout << " (__) (__) (____)\\_)(_/";
	//UIKit::gotoXY(itemX, y + 16); cout << "                               - ITEM -";
	UIKit::color((Config::B_BLACK + Config::T_L_GREEN)*killColor);
	UIKit::gotoXY(x, y + 18); cout << "                        VIE";
	UIKit::color((Config::B_BLACK + Config::T_L_TURQUOISE)*killColor);
	cout << "               ENERGIE         ";
	UIKit::color((Config::B_BLACK + Config::T_L_GREEN)*killColor);
	UIKit::gotoXY(x, y + 19); cout << "                         *";
	UIKit::color((Config::B_BLACK + Config::T_L_TURQUOISE)*killColor);
	cout << "                   *";

	UIKit::color(Config::B_BLACK + Config::T_BLACK);
}

void Menu::vaisseauMenu(int x, int y) {

	system("Color 00");
	UIKit::color(Config::B_WHITE + Config::T_GREY);
	UIKit::gotoXY(x + 12, y); cout << " ";
	UIKit::gotoXY(x + 12, y + 1); cout << " ";
	UIKit::gotoXY(x + 11, y + 2); cout << "  ";
	UIKit::gotoXY(x + 10, y + 3); cout << "   @";
	UIKit::gotoXY(x + 9, y + 4); cout << "   @";
	UIKit::gotoXY(x + 8, y + 5); cout << "   #";
	UIKit::gotoXY(x + 7, y + 6); cout << "   #";
	for (int i = 7; i <= 13; i++) {
		UIKit::gotoXY(x + 6, y + i); cout << "    ";
	}
	for (int i = 14; i <= 15; i++) {
		UIKit::gotoXY(x + 5, y + i); cout << "   ";
	}
	UIKit::gotoXY(x + 4, y + 16); cout << "   ";
	UIKit::gotoXY(x + 3, y + 17); cout << "   ";
	UIKit::gotoXY(x + 2, y + 18); cout << "   ";
	UIKit::gotoXY(x + 2, y + 19); cout << "  ";
	UIKit::gotoXY(x + 2, y + 20); cout << "  ";

	// Colorisation primaire gris foncé
	UIKit::color(Config::B_GREY);
	UIKit::gotoXY(x + 13, y); cout << "     ";
	UIKit::gotoXY(x + 13, y + 1); cout << "     ";
	UIKit::gotoXY(x + 13, y + 2); cout << "     ";
	UIKit::gotoXY(x + 14, y + 3); cout << "     ";
	UIKit::gotoXY(x + 13, y + 4); cout << "     ";
	UIKit::gotoXY(x + 12, y + 5); cout << "       ";
	UIKit::gotoXY(x + 11, y + 6); cout << "         ";
	UIKit::gotoXY(x + 10, y + 7); cout << "           ";
	UIKit::gotoXY(x + 9, y + 8); cout << "              ";
	UIKit::gotoXY(x + 10, y + 9); cout << "             ";
	UIKit::gotoXY(x + 8, y + 10); cout << "               ";
	UIKit::gotoXY(x + 10, y + 11); cout << "              ";
	UIKit::gotoXY(x + 8, y + 12); cout << "               ";
	UIKit::gotoXY(x + 8, y + 13); cout << "                ";
	UIKit::gotoXY(x + 7, y + 14); cout << "                 ";
	UIKit::gotoXY(x + 8, y + 15); cout << "                ";
	UIKit::gotoXY(x + 7, y + 16); cout << "                  ";
	UIKit::gotoXY(x + 6, y + 17); cout << "                   @";
	UIKit::gotoXY(x + 5, y + 18); cout << "                     #";
	UIKit::gotoXY(x + 4, y + 19); cout << "                      #";
	UIKit::gotoXY(x + 4, y + 20); cout << "                      #";
	UIKit::gotoXY(x + 7, y + 22); cout << "                 ";

	UIKit::color(Config::B_D_BLUE + Config::T_GREY);
	UIKit::gotoXY(x + 18, y); cout << " ";
	UIKit::gotoXY(x + 18, y + 1); cout << " ";
	UIKit::gotoXY(x + 18, y + 2); cout << "  ";
	UIKit::gotoXY(x + 17, y + 3); cout << "@   ";
	UIKit::gotoXY(x + 18, y + 4); cout << "@   ";
	UIKit::gotoXY(x + 19, y + 5); cout << "@   ";
	UIKit::gotoXY(x + 20, y + 6); cout << "@   ";
	UIKit::gotoXY(x + 21, y + 7); cout << "@   ";
	for (int i = 8; i <= 13; i++) {
		UIKit::gotoXY(x + 23, y + i); cout << "  ";
	}
	UIKit::gotoXY(x + 24, y + 14); cout << "  ";
	UIKit::gotoXY(x + 24, y + 15); cout << "  ";
	UIKit::gotoXY(x + 25, y + 16); cout << "  ";
	UIKit::gotoXY(x + 26, y + 17); cout << "  ";
	UIKit::gotoXY(x + 27, y + 18); cout << "  ";
	UIKit::gotoXY(x + 27, y + 19); cout << "  ";
	UIKit::gotoXY(x + 27, y + 20); cout << "  ";

	// Colorisation primaire bleu foncé Moteur

	UIKit::gotoXY(x + 7, y + 21); cout << "                 ";

	//Feu moteur
	UIKit::color(Config::B_D_RED);
	UIKit::gotoXY(x + 8, y + 23); cout << "               ";
	UIKit::gotoXY(x + 9, y + 24); cout << "             ";
	UIKit::gotoXY(x + 10, y + 25); cout << "           ";
	UIKit::gotoXY(x + 11, y + 26); cout << "         ";
	UIKit::gotoXY(x + 13, y + 30); cout << "     ";
	UIKit::color(Config::B_L_RED);
	UIKit::gotoXY(x + 9, y + 23); cout << "             ";
	UIKit::gotoXY(x + 10, y + 24); cout << "           ";
	UIKit::gotoXY(x + 11, y + 25); cout << "         ";
	for (int i = 26; i <= 29; i++) {
		UIKit::gotoXY(x + 12, y + i); cout << "       ";
	}
	UIKit::color(Config::B_L_YELLOW); //Couleur jaune clair
	UIKit::gotoXY(x + 11, y + 23); cout << "         ";
	UIKit::gotoXY(x + 12, y + 24); cout << "       ";
	UIKit::gotoXY(x + 12, y + 25); cout << "       ";
	UIKit::gotoXY(x + 14, y + 26); cout << "   ";
	UIKit::gotoXY(x + 14, y + 27); cout << "   ";
	UIKit::gotoXY(x + 14, y + 28); cout << "   ";

	UIKit::color(Config::B_BLACK + Config::T_BLACK);
}
void Menu::playChoix(bool killColor) {
	int x = Menu::choixPosX - 2;
	int y = Menu::choixPosY - 1;

	UIKit::color((Menu::choix == 1 ? Config::T_L_TURQUOISE : Config::couleurTextBase) * killColor);
	UIKit::gotoXY(x, y);     std::cout << " .____                  .         ";
	UIKit::gotoXY(x, y + 1);     std::cout << " /       ___    ___  `  |     ___ ";
	UIKit::gotoXY(x, y + 2);     std::cout << " |__.   /   ` .'   ` |  |   .'   `";
	UIKit::gotoXY(x, y + 3);     std::cout << " |     |    | |      |  |   |----'";
	UIKit::gotoXY(x, y + 4);     std::cout << " /     `.__/|  `._.' / /\\__ `.___,";
	x -= 3;
	y += Menu::spaceBtwChoice + 1;
	UIKit::color((Menu::choix == 2 ? Config::T_L_PURPLE : Config::couleurTextBase) * killColor);
	UIKit::gotoXY(x, y - 1); std::cout << "  _   _  ___  ____  __  __    _    _     ";
	UIKit::gotoXY(x, y + 0); std::cout << " | \\ | |/ _ \\|  _ \\|  \\/  |  / \\  | |    ";
	UIKit::gotoXY(x, y + 1); std::cout << " |  \\| | | | | |_) | |\\/| | / _ \\ | |    ";
	UIKit::gotoXY(x, y + 2); std::cout << " | |\\  | |_| |  _ <| |  | |/ ___ \\| |___ ";
	UIKit::gotoXY(x, y + 3); std::cout << " |_| \\_|\\___/|_| \\_\\_|  |_/_/   \\_\\_____|";

	x -= 5;
	y += Menu::spaceBtwChoice;
	UIKit::color((Menu::choix == 3 ? Config::T_L_RED : Config::couleurTextBase) * killColor);

	UIKit::gotoXY(x, y + 0); std::cout << "8888b.  88 888888 888888 88  dP\"\"b8 88 88     888888 ";
	UIKit::gotoXY(x, y + 1); std::cout << " 8I  Yb 88 88__   88__   88 dP   `\" 88 88     88__   ";
	UIKit::gotoXY(x, y + 2); std::cout << " 8I  dY 88 88\"\"   88\"\"   88 Yb      88 88  .o 88\"\"   ";
	UIKit::gotoXY(x, y + 3); std::cout << "8888Y\"  88 88     88     88  YboodP 88 88ood8 888888 ";
	UIKit::color(Config::B_BLACK + Config::T_BLACK);

}

void Menu::menuChoix(bool killColor) {

	int x = choixPosX;
	int y = choixPosY;
	UIKit::color((Menu::choix == 1 ? Config::T_L_GREEN + Config::B_BLACK : Config::couleurTextBase) * killColor);
	/*Bouton Play*/
	UIKit::gotoXY(x, y);     std::cout << "88\"\"Yb 88        db    Yb  dP ";
	UIKit::gotoXY(x, y + 1); std::cout << "88__dP 88       dPYb    YbdP  ";
	UIKit::gotoXY(x, y + 2); std::cout << "88\"\"\"  88  .o  dP__Yb    88   ";
	UIKit::gotoXY(x, y + 3); std::cout << "88     88ood8 dP\"\"\"\"Yb   88    ";
	/*Bouton Instruction*/
	UIKit::color((Menu::choix == 2 ? Config::T_L_YELLOW + Config::B_BLACK : Config::couleurTextBase) * killColor);
	x -= 20;
	y += spaceBtwChoice;
	UIKit::gotoXY(x, y + 0); std::cout << "88 88b 88 .dP\"Y8 888888 88\"\"Yb 88   88  dP\"\"b8 888888 88  dP\"Yb  88b 88 ";
	UIKit::gotoXY(x, y + 1); std::cout << "88 88Yb88 `Ybo.\"   88   88__dP 88   88 dP   `\"   88   88 dP   Yb 88Yb88 ";
	UIKit::gotoXY(x, y + 2); std::cout << "88 88 Y88 o.`Y8b   88   88\"Yb  Y8   8P Yb        88   88 Yb   dP 88 Y88 ";
	UIKit::gotoXY(x, y + 3); std::cout << "88 88  Y8 8bodP'   88   88  Yb `YbodP'  YboodP   88   88  YbodP  88  Y8 ";
	/*Bouton Quitter*/
	UIKit::color((Menu::choix == 3 ? Config::T_L_RED + Config::B_BLACK : Config::couleurTextBase) * killColor);
	x += 12;
	y += spaceBtwChoice;
	UIKit::gotoXY(x, y + 0); std::cout << " dP\"Yb  88   88 88 888888 888888 888888 88\"\"Yb ";
	UIKit::gotoXY(x, y + 1); std::cout << "dP   Yb 88   88 88   88     88   88__   88__dP ";
	UIKit::gotoXY(x, y + 2); std::cout << "Yb b dP Y8   8P 88   88     88   88\"\"   88\"Yb  ";
	UIKit::gotoXY(x, y + 3); std::cout << " `\"YoYo `YbodP' 88   88     88   888888 88  Yb ";
	UIKit::color(Config::B_BLACK + Config::T_BLACK);

}

void Menu::removeScrollBar() {
	UIKit::color(Config::B_BLACK + Config::T_BLACK);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};

	SetConsoleScreenBufferSize(handle, new_size);
	UIKit::color(Config::B_BLACK + Config::T_BLACK);

}

void Menu::laser(int posLaserX, int posLaserY) {
	UIKit::color(Config::B_D_GREEN);
	for (int i = 0; i < 10; i++) {
		UIKit::gotoXY(posLaserX, posLaserY - i); cout << "   ";
	}
	UIKit::color(Config::B_L_GREEN);
	for (int i = 0; i < 10; i++) {
		UIKit::gotoXY(posLaserX + 1, posLaserY - i); cout << "|";
	}
	UIKit::color(Config::B_BLACK + Config::T_BLACK);

}

void Menu::logo(int x, int y) {

	UIKit::color(Config::T_L_PURPLE);
	UIKit::gotoXY(x, y);         cout << " ad88888ba                                                       88                                                 88                                     ";
	UIKit::gotoXY(x, y + 1);     cout << "d8\"     \"8b                                                      88                                                 88                                     ";
	UIKit::gotoXY(x, y + 2);     cout << "Y8,                                                              88                                                 88                                     ";
	UIKit::gotoXY(x, y + 3);     cout << "`Y8aaaaa,    8b,dPPYba,   ,adPPYYba,   ,adPPYba,   ,adPPYba,     88  8b,dPPYba,   8b       d8  ,adPPYYba,   ,adPPYb,88   ,adPPYba,  8b,dPPYba,  ,adPPYba,  ";
	UIKit::gotoXY(x, y + 4);     cout << "  `\"\"\"\"\"8b,  88P'    \"8a  \"\"     `Y8  a8\"     \"\"  a8P_____88     88  88P'   `\"8a  `8b     d8'  \"\"     `Y8  a8\"    `Y88  a8P_____88  88P'   \"Y8  I8[    \"\"  ";
	UIKit::gotoXY(x, y + 5);     cout << "        `8b  88       d8  ,adPPPPP88  8b          8PP\"\"\"\"\"\"\"     88  88       88   `8b   d8'   ,adPPPPP88  8b       88  8PP\"\"\"\"\"\"\"  88           `\"Y8ba,   ";
	UIKit::gotoXY(x, y + 6);     cout << "Y8a     a8P  88b,   ,a8\"  88,    ,88  \"8a,   ,aa  \"8b,   ,aa     88  88       88    `8b,d8'    88,    ,88  \"8a,   ,d88  \"8b,   ,aa  88          aa    ]8I  ";
	UIKit::gotoXY(x, y + 7);     cout << " \"Y88888P\"   88`YbbdP\"'   `\"8bbdP\"Y8   `\"Ybbd8\"'   `\"Ybbd8\"'     88  88       88      \"8\"      `\"8bbdP\"Y8   `\"8bbdP\"Y8   `\"Ybbd8\"'  88          `\"YbbdP\"'  ";
	UIKit::gotoXY(x, y + 8);     cout << "             88                                                                                                                                            ";
	UIKit::gotoXY(x, y + 9);     cout << "             88                                                                                                                                            ";

	int symbolII_X = x + 157, symbolII_Y = y;
	UIKit::color(Config::T_L_RED);
	UIKit::gotoXY(symbolII_X, symbolII_Y + 2);     cout << "`7MMF'`7MMF'";
	UIKit::gotoXY(symbolII_X, symbolII_Y + 3);     cout << "  MM    MM  ";
	UIKit::gotoXY(symbolII_X, symbolII_Y + 4);     cout << "  MM    MM  ";
	UIKit::gotoXY(symbolII_X, symbolII_Y + 5);     cout << "  MM    MM  ";
	UIKit::gotoXY(symbolII_X, symbolII_Y + 6);     cout << "  MM    MM  ";
	UIKit::gotoXY(symbolII_X, symbolII_Y + 7);     cout << "  MM    MM  ";
	UIKit::gotoXY(symbolII_X, symbolII_Y + 8);     cout << ".JMML..JMML.";
	UIKit::color(Config::B_BLACK + Config::T_BLACK);

}
void Menu::initGame()
{
	bool isOver = false;
	do
	{
		system("cls");
		isOver = Menu::initMenu();
		PlaySound(NULL, NULL, SND_PURGE);
		if (!isOver) {
			Partie* parti = new Partie();
			parti->demarrerPartie();
			delete(parti);
			GOMenu::GOMenu();
			Menu::menuLvl = 1;
			Menu::choix = 1;
		}
	} while (!isOver);
}