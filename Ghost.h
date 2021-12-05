#pragma once
#include "square.h"
#include "pacman.h"
#include "board.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>
#include <queue>

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
static const int HEIGHT = 19;
static const int WIDTH = 70;

static const int GHOST_START_X = 38;
static const int GHOST_START_Y = 10;
enum class DIRECTIONS { RIGHT, DOWN, LEFT, UP};
struct queSquare {
	Square currSquare;
	DIRECTIONS move;
};

class Ghost {

	Square _position;
	int _direction;
public:
	Ghost(const int direction, const int x = GHOST_START_X, const int y = GHOST_START_Y);
	void print(const bool isWithColor) { _position.print(isWithColor); };
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(const int x) { _position.setX(x); }
	void setY(const int y) { _position.setY(y); }
	Square& getPosition() { return _position; };
	void changeDirection();
	void Move();
	void changePosition(const int y, const int x);
	void oneMoveBack();
	void SmartMove(const Pacman& pacman, const Board& b);
	const bool isTunnel(Square& position) const;
};