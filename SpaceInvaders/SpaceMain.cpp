#include <iostream>
#include "Menu.h"
#include <windows.h>
//#include <VersionHelpers.h>
#include <time.h>
#include "Config.h"
#include <mmsystem.h>
using namespace std;
int main()
{
	Config::fenetreXY = Config::initGameConsole();
	Menu::initGame();
	return 0;
}