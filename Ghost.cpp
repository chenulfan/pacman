#include "Ghost.h"

void Ghost::changeDirection() {
	int randomdirection = rand() % 4;
	while (randomdirection == direction) {
		randomdirection = rand() % 4;
	}
	direction = randomdirection;
}
Ghost::Ghost(int direction,int x, int y)
{
	_position.setSquare(x, y, Square::GHOST);
	this->direction = direction;
}
void Ghost::Move() {
	switch (direction)
	{
	case ZERO:
		_position.setX((_position.getX()) + 1);
		break;
	case ONE:
		_position.setY((_position.getY()) + 1);
		break;
	case TWO:
		_position.setX((_position.getX()) - 1);
		break;
	case THREE:
		_position.setY((_position.getY()) - 1);
		break;
	}
}
void Ghost::oneMoveBack() {
	switch (direction) {
	case ZERO:
		_position.setX((_position.getX()) - 1);
		break;
	case ONE:
		_position.setY((_position.getY()) - 1);
		break;
	case TWO:
		_position.setX((_position.getX()) + 1);
		break;
	case THREE:
		_position.setY((_position.getY()) + 1);
		break;
	}
	}
void Ghost::changePosition(int y, int x) {
	setX(x);
	setY(y);
}