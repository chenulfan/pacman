#pragma once

#include <string>
#include "square.h"


class Pacman {
private:
	Square _position;

public:
	Pacman() { _position.setSquare(1, 17, PACMAN); };
	void print() { _position.print(); }
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(int x) { _position.setX(x); };
	void setY(int y) { _position.setY(y); };
	Square getPosition() { return _position; };
	void startPosition() { _position.setSquare(1, 17, PACMAN); }

	
};