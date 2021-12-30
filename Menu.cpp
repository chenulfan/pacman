#include "Menu.h"

void Menu::pressAnyKeyToContinue(string msg) {
	cout << "press any key to " << msg << endl;
	cin.ignore();
	cin.ignore();
}

void Menu::printMenu()const {
	cout << endl << " (1) Start a new game without colors" << endl << " (2) Start a new game with colors" << endl
		<< " (3) Start a new game without colors from specific file" << endl
		<< " (4) Start a new game with colors from specific file" << endl
		<< " (5) play record game" << endl
		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
}
void Menu::printLevelMenu() const {
	cout << endl << "Please Choose Difficulty Level (1-3)" << endl << " (1) HARD (BEST)" << endl
		<< " (2) MID (GOOD)" << endl
		<< " (3) EASY (NOVICE)" << endl;
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
	bool isSilentMode = true;
	bool isFinished;
	string msg;
	getScreensFileName();
	int option, result, counter = 0;
	do {
		changeColor(WHITE);
		Game game;
		string filename;
		Level level = Level::NOVICE;
		clear();
		printMenu();
		option = getOption();
		clear();
		switch (option)
		{

		case GAME_WITHOUT_COLOR:
			printLevelMenu();
			level = getLevelOption();
			clear();
			for (auto i = _filenames.begin(); i != _filenames.end(); ++i) {
				++counter;
				result = game.startGame(false, *i, level, true);
				if (result != 0)
				{
					gameOver(result);
					break;
				}
				else {
					clear();
					cout << "you finished map number " << counter << " out of " << _filenames.size() << endl;
					clear();
				}
				clear();
				game.resetGame();
			}

			if (counter == _filenames.size())
				gameOver(0);

			counter = 0;
			break;

		case GAME_WITH_COLOR:
			printLevelMenu();
			level = getLevelOption();
			clear();
			for (auto y = _filenames.begin(); y != _filenames.end(); ++y) {
				++counter;
				result = game.startGame(true, *y, level, true);
				if (result != 0)
				{
					gameOver(result);
					break;
				}
				else {
					clear();
					cout << "you finished map number " << counter << " out of " << _filenames.size() << endl;
					msg = "countinue to the next game...";
					pressAnyKeyToContinue(msg);
					clear();
				}
				clear();
				game.resetGame();
			}

			if (counter == _filenames.size())
				gameOver(0);

			counter = 0;
			break;

		case FILE_WITHOUT_COLOR:
			cout << "please enter filename" << endl;
			cin >> filename;
			if (fileExists(filename)) {
				clear();
				printLevelMenu();
				level = getLevelOption();
				clear();
				gameOver(game.startGame(false, filename, level, true));
			}
			else {
				cout << "file doesn't exist" << endl;
				msg = "return to the menu...";
				pressAnyKeyToContinue(msg);
				clear();
			}
			clear();
			break;

		case FILE_WITH_COLOR:
			cout << "please enter filename" << endl;
			cin >> filename;
			if (fileExists(filename)) {
				clear();
				printLevelMenu();
				level = getLevelOption();
				clear();
				gameOver(game.startGame(true, filename, level, true));
			}
			else {
				cout << "file doesn't exist" << endl;
				msg = "return to the menu...";
				pressAnyKeyToContinue(msg);
				clear();
			}
			clear();
			break;

		case LOAD:
			counter = 0;
			isFinished = false;
			for (auto x = _filenames.begin(); x != _filenames.end(); ++x) {
				result = game.loadGame(true, isSilentMode, isFinished, *x);
				if (result != 0 && isFinished){
					gameOver(result);
					break;
				}
				else {
					game.resetGame();
					clear();
				}
				counter++;
			}

			if (counter == _filenames.size()) {
				if (isSilentMode)
					gameOver(-2);
				else
					gameOver(0);
			}

			break;

		case INSTRUCTIONS:
			printInstructions();
			msg = "return to the menu...";
			pressAnyKeyToContinue(msg);

			clear();
			break;
		}
	} while (option != EXIT);
}


int Menu::getOption() {
	int option;
	cin >> option;
	while (option != GAME_WITHOUT_COLOR && option != GAME_WITH_COLOR && option != FILE_WITH_COLOR && option != FILE_WITHOUT_COLOR && option != LOAD && option != INSTRUCTIONS && option != EXIT) {
		cout << "plesae enter valid number" << endl;
		cin >> option;
	}
	return option;
}


void Menu::getScreensFileName() {
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



void Menu::gameOver(int result) {
	string msg;
	clear(); // clears the console;
	switch (result) {
	case -1:
		cout << "Test Failed" << endl;
		break;
	case -2:
		cout << "Test Passed" << endl;
		break;
	case 0:
		cout << "You WON!!" << endl;
		break;
	case 1:
		cout << "GAME OVER" << endl;
		break;
	case 2:
		cout << "BOARD INVALID TOO MANY PACMANS" << endl;
		break;
	case 3:
		cout << "BOARD INVALID TOO MANY LEGENDS" << endl;
		break;
	case 4:
		cout << "BOARD INVALID TOO MANY GHOSTS" << endl;
		break;
	case 5:
		cout << "BOARD INVALID HEIGHT IS TOO BIG" << endl;
		break;
	case 6:
		cout << "BOARD INVALID WIDTH IS TOO BIG" << endl;
		break;
	case 7:
		cout << "BOARD INVALID NO PACMAN FOUND" << endl;
		break;
	}
	msg = "return to the menu...";
	pressAnyKeyToContinue(msg);
}

void Menu::clear()const {
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
Level Menu::getLevelOption() {
	int option;
	cin >> option;
	--option;
	while (option != int(Level::BEST) && option != int(Level::GOOD) && option != int(Level::NOVICE)) {
		cout << "plesae enter valid number" << endl;
		cin >> option;
		--option;
	}
	return Level(option);
}