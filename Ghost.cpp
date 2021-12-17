#include "Ghost.h"
void printArr(const int height, const int width, int** arr);
void resetArr(const int height, const int width, int** arr);

void Ghost::changeDirection() {
	int randomdirection = rand() % 4;
	while (randomdirection == _direction) {
		randomdirection = rand() % 4;
	}
	_direction = randomdirection;
}

Ghost::Ghost(int direction, int x, int y)
{
	setPosition(x,y,SqrType::GHOST);
	_direction = direction;
	_startX = x;
	_startY = y;
}

Ghost& Ghost::operator=(Ghost& s) {
	Square pos = s.getPosition();
	setPosition(pos);
	_direction = s._direction;
	_startX = s._startX;
	_startY = s._startY;
	return *this;
}


void Ghost::Move() {
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
void Ghost::oneMoveBack() {
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
void Ghost::changePosition(const int y, const int x) {
	setX(x);
	setY(y);
}

int** Ghost::initArr(const int height,const int width) {
	int** arr = new int * [height];
	for (int i = 0; i < height; ++i) {
		arr[i] = new int[width];
		for (int j = 0; j < width; ++j) {
			arr[i][j] = 0;
		}
	}
	return arr;
}

void Ghost::SmartMove(const Pacman& pacman, Square** b,const int height,const int width) {
	queSquare tempNode,nodeFront;
	int counter2 = 0;
	int x, y,counter,firstIteration = 0;;
	int** visited = initArr(height,width);
	queue<queSquare> queue;
	Square arr[4] = {};
	queSquare start = { getPosition() };
	queue.push(start);
	while (!queue.empty()) {
		nodeFront = queue.front();
		queue.pop();
		x = nodeFront.currSquare.getX();
		y = nodeFront.currSquare.getY();
		visited[y][x] = 1;
		if (x == pacman.getX() && y == pacman.getY()) {
			break;
		}
		else {
			arr[0] = b[ y ][ x + 1 ];
			arr[1] = b[ y ][ x-1];
			arr[2] = b[ y+1 ][ x ];
			arr[3] = b[ y-1 ][ x ];
			counter = 0;
			for (Square i : arr) { 
				x = i.getX();
				y = i.getY();
				if (visited[y][x] == 0 && i.getSqrType() != SqrType::WALL && !(isTunnel(i,height,width))) {
					if (!firstIteration) {
						if (counter == 0) { tempNode = { i,DIRECTIONS::RIGHT }; }
						if (counter == 1) { tempNode = { i,DIRECTIONS::LEFT }; }
						if (counter == 2) { tempNode = { i,DIRECTIONS::DOWN }; }
						if (counter == 3) { tempNode = { i,DIRECTIONS::UP }; }
					}
					else { tempNode = { i,nodeFront.move };}
					queue.push(tempNode);
					counter2++;
				}
				counter++;
			}
		}
		if (counter2 >= 20000) {
			notSmartMove(pacman,b,height,width);
			return;
		}
		firstIteration++;
	}
	
	_direction = (int)nodeFront.move;
}
void resetArr(const int height, const int width,int** arr) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			arr[i][j] = 0;
		}
	}
}

const bool Ghost::isTunnel(Square& position,const int height,const int width) const {
	const int xPos = position.getX();
	const int yPos = position.getY();
	if (xPos == 0 || xPos == width - 1 || yPos == 0 || yPos == height - 1)
		return true;
	return false;
}


void printArr(const int height, const int width,int** arr) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			cout << arr[i][j];
		}
		cout << endl;
	}
}

void Ghost::notSmartMove(const Pacman& pacman, Square** b, const int height, const int width) {
	int x = getX(), y = getY();
	if (pacman.getY() != y) {
		if (pacman.getY() > y && b[y + 1][x].getSqrType() != SqrType::WALL) { 
			_direction = 1;
			return;
		}
		else {
			if (pacman.getY() < getY() && b[y - 1][x].getSqrType() != SqrType::WALL) 
				_direction = 3; 
			else if (pacman.getX() > x) 
				_direction = 0;
			else 
				_direction = 2;
			return;
		}

		if (pacman.getX() > x)
			_direction = 0;
		else 
			_direction = 2;
		return; 
	}

	if (pacman.getX() > x)
		_direction = 0;
	else
		_direction = 2;
}