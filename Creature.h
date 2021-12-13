#pragma once
#include "square.h"


class Creature {
private:
	Square _position;

public:
	virtual int getX()const { return _position.getX(); }
	virtual int getY()const { return _position.getY(); }
	virtual Square getPosition() const { return _position; };
	virtual void print(const bool isWithColor, int distanceFromStart) { _position.print(isWithColor, distanceFromStart); }
	virtual void setPosition(Square& s)  {  _position = s; };
	virtual void setPosition(int x, int y, SqrType  type) { _position.setX(x);_position.setY(y);_position.setSqrType(type); };
	virtual void setX(const int x) { _position.setX(x); };
	virtual void setY(const int y) { _position.setY(y); }
};