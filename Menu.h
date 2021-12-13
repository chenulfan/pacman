#pragma once
#include "Game.h";

static const int WHITE = 15;
static const int GAME_WITHOUT_COLOR = 1;
static const int GAME_WITH_COLOR = 2;
static const int FILE_WITHOUT_COLOR = 3;
static const int FILE_WITH_COLOR = 4;
static const int INSTRUCTIONS = 8;
static const int EXIT = 9;

class Menu
{
private:
	vector<string> _filenames;
public:
	void getFileNameFromFile();
	void printInstructions()const;
	void printMenu()const;
	int getOption();
	Level getLevelOption();
	void startMenu();
	void gameOver(const bool isWon);
	void clear();
	bool fileExists(string filename);
	void printLevelMenu() const;
};

