#include "board.h"
#include "square.h"
#include "Game.h"

#define WHITE 15

void printMenu();
int getOption();


int main() {
	int option;

	char ch;

		do {
			changeColor(WHITE);
			Game game;
			game.printMenu();
			option = getOption();
			game.clear();

		switch (option) {
			case 1:
				game.startGame(false);
				game.clear();
				break;
			case 2:
				game.startGame(true);
				game.clear();
				break;
			case 8:
				game.printInstructions();
				cout << "press any key to return to the menu..." << endl;
				cin >> ch;
				game.clear();
				break;
			}
		}while (option != 9);
}


int getOption() {
	int option;
	cin >> option;
	while (option != 1 && option != 2 && option != 8 && option != 9) {
		cout << "plesae enter valid number" << endl;
		cin >> option;
	}
	return option;
}



