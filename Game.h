#pragma once
#include "board.h"
#include "Ghost.h"
#include "pacman.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

#define UP 119 // Up Arrow 
#define DOWN 120 // Down Arrow 
#define LEFT 97  // Left Arrow 
#define RIGHT 100 // Right Arrow 
#define ESC 27  // Escape Key
#define SPEED 300
#define STAY 115

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

	void gameOver();
	void clear();
	void printMenu();
	void printBanner();
	void printInstructions();
	int getPoints() { return _points; };
	int getHealth() { return _health; };
	void setPoints();
	void setHealth();
	Board getBoard() { return _board; };
	void resetGameAfterGhostHit(Ghost &ghost1, Ghost &ghost2);
	void deletePacmanLastMove();
	bool isPacmanAteFood();
	void changeColor(int color);
	bool isTunnel(Pacman& pacman);
	void movePacmanThruTunnel(Pacman& pacman);
};

