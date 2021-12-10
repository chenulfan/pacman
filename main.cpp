#include "board.h"
#include "square.h"
#include "Game.h"

static const int WHITE = 15;
static const int GAME_WITHOUT_COLOR = 1;
static const int GAME_WITH_COLOR = 2;
static const int INSTRUCTIONS = 8;
static const int EXIT = 9;

void printMenu();
int getOption();


// TODO:
// 1. delete unncessery *statics* and unncessery *includes* and unncessery *using*
// 2. delete unncessery functios
// 2. create menu class
// 3. create inheritence - abstract class 'creature' --> (ghost, pacman, fruit)
// 4. fruit
// 5. option to load spesific file from menu
// 6. option to load all file from directory
// 7. best / novice / good option for ghosts
// 10. check for bugs

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
			case GAME_WITHOUT_COLOR:
				game.startGame(false);
				game.clear();
				break;
			case GAME_WITH_COLOR:
				game.startGame(true);
				game.clear();
				break;
			case INSTRUCTIONS:
				game.printInstructions();
				cout << "press any key to return to the menu..." << endl;
				cin >> ch;
				game.clear();
				break;
			}
		}while (option != EXIT);
}


int getOption() {
	int option;
	cin >> option;
	while (option != GAME_WITHOUT_COLOR && option != GAME_WITH_COLOR && option != INSTRUCTIONS && option != EXIT) {
		cout << "plesae enter valid number" << endl;
		cin >> option;
	}
	return option;
}



