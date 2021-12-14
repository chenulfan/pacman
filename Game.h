#pragma once
#include "fruit.h"
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
enum class Level { BEST, GOOD, NOVICE };
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
	Fruit _fruit;
	//TODO: GHOST DESTRACTOR!
public:
	int getKey()const;
	int startGame(const bool withColor,string filename,Level type);
	const bool isCreatureHitWall(Square position) const;
	const bool isPacmanHitGhost(const Square& position);
	const bool isNextMoveIsAWall(const int x, const int y, const Board& b) const;
	//void clear();
	//void printMenu()const;
	void printBanner()const;
	//void printInstructions()const;
	const int getPoints() const { return _points; };
	const int getHealth() const { return _health; };
	const int getMaxPoints() const { return _maxPoints; };
	Board getBoard() const { return _board; };
	Pacman getPacman() const { return _pacman; }
	const int getHeight() const { return _board.getHeight(); }
	const int getWidth() const { return _board.getWidth(); }
	void setMaxPoints(const int num) { _maxPoints = num; };
	void setPoints(int num = 1);
	void setHealth();
	void setPlayerKey(char newKey) { _playerKey = newKey; };
	const bool isCreatureInTunnel(Square pos);
	void setWithColor(const bool isWithColor) { _isWithColor = isWithColor; };
	void resetGameAfterGhostHit();
	void deletePacmanLastMove();
	void deleteFruitLastMove(Fruit& fruit);
	const bool isPacmanAteFood() const;
	const bool isTunnel(char& prevKey);
	void movePacmanThruTunnel();
	void MoveAndPrintGhost(Ghost& ghost);
	void MoveAndPrintFruit();
	void deleteGhostLastMove(Ghost& ghost);
	const bool isGhostHitPacman(Square position);
	//void gameOver(const bool isWon);
	void printGhosts(int isWithColor);
	void whichDirectionMovePacman();
	const bool isPacmanAteFruit(const Fruit& fruit) const;
	const bool isGhostAteFruit(const Fruit& fruit, const Ghost& ghost) const;
	void resetGame();
	bool printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves);
	//void createGhosts();
	//bool** initArr();
	//int smartMove(const Ghost& ghost);
	//const bool isTunnel(Square& position) const;



	//int smartMove(const Ghost& ghost);
	//bool isValidMove(int row, int col, string moves);
	//bool foundPacman(int row, int col, string moves);
};

