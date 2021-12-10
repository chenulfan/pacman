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
	do {
		x = randomNum(1, b.getWidth() - 2);
		y = randomNum(1, b.getHeight() - 2);
		type = b.getSquare(y, x).getSqrType();
	} while (type == SqrType::WALL);
	randPos.x = x;
	randPos.y = y;
	return randPos;
}

int randomNum(int from, int to) {
	srand(time(0));
	return rand() % (to - from + 1) + from;
}