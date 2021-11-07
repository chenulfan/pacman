#include "board.h"
#include "square.h"
#include "Game.h"
#include <cstdlib>
#include <time.h> 
int main() {
	srand(time(NULL));
	Game game;
	game.startGame();
}


//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(hConsole, 10);
//cout << "CHEn" << endl;
//SetConsoleTextAttribute(hConsole, 13);
//cout << "DAN" << endl;
//
//SetConsoleTextAttribute(hConsole, 9);
//cout << "TALLLLL" << endl;