#pragma once
#include "board.h"
#include "Ghost.h"
#include "pacman.h"
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define UP1 119 // Up Arrow 
#define UP2 87 // Up Arrow 
#define DOWN1 120 // Down Arrow 
#define DOWN2 88 // Down Arrow 
#define LEFT1 97  // Left Arrow 
#define LEFT2 65  // Left Arrow 
#define RIGHT1 100 // Right Arrow 
#define RIGHT2 68  // Right Arrow 
#define ESC 27  // Escape Key
#define SPEED 300

int calcMoveX(int x, int y, int direction);
int calcMoveY(int x, int y, int direction);
void clearConsoleRow();
bool isNextMoveIsAWall(int x, int y, Board b);

class Game {
private:
	Board _board;
    char _playerKey;
	Pacman _pacman;
	int _health=3;
	int _points=0;

public:
	int getKey();
	void startGame();
	bool hitWall( Square position);
	void printGhosts(Ghost &ghost1, Ghost &ghost2);
	bool hitGhost(Square position, Ghost &ghost1, Ghost &ghost2);
	void pacmanStay(Square &_blank);

	void gameOver();
	void clear();
	void printMenu();
	void printBanner();
	void printInstructions();
	int getPoints() { return _points; };
	int getHealth() { return _health; };
	void setPoints() { _points = getPoints() + 1; };
	void setHealth() { _health = getHealth() - 1; };
	eSqrType whatPacmanMet(Pacman pacman);
	Board getBoard() { return _board; };
	void resetGameAfterGhostHit(Ghost &ghost1, Ghost &ghost2);

};

