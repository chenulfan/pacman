#include "fruit.h"
#include<time.h>

Fruit::Fruit(const Board& b, const Square& legend) {
	setPos(b, legend);
}

void Fruit::setPos(const Board& b, const Square& legend) {
	pos randPos = randomPos(b, legend);
	setPosition(randPos.x, randPos.y, SqrType::FRUIT);
}

void Fruit::setRandomVal() {
	_val = randomNum(5, 9);
}


void Fruit::setFruit(const Board& b, const Square& legend) {
	setRandomVal();
	setPos(b, legend);
}

pos Fruit::randomPos(const Board& b, const Square& legend) {
	int x, y;
	SqrType type;
	pos randPos;
	y = randomNum(1, b.getHeight() - 2);
	x = randomX(b, y, legend);
	type = b.getSquare(y, x).getSqrType();
	randPos.x = x;
	randPos.y = y;
	return randPos;
}

int Fruit::randomNum(int from, int to) {
	srand(time(0));
	return rand() % (to - from + 1) + from;
}

int Fruit::randomX(const Board& b, int y, const Square& legend) {
	int counterSpaces = 0;
	std::vector<int> myvector;
	for (int i = 0; i < b.getWidth(); i++) {
		if (b.getSquare(y, i).getSqrType() != SqrType::WALL && !isLegend(legend,y,i)) {
			myvector.push_back(i);
		}
	}
	int size = myvector.size();
	return(myvector[rand() % size]);
}

void Fruit::oneMoveBack(char c) {
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

void Fruit::Move(char c) {
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

bool Fruit::isLegend(const Square& legend,int y,int x) {
	if (y >= legend.getY() &&y <= legend.getY() + 2) {
		if (x >= legend.getX() && x <= legend.getX() + 19)
			return true;
	}
	return false;
}