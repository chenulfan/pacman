#include "Ghost.h"

int Ghost::randomMove() {
	int randomDir = rand() % 4;
	switch (randomDir)
	{
		// each case update pacman and blank to the new position according to the key pressed
	case 0:
		_position.setX((_position.getX()) + 2);
		_blank.setX((_blank.getX()) + 2);
		break;
	case 1:
		_position.setY((_position.getY()) + 1);
		_blank.setY((_blank.getY()) + 1);
		break;
	case 2:
		_position.setX((_position.getX()) - 2);
		_blank.setX((_blank.getX()) - 2);
		break;
	case 3:
		_position.setY((_position.getY()) - 1);
		_blank.setY((_blank.getY()) - 1);
		break;
	}
	return randomDir;
}
Ghost::Ghost(int x, int y)
{
	_position.setSquare(x, y, 5);
	_blank.setSquare(x, y, 0);
	color = 0;
}
