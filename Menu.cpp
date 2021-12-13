#include "Menu.h"

void Menu::printMenu()const {
	cout << endl << " (1) Start a new game without colors" << endl << " (2) Start a new game with colors" << endl
		<< " (3) Start a new game without colors from specific file" << endl
		<< " (4) Start a new game with colors from specific file" << endl
		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
}


void Menu::printInstructions()const {
	cout << endl << "The instructions are: " << endl;
	cout << "  Press W to move up" << endl;
	cout << "  Press D to move right" << endl;
	cout << "  Press A to move left" << endl;
	cout << "  Press X to move down" << endl;
	cout << "  Press S to stay in your place" << endl;
	cout << "  You have 4 tunnel each side of the board which you can teleport to other side! TRY THEM" << endl;
	cout << "  Your goal is to eat all the breadcrumbs without being eaten by the ghosts!" << endl;
	cout << "  You have 3 life to achieve that, each time you get eaten by a ghost ur life will be reduce by 1" << endl;
	cout << "  The amount of lifes left will be indicated under the game board, when you reach 0 you lose" << endl;
	cout << "  Have FUN" << endl << endl;
}
void Menu::startMenu() {
	getFileNameFromFile();
	int option;
	char ch;
	do {
		changeColor(WHITE);
		Game game;
		string filename;
		printMenu();
		option = getOption();
		clear();
		switch (option) 
		{
		case GAME_WITHOUT_COLOR:
			for (auto i = _filenames.begin(); i != _filenames.end(); ++i) {
				if (!game.startGame(false, *i))
				{
					gameOver(false);
				}
				clear();
				game.resetGame();
			}
			gameOver(true);
			break;
		case GAME_WITH_COLOR:
			for (auto i = _filenames.begin(); i != _filenames.end(); ++i) {
				if (!game.startGame(true, *i))
				{
					gameOver(false);
				}
				clear();
				game.resetGame();
			}
			gameOver(true);
			break;
		case FILE_WITHOUT_COLOR:
			cout << "please enter filename" << endl;
			cin >> filename;
			if (fileExists(filename)) {
				clear();
				gameOver(game.startGame(false,filename));
			}
			else {
				cout << "file doesn't exist" << endl;
				cout << "press any key to return to the menu..." << endl;
				cin >> ch;
				clear();
			}
			clear();
			break;
		case FILE_WITH_COLOR:
			cout << "please enter filename" << endl;
			cin >> filename;
			if (fileExists(filename)) {
				clear();
				gameOver(game.startGame(true, filename));
			}
			else {
				cout <<"file doesn't exist" << endl;
				cout << "press any key to return to the menu..." << endl;
				cin >> ch;
				clear();
			}
			clear();
			break;
		case INSTRUCTIONS:
			printInstructions();
			cout << "press any key to return to the menu..." << endl;
			cin >> ch;
			clear();
			break;
		}
	} while (option != EXIT);
}


int Menu::getOption() {
	int option;
	cin >> option;
	while (option != GAME_WITHOUT_COLOR && option != GAME_WITH_COLOR && option != FILE_WITH_COLOR && option != FILE_WITHOUT_COLOR && option != INSTRUCTIONS && option != EXIT) {
		cout << "plesae enter valid number" << endl;
		cin >> option;
	}
	return option;
}


void Menu::getFileNameFromFile() {
	string sourceFolder;
	sourceFolder = _getcwd(NULL, 0);

	for (auto& p : std::filesystem::directory_iterator(sourceFolder))
	{
		if (p.path().extension().string() == ".screen" && p.is_regular_file())
		{
			string fileName = p.path().filename().generic_string();
			_filenames.push_back(fileName);
		}
	}
	sort(_filenames.begin(), _filenames.end());
}


void Menu::gameOver(const bool isWon) {
	clear(); // clears the console;
	char ch;
	if (isWon)
		cout << "You WON!!" << endl;
	else
		cout << "GAME OVER" << endl;
	cout << "press any key to return to the menu..." << endl;
	cin >> ch;
}

void Menu::clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
bool Menu::fileExists(string filename) {
	ifstream file(filename, ios::in);
	if (file) {
		file.close();
		return true;
	}
	else {
		file.close();
		return false;
	}
}