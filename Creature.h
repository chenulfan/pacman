#pragma once
#include "square.h"

class Creature {

protected:
	Square _position;
	int _direction;

public:
	int getX()const { return _position.getX(); }
	int getY()const { return _position.getY(); }
	int getDirection()const { return _direction; }
	void setDirection(int direction) { _direction = direction; };
	Square getPosition() const { return _position; };
	void print(const bool isWithColor, int distanceFromStart, bool isSilentMode = false) { 
		_position.print(isWithColor, distanceFromStart, isSilentMode); 
	}
	void setPosition(Square& s) { _position = s; };
	void setPosition(int x, int y, SqrType  type) { _position.setX(x); _position.setY(y); _position.setSqrType(type); };
	void setX(const int x) { _position.setX(x); };
	void setY(const int y) { _position.setY(y); }
	virtual void Move(char playerkey) = 0;
	virtual void changeDirection() = 0;
	virtual void oneMoveBack(char playerkey) = 0;
};