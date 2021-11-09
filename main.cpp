#include "board.h"
#include "square.h"
#include "Game.h"

void printMenu();
int getOption();


int main() {

	int option;
	Game game;
	
	game.printMenu();
	option = getOption();
	game.clear();

	switch (option) {
		case 1:
			game.startGame();
			break;
		case 8:
			game.printInstructions();
			break;
	}
	game.clear();
}

int getOption() {
	int option;
	cin >> option;
	while (option != 1 && option != 8 && option != 9) {
		cin >> option;
	}
	return option;
}



