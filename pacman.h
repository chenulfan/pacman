#pragma once

#include <string>
#include "square.h"

#define ROW_SIZE 76
#define COL_SIZE 20

class PacMan {

	Square _position;
	int color;

public:
	PacMan() { _position.setSquare(38, 10, 4), color = 0; }
	void print() { _position.print(); }
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(int x) { _position.setX(x); };
	void setY(int y) { _position.setY(y); };
	Square getPosition() { return _position; };

	
};