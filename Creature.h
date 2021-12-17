#pragma once
#include "square.h"


class Creature {
private:
	Square _position;

public:
	 int getX()const { return _position.getX(); }
	 int getY()const { return _position.getY(); }
	 Square getPosition() const { return _position; };
	 void print(const bool isWithColor, int distanceFromStart) { _position.print(isWithColor, distanceFromStart); }
	 void setPosition(Square& s)  {  _position = s; };
	 void setPosition(int x, int y, SqrType  type) { _position.setX(x);_position.setY(y);_position.setSqrType(type); };
	 void setX(const int x) { _position.setX(x); };
	 void setY(const int y) { _position.setY(y); }
	 virtual void Move(char playerkey) = 0;
	 virtual void changeDirection() = 0;
	 virtual void oneMoveBack(char playerkey) = 0;
};