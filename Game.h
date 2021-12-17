#pragma once
#include "fruit.h"
#include "board.h"
#include "Ghost.h"
#include "pacman.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>


static const int SPEED = 150;





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
	const bool isCreatureHitWall(Creature& creature) const;
	const bool isPacmanHitGhost(const Square& position);
	//const bool isNextMoveIsAWall(const int x, const int y, const Board& b) const;
	//void clear();
	//void printMenu()const;
	void printBanner()const;
	//void printInstructions()const;
	const int getPoints() const { return _points; };
	const int getHealth() const { return _health; };
	const int getMaxPoints() const { return _maxPoints; };
	Board getBoard() const { return _board; };
	Pacman getPacman() const { return _pacman; }
	Square getLegend() const { return _legend; }
	const int getHeight() const { return _board.getHeight(); }
	const int getWidth() const { return _board.getWidth(); }
	void setMaxPoints(const int num) { _maxPoints = num; };
	void setPoints(int num = 1);
	void setHealth();
	void setPlayerKey(char newKey) { _playerKey = newKey; };
	const bool isCreatureInTunnel(Creature& creature);
	void setWithColor(const bool isWithColor) { _isWithColor = isWithColor; };
	void resetGameAfterGhostHit();
	void deletePacmanLastMove();
	//void deleteFruitLastMove(Fruit& fruit);
	void deleteCreatureLastMove(Creature& creature);
	const bool isPacmanAteFood() const;
	const bool isTunnel(char& prevKey);
	void movePacmanThruTunnel();
	void MoveAndPrintCreature(Creature& creature);
	void deleteGhostLastMove(Ghost& ghost);
	const bool isGhostHitPacman(Square position);
	void printGhosts(int isWithColor);
	//void whichDirectionMovePacman();
	const bool isPacmanAteFruit(const Fruit& fruit) const;
	const bool isGhostAteFruit(const Fruit& fruit, const Ghost& ghost) const;
	void resetGame();
	bool printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves);
};

