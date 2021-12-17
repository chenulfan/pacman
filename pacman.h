#pragma once

#include <string>
#include "square.h"
#include "Creature.h"

static const int UP = 119; // Up Arrow 
static const int DOWN = 120; // Down Arrow 
static const int LEFT = 97; // Left Arrow 
static const int RIGHT = 100; // Right Arrow 
static const int ESC = 27;  // Escape Key
static const int STAY = 115;

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
	Square getStartPosition() const { return _startPosition; };
	void moveToStartPosition() { setX(_startPosition.getX());setY(_startPosition.getY()); };
	virtual void Move(char playerkey) override;
	virtual void changeDirection() {};
	virtual void oneMoveBack(char playerkey) override;

	
};