#pragma once

#include "square.h"
#include "pacman.h"
//#include "board.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>
#include <queue>

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3

static const int GHOST_START_X = 38;
static const int GHOST_START_Y = 10;

enum class DIRECTIONS { RIGHT, DOWN, LEFT, UP,DEAD};

struct queSquare {
	Square currSquare;
	DIRECTIONS move;
};

class Ghost {

	Square _position;
	int _direction = 0;
	int _startX = 0;
	int _startY = 0;
	//int _height = 0;
	//int _width = 0;

public:
	Ghost() {};
	Ghost(int direction, int x, int y);
	Ghost& operator=(Ghost& s);


	void print(const bool isWithColor, int distanceFromStart) { _position.print(isWithColor , distanceFromStart); };
	int getX()const { return _position.getX(); }
	int getY()const { return _position.getY(); }
	int getStartX() { return _startX; }
	int getStartY() { return _startY; }
	void setX(const int x) { _position.setX(x); }
	void setY(const int y) { _position.setY(y); }
	Square getPosition()const { return _position; };
	void changeDirection();
	void setDirection(int direction) { _direction = direction; };
	void Move();
	void changePosition(const int y, const int x);
	void oneMoveBack();
	//const bool isTunnel(Square& position) const;
	//void SmartMove(const Pacman& pacman, const Board& b);
	//bool** initArr();
};