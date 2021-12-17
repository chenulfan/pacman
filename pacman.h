#pragma once

#include "Creature.h"

static const int UP = 119; 
static const int DOWN = 120; 
static const int LEFT = 97; 
static const int RIGHT = 100;
static const int ESC = 27;  
static const int STAY = 115;

class Pacman : public Creature {
	private:
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