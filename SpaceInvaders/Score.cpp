#include "Score.h"
#include "UIKit.h"
#include <sstream>
#include <string>

std::ofstream Score::scoreEcriture;
std::ifstream Score::scoreLecture;
std::ofstream Score::scoreNomEcriture;
std::ifstream Score::scoreNomLecture;
std::string Score::nomJoueurEnCours;
int Score::scorePartieEnCours;

//short Score::nombresDeJoueurs = 0;

void Score::initScore(std::string nom, int score) {

	Score::scorePartieEnCours = score;
	Score::nomJoueurEnCours = "";
	Score::setNomJoueur(nom);
	Score::saisirLeNoveauScore();
}
Score::~Score() {}


void Score::setNomJoueur(std::string nomJoueur) {
	Score::nomJoueurEnCours = nomJoueur;
}

void Score::saisirLeNoveauScore() {

	ostringstream tmpScoree;
	tmpScoree << scorePartieEnCours;
	string tmpScore = tmpScoree.str();
	//cout << tmpScore << "*********" << endl;
	bool changer = false;
	Score::scoreLecture.open("Score.txt");
	Score::scoreNomLecture.open("ScoreNom.txt");
	string tmpFichier[10];
	string tmpFichierNom[10];
	for (int i = 0; i < 10; i++) {
		getline(Score::scoreLecture, tmpFichier[i]);
		getline(Score::scoreNomLecture, tmpFichierNom[i]);
	}
	Score::scoreEcriture.open("Score.txt");
	Score::scoreNomEcriture.open("ScoreNom.txt");
	int i = 0;
	do {
		if (tmpScore > tmpFichier[i] && changer == false && i != 0) {
			Score::scoreNomEcriture << Score::nomJoueurEnCours;
			Score::scoreNomEcriture << endl;
			Score::scoreEcriture << tmpScore;
			Score::scoreEcriture << endl;
			changer = true;
			i--;
		}
		else {
			Score::scoreNomEcriture << tmpFichierNom[i];
			Score::scoreNomEcriture << endl;
			Score::scoreEcriture << tmpFichier[i];
			Score::scoreEcriture << endl;
		}
		i++;
	} while (i < 10);
	Score::scoreLecture.close();
	Score::scoreEcriture.close();
	Score::scoreNomLecture.close();
	Score::scoreNomEcriture.close();
}
void Score::afficherLesScores(int posX, int posY, bool afficherCouleur) {
	Score::scoreNomLecture.open("ScoreNom.txt");
	Score::scoreLecture.open("Score.txt");
	//UIKit::cadre(posX - 4, posY - 4, posX + 42, posY + 12, 15);
	UIKit::cadre(posX - 2, posY - 2, posX + 31, posY + 10, 15 * afficherCouleur);
	std::string ligneScore;
	string ligneNom;
	UIKit::color(afficherCouleur ? 0x0f: 0x00);
	for (int i = 0; i < 9; i++) {
		std::getline(scoreLecture, ligneScore);
		std::getline(scoreNomLecture, ligneNom);
		UIKit::gotoXY(posX, posY + i);
		std::cout << ligneScore;
		cout << "\t\t";
		std::cout << ligneNom;
	}
	Score::scoreNomLecture.close();
	Score::scoreLecture.close();
}
