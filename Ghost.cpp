#include "Ghost.h"

void Ghost::changeDir() {
	oneMoveBack();
	int randomDir = rand() % 4;
	while (randomDir == dir) {
		randomDir = rand() % 4;
	}
	switch (randomDir)
	{
		// each case update pacman and blank to the new position according to the key pressed
	case LEFT:
		_position.setX((_position.getX()) + 2);
		_blank.setX((_blank.getX()) + 2);
		break;
	case DOWN:
		_position.setY((_position.getY()) + 1);
		_blank.setY((_blank.getY()) + 1);
		break;
	case RIGHT:
		_position.setX((_position.getX()) - 2);
		_blank.setX((_blank.getX()) - 2);
		break;
	case UP:
		_position.setY((_position.getY()) - 1);
		_blank.setY((_blank.getY()) - 1);
		break;
	}
	dir = randomDir;
}
Ghost::Ghost(int dir,int x, int y)
{
	_position.setSquare(x, y, 5);
	_blank.setSquare(x, y, 0);
	color = 0;
	this->dir = dir;
}
void Ghost::Move() {
	switch (dir)
	{
		// each case update pacman and blank to the new position according to the key pressed
	case LEFT:
		_position.setX((_position.getX()) + 2);
		_blank.setX((_blank.getX()) + 2);
		break;
	case DOWN:
		_position.setY((_position.getY()) + 1);
		_blank.setY((_blank.getY()) + 1);
		break;
	case RIGHT:
		_position.setX((_position.getX()) - 2);
		_blank.setX((_blank.getX()) - 2);
		break;
	case UP:
		_position.setY((_position.getY()) - 1);
		_blank.setY((_blank.getY()) - 1);
		break;
	}
}
void Ghost::oneMoveBack() {
	switch (dir) {
	case LEFT:
		_position.setX((_position.getX()) - 2);
		_blank.setX((_blank.getX()) - 2);
		break;
	case DOWN:
		_position.setY((_position.getY()) - 1);
		_blank.setY((_blank.getY()) - 1);
		break;
	case RIGHT:
		_position.setX((_position.getX()) + 2);
		_blank.setX((_blank.getX()) + 2);
		break;
	case UP:
		_position.setY((_position.getY()) + 1);
		_blank.setY((_blank.getY()) + 1);
		break;
	}
	}