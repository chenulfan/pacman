#include "Ghost.h"



void Ghost::changeDirection() {
	int randomdirection = rand() % 4;
	while (randomdirection == _direction) {
		randomdirection = rand() % 4;
	}
	_direction = randomdirection;
}

Ghost::Ghost(int direction, int x, int y)
{
	_position.setSquare(x, y, SqrType::GHOST);
	_direction = direction;
	_startX = x;
	_startY = y;
}

Ghost& Ghost::operator=(Ghost& s) {
	_position = s._position;
	_direction = s._direction;
	_startX = s._startX;
	_startY = s._startY;
	return *this;
}


void Ghost::Move() {
	switch ((DIRECTIONS)_direction)
	{
	case DIRECTIONS::RIGHT:
		_position.setX((_position.getX()) + 1);
		break;
	case DIRECTIONS::DOWN:
		_position.setY((_position.getY()) + 1);
		break;
	case DIRECTIONS::LEFT:
		_position.setX((_position.getX()) - 1);
		break;
	case DIRECTIONS::UP:
		_position.setY((_position.getY()) - 1);
		break;
	}
}
void Ghost::oneMoveBack() {
	switch (_direction) {
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
void Ghost::changePosition(const int y, const int x) {
	setX(x);
	setY(y);
}

//bool** Ghost::initArr() {
//	bool** arr = new bool * [_height];
//	for (int i = 0; i < _height; ++i) {
//		arr[i] = new bool[_width];
//	}
//	return arr;
//}

//void Ghost::SmartMove(const Pacman& pacman, const Board& b) {
//	queSquare tempNode,nodeFront;
//	int x, y,counter,firstIteration = 0;;
//	bool** visited = initArr();
//	queue<queSquare> queue;
//	Square arr[4] = {};
//	queSquare start = { _position };
//	queue.push(start);
//	while (!queue.empty()) {
//		nodeFront = queue.front();
//		queue.pop();
//		x = nodeFront.currSquare.getX();
//		y = nodeFront.currSquare.getY();
//		visited[y][x] = true;
//		if (x == pacman.getX() && y == pacman.getY()) {
//			break;
//		}
//		else {
//			arr[0] = b.getSquare(y, x+1);
//			arr[1] = b.getSquare(y, x-1);
//			arr[2] = b.getSquare(y+1, x);
//			arr[3] = b.getSquare(y-1, x);
//			counter = 0;
//			for (Square i : arr) { 
//				x = i.getX();
//				y = i.getY();
//				if (!visited[y][x] && i.getSqrType() != SqrType::WALL && !(isTunnel(i))) {
//					if (!firstIteration) {
//						if (counter == 0) { tempNode = { i,DIRECTIONS::RIGHT }; }
//						if (counter == 1) { tempNode = { i,DIRECTIONS::LEFT }; }
//						if (counter == 2) { tempNode = { i,DIRECTIONS::DOWN }; }
//						if (counter == 3) { tempNode = { i,DIRECTIONS::UP }; }
//					}
//					else { tempNode = { i,nodeFront.move };}
//					queue.push(tempNode);
//				}
//				counter++;
//			}
//		}
//		firstIteration++;
//	}
//	
//	_direction = (int)nodeFront.move;
//}

//const bool Ghost::isTunnel(Square& position) const {
//	//const int xPos = position.getX();
//	//const int yPos = position.getY();
//	//if (xPos == 0 || xPos == _width - 1 || yPos == 0 || yPos == _height - 1)
//	//	return true;
//	return false;
//}
