#pragma once
#include "square.h"
#include <string>

class PacMan {

	Square _position;
	string color;

public:
	PacMan() { _position.setSquare(38, 10, 4), color = "b"; }
	void print() { _position.print(); }
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(int x) { _position.setX(x); }
	void setY(int y) { _position.setY(y); }
	Square getPosition() { return _position; };
	
};