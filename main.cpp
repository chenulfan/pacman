#include "board.h"
#include "square.h"
#include "Game.h"

void printMenu();
int getOption();


int main() {
	int option;
	Game game;

	char ch;

		game.printMenu();
		option = getOption();
		game.clear();
		switch (option) {
			case 1:
				game.startGame();
				game.clear();
				break;
			case 8:
				game.printInstructions();
				cout << "press any key to return to them menu" << endl;
				cin >> ch;
				game.clear();
				game.printMenu();
				option = getOption();
				game.clear();
				break;
			}
}


int getOption() {
	int option;
	cin >> option;
	while (option != 1 && option != 8 && option != 9) {
		cout << "plesae enter valid number" << endl;
		cin >> option;
	}
	return option;
}



