#pragma once

#include "square.h"
#include "pacman.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>
#include <queue>

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3

class Board;

enum class DIRECTIONS { RIGHT, DOWN, LEFT, UP,DEAD};

struct queSquare {
	Square currSquare;
	DIRECTIONS move;
};

class Ghost: public Creature{

	private:
		int _startX = 0;
		int _startY = 0;

	public:
		Ghost() {};
		Ghost(int direction, int x, int y);
		Ghost& operator=(Ghost& s);
		int getStartX() { return _startX; }
		int getStartY() { return _startY; }


		void changeDirection() override;
		void Move(char c) override;
		void changePosition(const int y, const int x);
		void oneMoveBack(char c) override;
		const bool isTunnel(Square& position, const int height, const int width) const;
		void SmartMove(const Pacman& pacman, Square** b, const int height, const int width);
		int** initArr(const int height,const int width);
		void notSmartMove(const Pacman& pacman, Square** b, const int height, const int width);

	private:
		void printArr(const int height, const int width, int** arr);
		void resetArr(const int height, const int width, int** arr);
};