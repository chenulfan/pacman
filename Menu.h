#pragma once
#include "Game.h";


static const int GAME_WITHOUT_COLOR = 1;
static const int GAME_WITH_COLOR = 2;
static const int FILE_WITHOUT_COLOR = 3;
static const int FILE_WITH_COLOR = 4;
static const int LOAD = 5;
static const int INSTRUCTIONS = 8;
static const int EXIT = 9;
static const int WHITE = 15;

class Menu
{
private:
	vector<string> _filenames;

public:
	void getScreensFileName();
	void printInstructions()const;
	void printMenu()const;
	int getOption();
	Level getLevelOption();
	void startMenu(bool isSaveToFile = false, bool isLoadMode = false, bool isSilentMode = false);
	void gameOver(int result);
	void clear()const;
	bool fileExists(string filename);
	void printLevelMenu() const;
	void pressAnyKeyToContinue(string msg);
};

