#pragma once
#include "square.h"
#include "board.h"
struct pos {
	int x;
	int y;
};

pos randomPos(const Board& b);
int randomNum(int from, int to);
int randomY(const Board& b, int x);
class Fruit : public Creature
{
private:
	//Square _position;
	int _val;
	int _direction = 0;
public:
	Fruit() = default;
	Fruit(const Board& b);
	//Square getSqr() const { return _position; };
	//int getX() const { return getSqr().getX(); };
	//int getY() const { return getSqr().getY(); };
	int getVal() const { return _val; };
	void setPos(const Board& b);
	void setVal();
	void setFruit(const Board& b);
	void Move();
	void oneMoveBack();
	void changeDirection();
	void resetFruit();
};




