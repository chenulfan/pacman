#include "Menu.h"

int main(int argc, char* argv[]) {
	Menu menu;
	if (argc == 1) {
		menu.startMenu();
	}
	else if (strcmp(argv[1], "-load") == 0 || strcmp(argv[1], "-save") == 0)
	{
		if (argc == 2) {
			if (strcmp(argv[1], "-load") == 0) {
				menu.startMenu(false, true);
			}
			else {
				menu.startMenu(true);
			}
		}
		else {
			if (strcmp(argv[2], "-silent") == 0 && strcmp(argv[1], "-load") == 0) {
				menu.startMenu(false, true, true);
			}
			else {
				cout << "Commad Line Argument Are NOT Valid";
			}
		}
	}
	else {
		cout << "Command Line Arguemnt Are NOT Valid";
		return 0;
	}
}



// TOOD:



//DONE:
// 1. issue when hit ghost and food is deleted from screen
// 2. ghost doesn't eat fruit
// 3. fruit crush game 3
// 4. ArgV argC - CMD
// 5. silent MODE
// ?? - maybe add test failed for helath and points
