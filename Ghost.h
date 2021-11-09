#pragma once
#include "square.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3
class Ghost {

	Square _position,_blank;
	int color;
	int dir; //direction
	void oneMoveBack();
public:
	Ghost(int dir,int x = 38, int y = 10);
	void print() { _position.print(); };
	bool isHitWall();
	int getX() { return _position.getX(); }
	int getY() { return _position.getY(); }
	void setX(int x) { _position.setX(x); }
	void setY(int y) { _position.setY(y); }

	Square getPosition() { return _position; };
	void changeDir();
	void trailDelete() { _blank.print(); };
	void startMoving();
	void Move();
	void changePosition(int y, int x);
};