#pragma once

#include <string>
#include "square.h"
#include "Creature.h"


class Pacman : public Creature {
private:
	//Square _position;
	Square _startPosition;

public:
	Pacman& operator=(Square& s) {
		setPosition(s);
		_startPosition = s;
		return *this;
	}
	//Pacman() {};
	//void print(const bool isWithColor, int distanceFromStart) { _position.print(isWithColor , distanceFromStart); }
	//const int getX() const { return _position.getX(); }
	//const int getY() const { return _position.getY(); }
	//Square getPosition() const { return _position; };
	Square getStartPosition() const { return _startPosition; };
	//void setX(const int x) { _position.setX(x); };
	//void setY(const int y) { _position.setY(y); }
	void moveToStartPosition() { setX(_startPosition.getX());setY(_startPosition.getY()); };

	
};