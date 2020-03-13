#pragma once
#include "Coord.h"
class Config
{
public:
	static int difficulter;
	static Coord fenetreXY;
	static int couleurTextBase;
	static const short UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13;
	const enum COULEUR_BACKGROUND {
		B_BLACK = 0X0000,			//BACKGROUND BLACK
		B_WHITE = 0X00F0,			//BACKGROUND WHITE
		B_GREY = 0X0070,			//BACKGROUND GREY
		B_D_BLUE = 0X0010,			//BACKGROUND DARK BLUE
		B_D_GREEN = 0X0020,			//BACKGROUND DARK GREEN
		B_D_TURQUOISE = 0X0030,		//BACKGROUND DARK TURQUOISE
		B_D_RED = 0X0040,			//BACKGROUND DARK RED
		B_D_PURPLE = 0X0050,		//BACKGROUND DARK PURPLE
		B_D_YELLOW = 0X0060,		//BACKGROUND DARK YELLOW
		B_L_BLUE = 0X0090,			//BACKGROUND LIGHT BLUE
		B_L_GREEN = 0X00A0,
		B_L_TURQUOISE = 0X00B0,
		B_L_RED = 0X00C0,
		B_L_PURPLE = 0X00D0,
		B_L_YELLOW = 0X00E0,
	};
	const enum COULEUR_TEXT {
		T_BLACK = 0X0000,
		T_D_BLUE = 0X0001,
		T_D_GREEN = 0X0002,
		T_D_TURQUOISE = 0X0003,
		T_D_RED = 0X0004,
		T_D_PURPLE = 0X0005,
		T_D_YELLOW = 0X0006,
		T_GREY = 0X0007,
		T_L_BLUE = 0X0009,
		T_L_GREEN = 0X000A,
		T_L_TURQUOISE = 0X000B,
		T_L_RED = 0X000C,
		T_L_PURPLE = 0X000D,
		T_L_YELLOW = 0X000E,
		T_WHITE = 0X000F,
	};
	static Coord initGameConsole();
	static char customKey[4];
	static const char CUSTOM_KEY[4];
	static int separationEcran;
	static int currentColor(int bx, int by);
	static char const DIGITAL_TABLE[10][3][4];
	static char const ASCII_TABLE[26][4][9];
};

