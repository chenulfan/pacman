#include "Game.h"
#include "square.h"
#include "board.h"
#include <cctype>



void Game::printBanner()const {
	goToXY(_legend.getX(), _legend.getY());
	if(_isWithColor) changeColor(10);
	cout << "Life: " << getHealth() << " | Score: " << getPoints();
	goToXY(_pacman.getX(), _pacman.getY() + _board.getDistantceFromStart());
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

int Game::startGame(bool isWithColor,string filename,Level type) {
	char prevKey = RIGHT;
	int maxPoints =0 ,result, smartMoveDirection, counterGhostsMoves = 0, totalCounterMoves = 0;;
	bool printCreatureFlag = 1,fruitFlag = false;
	Square pacmanStart;
	int random = 20 +  rand() % 30;
	setWithColor(isWithColor);
	
	result = _board.initBoard(_ghosts, _numOfGhosts, pacmanStart, _legend,filename,maxPoints);
	if (result != 1) {
		return result;
	}
	setMaxPoints(maxPoints);

	goToXY(0, _board.getDistantceFromStart());

	_board.printBoard(isWithColor);

	_pacman = pacmanStart;

	printGhosts(isWithColor);

	printBanner();


	while (_health != 0 && _points < _maxPoints) {
		prevKey = _playerKey;
		Sleep(SPEED);

		if (_kbhit()) { // if any key was hit
			_playerKey = tolower(getKey());  // change direction
			if (_playerKey != LEFT && _playerKey != UP && _playerKey != DOWN && _playerKey != RIGHT && _playerKey != STAY && _playerKey != ESC) {
				_playerKey = prevKey;
			}
		}

		if (_playerKey == ESC) continue;

		whichDirectionMovePacman();

		_pacman.print(isWithColor, _board.getDistantceFromStart());

		if (isPacmanHitGhost(_pacman.getPosition())) {
			return 1;
		}

		if (printCreatureFlag) {
			if (printGhostsAndCheckifGhostHitPacman(type, counterGhostsMoves)) {
				return 1;
			}
			if (counterGhostsMoves == 25) { counterGhostsMoves = 0; }
			else { counterGhostsMoves++; }
			if (fruitFlag) {
				if (!(_fruit.getVal() == 0)) {
					MoveAndPrintFruit();
				}
			}
			printCreatureFlag = 0;
		}

		else { printCreatureFlag = 1; }

		if (totalCounterMoves == random) {
			if (!fruitFlag) {
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				_fruit.setFruit(_board,getLegend());
				_fruit.getPosition().print(isWithColor, _board.getDistantceFromStart());
				cout << _fruit.getVal();
				fruitFlag = true;
				totalCounterMoves = 0;
			}
			else { 
				fruitFlag = false;
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				totalCounterMoves = 0;
			}
		}

		if (isPacmanAteFood()) {
			_board.setSqrType(_pacman.getY(), _pacman.getX(), SqrType::EMPTY);
			setPoints();
		}
		if (isTunnel(prevKey)) {
			deletePacmanLastMove();
			movePacmanThruTunnel();
			if (isPacmanAteFood()) 
				setPoints();
		}

		if (isPacmanAteFruit(_fruit)) {
			_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
			_allPoints += _fruit.getVal();
			printBanner();
			_fruit.resetFruit();
		}

		for (int i = 0; i < _numOfGhosts; ++i) {
			if (isGhostAteFruit(_fruit, _ghosts[i])) {
					_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
			}
		}

		totalCounterMoves++;

	}
	return 0;
}

bool Game::printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves) {
	switch (int(type)) {
	case 0:
		for (int i = 0; i < _numOfGhosts; i++) {
			_ghosts[i].SmartMove(_pacman, _board.getArrSquare(), _board.getHeight(), _board.getWidth());
			MoveAndPrintGhost(_ghosts[i]);
			if (isGhostHitPacman(_ghosts[i].getPosition())) {
				setHealth();
				if (getHealth() == 0) {
					return true;
				}
				resetGameAfterGhostHit();
			}
		}
		break;
	case 1:
		for (int i = 0; i < _numOfGhosts;i++) {
			if (counterGhostsMoves < 20) {
				_ghosts[i].SmartMove(_pacman, _board.getArrSquare(), _board.getHeight(), _board.getWidth());
				MoveAndPrintGhost(_ghosts[i]);
				if (isGhostHitPacman(_ghosts[i].getPosition())) {
					setHealth();
					if (getHealth() == 0) {
						return true;
					}
					resetGameAfterGhostHit();
				}
			}
			else  {
				if (counterGhostsMoves == 20) {
					_ghosts[i].changeDirection();
					MoveAndPrintGhost(_ghosts[i]);
					if (isGhostHitPacman(_ghosts[i].getPosition())) {
						setHealth();
						if (getHealth() == 0) {
							return true;
						}
						resetGameAfterGhostHit();
					}
				}
				else {
						MoveAndPrintGhost(_ghosts[i]);
						if (isGhostHitPacman(_ghosts[i].getPosition())) {
							setHealth();
							if (getHealth() == 0) {
								return true;
							}
							resetGameAfterGhostHit();
						}
					}
			}
		}
		break;
	case 2:
		for (int i = 0; i < _numOfGhosts;i++) {
			if (counterGhostsMoves == 20) {
				_ghosts[i].changeDirection();
			}
			MoveAndPrintGhost(_ghosts[i]);
			if (isGhostHitPacman(_ghosts[i].getPosition())) {
				setHealth();
				if (getHealth() == 0) {
					return true;
				}
				resetGameAfterGhostHit();
			}
		}
		break;
	}
	return false;
}

const bool Game::isPacmanAteFruit(const Fruit& fruit) const {
	return _pacman.getPosition().getX() == fruit.getX() && _pacman.getPosition().getY() == fruit.getY();
}

const bool Game::isGhostAteFruit(const Fruit& fruit, const Ghost& ghost) const {
	return ghost.getX() == fruit.getX() && ghost.getY() == fruit.getY();
}

void Game::whichDirectionMovePacman() {
	switch (_playerKey) {
	case RIGHT:
		if (!isNextMoveIsAWall(_pacman.getX() + 1, _pacman.getY(), _board)) {
			deletePacmanLastMove();
			_pacman.setX(_pacman.getX() + 1);
		}
		break;
	case LEFT:
		if (!isNextMoveIsAWall(_pacman.getX() - 1, _pacman.getY(), _board)) {
			deletePacmanLastMove();
			_pacman.setX(_pacman.getX() - 1);
		}
		break;
	case UP:
		if (!isNextMoveIsAWall(_pacman.getX(), _pacman.getY() - 1, _board)) {
			deletePacmanLastMove();
			_pacman.setY(_pacman.getY() - 1);
		}
		break;
	case DOWN:
		if (!isNextMoveIsAWall(_pacman.getX(), _pacman.getY() + 1, _board)) {
			deletePacmanLastMove();
			_pacman.setY(_pacman.getY() + 1);
		}
		break;
	case STAY:
		break;
	}
}

void Game::printGhosts(int isWithColor) {
	for (int i = 0; i < _numOfGhosts; i++) {
		_ghosts[i].print(isWithColor, _board.getDistantceFromStart());
	}
}

void Game::isParallelTunnelIsFood(int yPos, int xPos) {
	if (_board.getSquare(yPos, xPos).getSqrType() == SqrType::FOOD) {
		setPoints();
		_board.setSqrType(yPos, xPos, SqrType::EMPTY);
		_board.getSquare(yPos, xPos).print(_isWithColor, _board.getDistantceFromStart());
	}
}

void Game::movePacmanThruTunnel() {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	if (xPos == 0) {
		_pacman.setX(getWidth()-2);
		isParallelTunnelIsFood(yPos, getWidth() - 1);
	}
	else if (xPos == getWidth() - 1) {
		_pacman.setX(1);
		isParallelTunnelIsFood(yPos, 0);
	}
	else if (yPos == 0) {
		_pacman.setY(getHeight()-2);
		isParallelTunnelIsFood(getHeight() - 1, xPos);
	}
	else if (yPos == getHeight() - 1) {
		_pacman.setY(1);
		isParallelTunnelIsFood(0, xPos);
	}
}

const bool Game::isTunnel(char& playerKey) {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	bool ret;
	if (xPos == 0 )
		ret = _board.getSquare(yPos, getWidth() - 1).getSqrType() != SqrType::WALL;
	else if (xPos == getWidth() - 1) 
		ret = _board.getSquare(yPos, 0).getSqrType() != SqrType::WALL;
	else if(yPos == 0)
		ret = _board.getSquare(getHeight() - 1, xPos).getSqrType() != SqrType::WALL;
	else if(yPos == getHeight() - 1)
		ret = _board.getSquare(0, xPos).getSqrType() != SqrType::WALL;
	else {
		return false;
	}

	if (ret) 
		return true;
	setPlayerKey(STAY);
	return false;
}


const bool Game::isCreatureInTunnel(Square pos) {
	const int xPos = pos.getX();
	const int yPos = pos.getY();
	bool ret;
	if (xPos == 0)
		ret = _board.getSquare(yPos, getWidth() - 1).getSqrType() != SqrType::WALL;
	else if (xPos == getWidth() - 1)
		ret = _board.getSquare(yPos, 0).getSqrType() != SqrType::WALL;
	else if (yPos == 0)
		ret = _board.getSquare(getHeight() - 1, xPos).getSqrType() != SqrType::WALL;
	else if (yPos == getHeight() - 1)
		ret = _board.getSquare(0, xPos).getSqrType() != SqrType::WALL;
	else {
		return false;
	}

	if (ret)
		return true;
	return false;
}

void Game::MoveAndPrintGhost(Ghost& ghost) {
	Square boardPositionOfGhost = _board.getSquare(ghost.getY(), ghost.getX());
	deleteGhostLastMove(ghost);
	boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());

	ghost.Move();
	while (isCreatureHitWall(ghost.getPosition()) || isCreatureInTunnel(ghost.getPosition())) {
		ghost.oneMoveBack();
		ghost.changeDirection();
		ghost.Move();
	}
	ghost.print(_isWithColor, _board.getDistantceFromStart());
}

const bool Game::isCreatureHitWall(Square position) const {
	const int xPos = position.getX();
	const int yPos = position.getY();
	const SqrType sqrType = _board.getSquare(yPos, xPos).getSqrType();
	if (sqrType == SqrType::WALL)
		return true;
	return false;
}

const bool Game::isPacmanAteFood() const {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	const SqrType sqrType = _board.getSquare(yPos, xPos).getSqrType();
	return sqrType == SqrType::FOOD;
}

void Game::deletePacmanLastMove() {
	_board.setSqrType(_pacman.getY(), _pacman.getX(), SqrType::EMPTY);
	goToXY(_pacman.getX(), _pacman.getY() + _board.getDistantceFromStart());
	cout << " ";
}

void Game::deleteGhostLastMove(Ghost& ghost) {
	goToXY(ghost.getX(), ghost.getY() + _board.getDistantceFromStart());
	cout << " ";
}

void Game::deleteFruitLastMove(Fruit& fruit) {
	goToXY(fruit.getX(), fruit.getY() + _board.getDistantceFromStart());
	cout << " ";
}

const bool Game::isNextMoveIsAWall(const int x, const int y,  const Board& b) const {
	Square pos = b.getSquare(y, x);
	return pos.getSqrType() == SqrType::WALL;
}

const bool Game::isGhostHitPacman(Square position){
	if (position.getX() == _pacman.getX() && position.getY() == _pacman.getY())
		return true;
	return false;
}


int Game::getKey()const
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}


void Game::resetGameAfterGhostHit() {
	_pacman.moveToStartPosition();
	for (int i = 0; i < _numOfGhosts; i++) {
		deleteGhostLastMove(_ghosts[i]);
		_ghosts[i].changePosition(_ghosts[i].getStartY(), _ghosts[i].getStartX()); // TODO: CHNAGE INIT VALUE MAKE START POSITION
	}
}

void Game::setPoints() {
	_points += 1;
	_allPoints += 1;
	printBanner();
};

void Game::setHealth() { 
	_health = getHealth() - 1;
	printBanner();
};

void Game::resetGame() {
	_board.resetBoard();
	_points = 0;
	_maxPoints = 0;
	_numOfGhosts = 0;
}

const bool Game::isPacmanHitGhost(const Square& position) {
	for (int i = 0; i < _numOfGhosts; i++) {
		if ((position.getX() == _ghosts[i].getX() && position.getY() == _ghosts[i].getY())) {
			setHealth();
			if (getHealth() == 0) {
					return true;
				}
				resetGameAfterGhostHit();
			}
		}
	return false;
	}

void Game::MoveAndPrintFruit() {
	Square boardPositionOfFruit = _board.getSquare(_fruit.getY(), _fruit.getX());
	deleteFruitLastMove(_fruit);
	boardPositionOfFruit.print(_isWithColor, _board.getDistantceFromStart());
	_fruit.Move();
	while (isCreatureHitWall(_fruit.getPosition()) || isCreatureInTunnel(_fruit.getPosition())) {
		_fruit.oneMoveBack();
		_fruit.changeDirection();
		_fruit.Move();
	}
	_fruit.print(_isWithColor, _board.getDistantceFromStart());
	cout << _fruit.getVal();
}

//void Game::printMenu()const {
//	cout << endl << " (1) Start a new game without colors" << endl << " (2) Start a new game with colors" << endl
//		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
//}
//
//void Game::printInstructions()const {
//	cout << endl << "The instructions are: " << endl;
//	cout << "  Press W to move up" << endl;
//	cout << "  Press D to move right" << endl;
//	cout << "  Press A to move left" << endl;
//	cout << "  Press X to move down" << endl;
//	cout << "  Press S to stay in your place" << endl;
//	cout << "  You have 4 tunnel each side of the board which you can teleport to other side! TRY THEM" << endl;
//	cout << "  Your goal is to eat all the breadcrumbs without being eaten by the ghosts!" << endl;
//	cout << "  You have 3 life to achieve that, each time you get eaten by a ghost ur life will be reduce by 1" << endl;
//	cout << "  The amount of lifes left will be indicated under the game board, when you reach 0 you lose" << endl;
//	cout << "  Have FUN" << endl << endl;
//}


// TODO DELETE:

//int Game::smartMove(const Ghost& ghost) {
//	queSquare tempNode,nodeFront;
//	int x, y,counter,firstIteration = 0;;
//	bool** visited = initArr();
//	queue<queSquare> queue;
//	Square arr[4] = {};
//	queSquare start = { ghost.getPosition() };
//	queue.push(start);
//	while (!queue.empty()) {
//		nodeFront = queue.front();
//		queue.pop();
//		x = nodeFront.currSquare.getX();
//		y = nodeFront.currSquare.getY();
//		visited[y][x] = true;
//		if (x == _pacman.getX() && y == _pacman.getY()) {
//			break;
//		}
//		else {
//			arr[0] = _board.getSquare(y, x+1);
//			arr[1] = _board.getSquare(y, x-1);
//			arr[2] = _board.getSquare(y+1, x);
//			arr[3] = _board.getSquare(y-1, x);
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
//	return (int)nodeFront.move;
//}
//
//bool** Game::initArr() {
//	int height = _board.getHeight();
//	int width = _board.getWidth();
//	bool** arr = new bool* [height];
//	for (int i = 0; i < height; ++i) {
//		arr[i] = new bool[width];
//	}
//	return arr;
//}
//
//const bool Game::isTunnel(Square& position) const {
//	int height = _board.getHeight();
//	int width = _board.getWidth();
//	const int xPos = position.getX();
//	const int yPos = position.getY();
//	if (xPos == 0 || xPos == width - 1 || yPos == 0 || yPos == height - 1)
//		return true;
//	return false;
//}
//

//void Game::printMenu()const {
//	cout << endl << " (1) Start a new game without colors" << endl << " (2) Start a new game with colors" << endl
//		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
//}
//
//void Game::printInstructions()const {
//	cout << endl << "The instructions are: " << endl;
//	cout << "  Press W to move up" << endl;
//	cout << "  Press D to move right" << endl;
//	cout << "  Press A to move left" << endl;
//	cout << "  Press X to move down" << endl;
//	cout << "  Press S to stay in your place" << endl;
//	cout << "  You have 4 tunnel each side of the board which you can teleport to other side! TRY THEM" << endl;
//	cout << "  Your goal is to eat all the breadcrumbs without being eaten by the ghosts!" << endl;
//	cout << "  You have 3 life to achieve that, each time you get eaten by a ghost ur life will be reduce by 1" << endl;
//	cout << "  The amount of lifes left will be indicated under the game board, when you reach 0 you lose" << endl;
//	cout << "  Have FUN" << endl << endl;
//}


//int Game::smartMove(const Ghost& ghsot) {
//	queue<string> queue;
//	int direction;
//	queue.push("");
//	int row, col;
//	row = ghsot.getY();
//	col = ghsot.getY();
//	string moves = "";
//
//	while (!foundPacman(row, col, moves)) {
//		string arr = { 'U', 'D', 'L', 'R' };
//		string top = queue.front();
//		queue.pop();
//		for (auto key : arr) {
//			if (isValidMove(row, col, moves)) {
//				queue.push(top + key);
//			}
//		}
//		moves = queue.front();
//	}
//	switch (moves[0]) {
//	case 'U':
//		direction = (int)DIRECTIONS::UP;
//	case 'D':
//		direction = (int)DIRECTIONS::DOWN;
//	case 'L':
//		direction = (int)DIRECTIONS::LEFT;
//	case 'R':
//		direction = (int)DIRECTIONS::RIGHT;
//	}
//	return direction;
//}
//
//
//bool Game::isValidMove(int row, int col, string moves) {
//	for (auto move : moves) {
//		if (move == 'L')
//			col -= 1;
//		else if (move == 'R')
//			col += 1;
//		else if (move == 'U')
//			row -= 1;
//		else if (move == 'D')
//			row += 1;
//	}

//	if (_board.getSquare(row, col).getSqrType() == SqrType::WALL)
//		return false;
//	if (row < 0 || row > _board.getHeight() - 1)
//		return false;
//	if (col < 0 || col > _board.getWidth() - 1)
//		return false;
//	return true;
//}
//
//bool Game::foundPacman(int row, int col, string moves) {
//	for (auto move : moves) {
//		if (move == 'L')
//			col -= 1;
//		else if (move == 'R')
//			col += 1;
//		else if (move == 'U')
//			row -= 1;
//		else if (move == 'D')
//			row += 1;
//	}
//	if (row == 10) {
//		int z = 0;
//	}
//	if (_board.getSquare(row, col).getSqrType() == SqrType::PACMAN)
//		return true;
//	return false;
//}

//
//void Game::gameOver(const bool isWon) {
//	clear(); // clears the console;
//	char ch;
//	if(isWon)
//		cout << "You WON!!" << endl;
//	else
//		cout << "GAME OVER" << endl;
//	cout << "press any key to return to the menu..." << endl;
//	cin >> ch;
//}

//void Game::clear() {
//	COORD topLeft = { 0, 0 };
//	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_SCREEN_BUFFER_INFO screen;
//	DWORD written;
//
//	GetConsoleScreenBufferInfo(console, &screen);
//	FillConsoleOutputCharacterA(
//		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
//	);
//	FillConsoleOutputAttribute(
//		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
//		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
//	);
//	SetConsoleCursorPosition(console, topLeft);
//}
