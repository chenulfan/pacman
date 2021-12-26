#pragma once

#include "board.h"

struct pos {
	int x;
	int y;
};

class Fruit : public Creature
{
	private:
		int _val;

	public:
		Fruit() = default;
		Fruit(const Board& b, const Square& legend);
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

	private:
		int randomNum(int from, int to);
};