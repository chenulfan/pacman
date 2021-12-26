#include "pacman.h"

void Pacman::Move(char playerkey) {
	
	switch (playerkey) {
	case RIGHT:
	    setX(getX() + 1);
		break;
	case LEFT:
		setX(getX() - 1);
		break;
	case UP:
		setY(getY() - 1);
		break;
	case DOWN:
		setY(getY() + 1);
		break;
	case STAY:
		break;
	}
}

void Pacman::oneMoveBack(char playerkey) {
	switch (playerkey) {
	case RIGHT:
		setX(getX() - 1);
		break;
	case LEFT:
		setX(getX() + 1);
		break;
	case UP:
		setY(getY() + 1);
		break;
	case DOWN:
		setY(getY() - 1);
		break;
	case STAY:
		break;
	}
}
