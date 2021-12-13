#include "fruit.h"
#include "square.h"
#include<time.h>

Fruit::Fruit(const Board& b) {
	setPos(b);
}


void Fruit::setPos(const Board& b) {
	pos randPos = randomPos(b);
	setPosition(randPos.x, randPos.y, SqrType::FRUIT);
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
	y = randomNum(1, b.getHeight() - 2);
	x = randomY(b, y);
	type = b.getSquare(y, x).getSqrType();
	randPos.x = x;
	randPos.y = y;
	return randPos;
}

int randomNum(int from, int to) {
	srand(time(0));
	return rand() % (to - from + 1) + from;
}

int randomY(const Board &b, int y) {
	int counterSpaces = 0;
	std::vector<int> myvector;
	for (int i = 0; i < b.getWidth(); i++) {
		if (b.getSquare(y, i).getSqrType() != SqrType::WALL) {
			myvector.push_back(i);
		}
	}
	int size = myvector.size();
	return(myvector[rand() % size]);
}

void Fruit::oneMoveBack() {
	switch (_direction) {
	case ZERO:
		setX((getX()) - 1);
		break;
	case ONE:
		setY((getY()) - 1);
		break;
	case TWO:
		setX((getX()) + 1);
		break;
	case THREE:
		setY((getY()) + 1);
		break;
	}
}

void Fruit::Move() {
	switch ((DIRECTIONS)_direction)
	{
	case DIRECTIONS::RIGHT:
		setX((getX()) + 1);
		break;
	case DIRECTIONS::DOWN:
		setY((getY()) + 1);
		break;
	case DIRECTIONS::LEFT:
		setX((getX()) - 1);
		break;
	case DIRECTIONS::UP:
		setY((getY()) - 1);
		break;
	}
}

void Fruit::changeDirection() {
	int randomdirection = rand() % 4;
	while (randomdirection == _direction) {
		randomdirection = rand() % 4;
	}
	_direction = randomdirection;
}

void Fruit::resetFruit() {
	_direction = 0;
	_val = 0;
	setX(0);
	setY(0);
}