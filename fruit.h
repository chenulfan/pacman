#pragma once
#include "square.h"
#include "board.h"
struct pos {
	int x;
	int y;
};


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
	Fruit(const Board& b, const Square& legend);
	//Square getSqr() const { return _position; };
	//int getX() const { return getSqr().getX(); };
	//int getY() const { return getSqr().getY(); };
	int getVal() const { return _val; };
	void setPos(const Board& b, const Square& legend);
	void setVal();
	void setFruit(const Board& b, const Square& legend);
	void Move(char c) override;
	void oneMoveBack(char c) override;
	void changeDirection() override;
	void resetFruit();
	bool isLegend(const Square& legend, int y, int x);
	int randomX(const Board& b, int y, const Square& legend);
	pos randomPos(const Board& b, const Square& legend);
};