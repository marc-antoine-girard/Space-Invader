#include "Config.h"
#include "UIKit.h"
#include <windows.h>
#include <VersionHelpers.h>
HANDLE consoleSpaceInvader = GetStdHandle(STD_OUTPUT_HANDLE);
int Config::difficulter = 0;
int Config::couleurTextBase = Config::T_GREY;
Coord Config::fenetreXY = Coord();
char Config::customKey[] = { 'a', 'd', 'e', 'l' };
const char Config::CUSTOM_KEY[] = { 'a', 'd', 'e', 'l' };
int Config::separationEcran = 40;

int Config::currentColor(int bx, int by) {
	cout.flush();
	COORD coord;
	coord.X = bx;
	coord.Y = by;
	SetConsoleCursorPosition(consoleSpaceInvader, coord);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(consoleSpaceInvader, &info);
	return info.wAttributes;
}

Coord Config::initGameConsole() {
	Coord fenetre;
	UIKit::setDimensionFenetre(0, 0, 213, 55);
	if (IsWindows8OrGreater) {
		int fontSize = 16;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 100;
		SetConsoleCursorInfo(consoleSpaceInvader, &cursorInfo);
		CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
		cfi.dwFontSize.Y = fontSize;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(consoleSpaceInvader, &info);
		COORD new_size =
		{
			info.srWindow.Right - info.srWindow.Left + 1,
			info.srWindow.Bottom - info.srWindow.Top + 1
		};
		SetConsoleScreenBufferSize(consoleSpaceInvader, new_size);
		SetCurrentConsoleFontEx(consoleSpaceInvader, FALSE, &cfi);
		COORD coord = GetLargestConsoleWindowSize(consoleSpaceInvader);
		const int X = coord.X - 1, Y = coord.Y - 1; //213, 50
		fenetre.setPositionX(X);
		fenetre.setPositionY(Y);

	}
	else {
		const int X = 212, Y = 54;
		UIKit::setDimensionFenetre(0, 0, 213, 55);
		fenetre.setPositionX(212);
		fenetre.setPositionY(54);

	}
	UIKit::curseurVisible(false);

	return fenetre;
}

char const Config::ASCII_TABLE[26][4][9] =
{
	{
		{"   db   "},
		{"  dPYb  "},
		{" dP__Yb "},
		{"dP\"\"\"\"Yb"}
},
	{
		{"88\"\"Yb"},
		{"88__dP"},
		{"88\"\"Yb"},
		{"88oodP"}
	},
	{
		{" dP\"\"b8"},
		{"dP   `\""},
		{"Yb     "},
		{" YboodP"}
	},
	{
		{"8888b. "},
		{" 8I  Yb"},
		{" 8I  dY"},
		{"8888Y\" "}
	},
	{
		{"888888"},
		{"88__  "},
		{"88\"\"  "},
		{"888888"}
	},
	{
		{"888888"},
		{"88__  "},
		{"88\"\"  "},
		{"88    "}
	},
	{
		{" dP\"\"b8"},
		{"dP   `\""},
		{"Yb  \"88"},
		{" YboodP"}
	},
	{
		{" 88  88"},
		{" 88  88"},
		{" 888888"},
		{" 88  88"}
	},
	{
		{"  88"},
		{"  88"},
		{"  88"},
		{"  88"}
	},
	{
		{" 88888"},
		{"    88"},
		{"o.  88"},
		{"\"bodP'"}
	},
	{
		{"88  dP"},
		{"88odP "},
		{"88\"Yb"},
		{"88  Yb"}
	},
	{
		{"88    "},
		{"88    "},
		{"88  .o"},
		{"88ood8"}
	},
	{
		{"8b    d8"},
		{"88b  d88"},
		{"88YbdP88"},
		{"88 YY 88"}
	},
	{
		{"88b 88"},
		{"88Yb88"},
		{"88 Y88"},
		{"88  Y8"}
	},
	{
		{" dP\"Yb "},
		{"dP   Yb"},
		{"Yb   dP"},
		{" YbodP "}
	},
	{
		{"88\"\"Yb"},
		{"88__dP"},
		{"88\"\"\" "},
		{"88    "}
	},
	{
		{" dP\"Yb "},
		{"dP   Yb"},
		{"Yb b dP"},
		{" `\"YoYo"}
	},
	{
		{"88\"\"Yb"},
		{"88__dP"},
		{"88\"Yb "},
		{"88  Yb"},
	},
	{
		{".dP\"Y8" },
		{"`Ybo.\"" },
		{"o.`Y8b"},
		{"8bodP'"}
	},
	{
		{"888888"},
		{"  88  "},
		{"  88  "},
		{"  88  "}
	},
	{
		{"88   88"},
		{"88   88" },
		{"Y8   8P" },
		{"`YbodP'"}
	},
	{
		{"Yb    dP" },
		{" Yb  dP "},
		{"  YbdP  "},
		{"   YP   "}
	},
	{
		{"Yb    dP"},
		{" b db d " },
		{"  d''b  " },
		{"  P  Y  "}
	},
	{
		{"Yb  dP" },
		{" YbdP " },
		{" dPYb "},
		{"dP  Yb"}
	},
	{
		{"Yb  dP"},
		{" YbdP "},
		{"  8P  "},
		{" dP   "}
	},
	{
		{"8888P"},
		{"  dP "},
		{" dP  "},
		{"d8888"}
	}
};
char const Config::DIGITAL_TABLE[10][3][4] =
{
	{
		{" _"},
		{"| |"},
		{"|_|"}
	},
	{
		{""},
		{"  |"},
		{"  |"}
	},
	{
		{" _"},
		{" _|"},
		{"|_"}
	},
	{
		{" _ "},
		{" _|"},
		{" _|"}
	},
	{
		{" "},
		{"|_|" },
		{"  |"}
	},
	{
		{" _"},
		{"|_" },
		{" _|"}
	},
	{
		{" _"},
		{"|_" },
		{"|_|"}
	},
	{
		{" _"},
		{"  |"},
		{"  |"}
	},
	{
		{" _"},
		{"|_|"},
		{"|_|"}
	},
	{
		{" _"},
		{"|_|"},
		{" _|"}
	}
};

//int fontSize = 16;
//
//HANDLE consoleSpaceInvader = GetStdHandle(STD_OUTPUT_HANDLE);
//CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
//cfi.dwFontSize.Y = fontSize;
//wcscpy_s(cfi.FaceName, L"Consolas");
//SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
//CONSOLE_SCREEN_BUFFER_INFO info;
//GetConsoleScreenBufferInfo(consoleSpaceInvader, &info);
//COORD new_size =
//{
//	info.srWindow.Right - info.srWindow.Left + 1,
//	info.srWindow.Bottom - info.srWindow.Top + 1
//};
//SetConsoleScreenBufferSize(consoleSpaceInvader, new_size);
//SetCurrentConsoleFontEx(consoleSpaceInvader, FALSE, &cfi);
//COORD coord = GetLargestConsoleWindowSize(consoleSpaceInvader);
//const int X = coord.X - 1, Y = coord.Y - 1; //213, 50
//
//UIKit::curseurVisible(false);
//
//Coord fenetre;
//fenetre.setPositionX(X);
//fenetre.setPositionY(Y);