#pragma once
#include "square.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
class Ghost {

	Square _position;
	int direction; 
public:
	Ghost(int direction ,int x = 38, int y = 10);
	void print(bool isWithColor) { _position.print(isWithColor); };
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(int x) { _position.setX(x); }
	void setY(int y) { _position.setY(y); }
	Square getPosition() { return _position; };
	void changeDirection();
	void Move();
	void changePosition(int y, int x);
	void oneMoveBack();
};