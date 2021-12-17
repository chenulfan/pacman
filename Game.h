#pragma once

#include "fruit.h"
#include "Ghost.h"

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
		int _allPoints=0;
		int _maxPoints = 0;
		bool _isWithColor= false;
		int _numOfGhosts = 0;
		Ghost _ghosts[4];
		Square _legend;
		Fruit _fruit;
	
	public:
		int getKey()const;
		const int getPoints() const { return _allPoints; };
		const int getHealth() const { return _health; };
		const int getMaxPoints() const { return _maxPoints; };
		Board getBoard() const { return _board; };
		Pacman getPacman() const { return _pacman; }
		Square getLegend() const { return _legend; }
		const int getHeight() const { return _board.getHeight(); }
		const int getWidth() const { return _board.getWidth(); }

		void setMaxPoints(const int num) { _maxPoints = num; };
		void setPoints();
		void setHealth();
		void setPlayerKey(char newKey) { _playerKey = newKey; };
		
		const bool isCreatureHitWall(Creature& creature) const;
		const bool isPacmanHitGhost(const Square& position);
		const bool isCreatureInTunnel(Creature& creature);
		const bool isPacmanAteFood() const;
		const bool isTunnel(char& prevKey);
		const bool isPacmanAteFruit(const Fruit& fruit) const;
		const bool isGhostAteFruit(const Fruit& fruit, const Ghost& ghost) const;
		const bool isGhostHitPacman(Square position);

		void deletePacmanLastMove();
		void deleteCreatureLastMove(Creature& creature);
		void deleteGhostLastMove(Ghost& ghost);

		int startGame(const bool withColor,string filename,Level type);
		void printBanner()const;
		void setWithColor(const bool isWithColor) { _isWithColor = isWithColor; };
		void resetGameAfterGhostHit();
		void resetGame();
		bool printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves);
		void movePacmanThruTunnel();
		void MoveAndPrintCreature(Creature& creature);
		void printGhosts(int isWithColor);
		void isParallelTunnelIsFood(int yPos, int xPos);

};

