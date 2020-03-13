#pragma once
#include <iostream>
#include <fstream>
#include <string>


class Score {
	static std::ofstream scoreEcriture;
	static std::ifstream scoreLecture;
	static std::ofstream scoreNomEcriture;
	static std::ifstream scoreNomLecture;
	static std::string nomJoueurEnCours;
	static int scorePartieEnCours;
	
public:
	//static std::string players[10];
	static void initScore(std::string nom, int score);
	~Score();
	static void setNomJoueur(std::string nomJoueur);
	static void afficherLesScores(int posX, int posY, bool afficherCouleur);
	//static short nombresDeJoueurs;
	static void saisirLeNoveauScore();
};

