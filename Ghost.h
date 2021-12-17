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
	//Square _position;
	int _direction = 0;
	int _startX = 0;
	int _startY = 0;

public:
	Ghost() {};
	Ghost(int direction, int x, int y);
	Ghost& operator=(Ghost& s);


	//void print(const bool isWithColor, int distanceFromStart) { _position.print(isWithColor , distanceFromStart); };
	//int getX()const { return _position.getX(); }
	//int getY()const { return _position.getY(); }
	int getStartX() { return _startX; }
	int getStartY() { return _startY; }
	//void setX(const int x) { _position.setX(x); }
	//void setY(const int y) { _position.setY(y); }
	//Square getPosition()const { return _position; };
	void changeDirection();
	void setDirection(int direction) { _direction = direction; };
	void Move();
	void changePosition(const int y, const int x);
	void oneMoveBack();
	const bool isTunnel(Square& position, const int height, const int width) const;
	void SmartMove(const Pacman& pacman, Square** b, const int height, const int width);
	int** initArr(const int height,const int width);
	void notSmartMove(const Pacman& pacman, Square** b, const int height, const int width);
};