#pragma once
#include "board.h"
#include "Ghost.h"
#include "pacman.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

static const int UP = 119; // Up Arrow 
static const int DOWN = 120; // Down Arrow 
static const int LEFT = 97; // Left Arrow 
static const int RIGHT = 100; // Right Arrow 
static const int ESC = 27;  // Escape Key
static const int SPEED = 150;
static const int STAY = 115;


void clearConsoleRow();

class Game {
private:
	Board _board;
    char _playerKey;
	Pacman _pacman;
	int _health=3;
	int _points=0;
	bool _isWithColor= false;
	int _maxPoints = 0;
	int _numOfGhosts = 0;
	Ghost _ghosts[4];
	Square _legend;
	//TODO: GHOST DESTRACTOR!
public:
	int getKey()const;
	void startGame(const bool withColor);
	const bool isGhostHitWall(Square position) const;
	const bool isPacmanHitGhost(Square position, Ghost &ghost) const ;
	const bool isNextMoveIsAWall(const int x, const int y, Board b) const;
	void clear();
	void printMenu()const;
	void printBanner()const;
	void printInstructions()const;
	const int getPoints() const { return _points; };
	const int getHealth() const { return _health; };
	const int getMaxPoints() const { return _maxPoints; };
	Board getBoard() const { return _board; };
	Pacman getPacman() const { return _pacman; }
	const int getHeight() const { return _board.getHeight(); }
	const int getWidth() const { return _board.getWidth(); }
	void setMaxPoints(const int num) { _maxPoints = num; };
	void setPoints();
	void setHealth();
	void setWithColor(const bool isWithColor) { _isWithColor = isWithColor; };
	void resetGameAfterGhostHit();
	void deletePacmanLastMove();
	const bool isPacmanAteFood() const;
	const bool isTunnel(Pacman& pacman) const;
	void movePacmanThruTunnel(Pacman& pacman);
	void MoveAndPrintGhost(Ghost& ghost);
	void deleteGhostLastMove(Ghost& ghost);
	const bool isGhostHitPacman(Square position);
	void gameOver(const bool isWon);
	void createGhosts();
};

