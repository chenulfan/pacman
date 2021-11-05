#pragma once
#include "square.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>
class Ghost {

	Square _position,_blank;
	int color;

public:
	Ghost(int x = 38, int y = 10);
	void print() { _position.print(); };
	bool isHitWall();
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(int x) { _position.setX(x); }
	void setY(int y) { _position.setY(y); }
	Square getPosition() { return _position; };
	int randomMove();
	void trailDelete() { _blank.print(); };

};