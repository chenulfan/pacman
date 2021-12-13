#include "fruit.h"
#include "square.h"
#include<time.h>

Fruit::Fruit(const Board& b) {
	setPos(b);
}

void Fruit::setPos(const Board& b) {
	pos randPos = randomPos(b);
	_position.setSquare(randPos.x, randPos.y, SqrType::FRUIT);
}

void Fruit::setVal() {
	_val = randomNum(5, 9);
}

void Fruit::setFruit(const Board& b) {
	setVal();
	setPos(b);
}

pos randomPos(const Board& b) {
	int x, y;
	SqrType type;
	pos randPos;
	x = randomNum(1, b.getWidth() - 2);
	y = randomY(b, x);
	type = b.getSquare(y, x).getSqrType();
	randPos.x = x;
	randPos.y = y;
	return randPos;
}

int randomNum(int from, int to) {
	srand(time(0));
	return rand() % (to - from + 1) + from;
}

int randomY(const Board &b, int x) {
	int counterSpaces = 0;
	std::vector<int> myvector;
	for (int i = 0; i < b.getHeight(); i++) {
		if (b.getSquare(i, x).getSqrType() != SqrType::WALL) {
			myvector.push_back(i);
		}
	}
	int size = myvector.size();
	return(myvector[rand() % size]);
}
