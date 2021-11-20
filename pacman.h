#pragma once

#include <string>
#include "square.h"

static const int START_Y = 1;
static const int START_X = 17;

class Pacman {
private:
	Square _position;

public:
	Pacman() { _position.setSquare(START_Y, START_X, Square::PACMAN); };
	void print(const bool isWithColor) { _position.print(isWithColor); }
	const int getX() { return _position.getX(); }
	const int getY() { return _position.getY(); }
	void setX(const int x) { _position.setX(x); };
	void setY(const int y) { _position.setY(y); };
	Square getPosition() { return _position; };
	void startPosition() { _position.setSquare(START_Y, START_X, Square::PACMAN); }

	
};