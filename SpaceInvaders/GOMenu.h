#pragma once
class GOMenu
{
private:
	static char tabInput[5];
	static int tabScoreDigit[15];
	static int textFieldX;
	static int textFieldY;
	static int cursorText;
	static int nbChar;
public:
	static void initGOMenu(int partieScore);
	GOMenu();
	const int NB_CHAR_MAX = 3;
	static void gameOver();
	static void zoneTextInput();
	static int scoreFieldX;
	static bool buttonMainMenu();
	static bool enterPress;

	static void putScore(int score, int x, int y);
	static void removeScore();
	static void putChar(int key);
	static void removeChar();
	~GOMenu();
};

