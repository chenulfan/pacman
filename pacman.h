#pragma once

#include <string>
#include "square.h"

static const int PACMAN_START_Y = 1;
static const int PACMAN_START_X = 17;

class Pacman {
private:
	Square _position;

public:
	Pacman() { _position.setSquare(PACMAN_START_Y, PACMAN_START_X, SqrType::PACMAN); };
	void print(const bool isWithColor) { _position.print(isWithColor); }
	const int getX() const { return _position.getX(); }
	const int getY() const { return _position.getY(); }
	Square getPosition() const { return _position; };
	void setX(const int x) { _position.setX(x); };
	void setY(const int y) { _position.setY(y); };
	void startPosition() { _position.setSquare(PACMAN_START_Y, PACMAN_START_X, SqrType::PACMAN); }

	
};