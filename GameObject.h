#pragma once
#include "square.h"

class GameObject {

public:
	Square _position;
	int _x;
	int _y;
	GameObject() { _x = 38;_y = 10; _position.setSquare(38, 10, 4); }
	void print() { _position.print(); }
	void setX(int x) { _x = x;_position.setX(x); }
	void setY(int y) { _y = y;_position.setY(y); }
};