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
	_pacman.print(_isWithColor, _board.getDistantceFromStart());
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
		
		MoveAndPrintCreature(_pacman);

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
					MoveAndPrintCreature(_fruit);
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
			setPoints(_fruit.getVal());
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
			MoveAndPrintCreature(_ghosts[i]);
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
				MoveAndPrintCreature(_ghosts[i]);
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
					MoveAndPrintCreature(_ghosts[i]);
					if (isGhostHitPacman(_ghosts[i].getPosition())) {
						setHealth();
						if (getHealth() == 0) {
							return true;
						}
						resetGameAfterGhostHit();
					}
				}
				else {
						MoveAndPrintCreature(_ghosts[i]);
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
			MoveAndPrintCreature(_ghosts[i]);
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

void Game::printGhosts(int isWithColor) {
	for (int i = 0; i < _numOfGhosts; i++) {
		_ghosts[i].print(isWithColor, _board.getDistantceFromStart());
	}
}

void Game::movePacmanThruTunnel() {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	if (xPos == 0) _pacman.setX(getWidth()-1);
	else if (xPos == getWidth()-1) _pacman.setX(1);
	else if (yPos == 0) _pacman.setY(getHeight()-1);
	else if (yPos == getHeight()-1) _pacman.setY(1);
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

const bool Game::isCreatureInTunnel(Creature& creature) {
	const int xPos = creature.getX();
	const int yPos = creature.getY();
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

const bool Game::isCreatureHitWall(Creature& creature) const{
	const int xPos = creature.getX();
	const int yPos = creature.getY();
	const SqrType sqrType = _board.getSquare(yPos, xPos).getSqrType();
	if (sqrType == SqrType::WALL)
		return true;
	return false;
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

void Game::setPoints(int num ) {
	_points = getPoints() + num;
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

void Game::MoveAndPrintCreature(Creature& creature) {
	Square boardPositionOfGhost = _board.getSquare(creature.getY(), creature.getX());
	deleteCreatureLastMove(creature);
	boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());

	creature.Move(_playerKey);
	if (typeid(creature) != typeid(_pacman)) {
		while (isCreatureHitWall(creature) || isCreatureInTunnel(creature)) {
			creature.oneMoveBack(' ');
			creature.changeDirection();
			creature.Move(' ');
		}
	}
	else {
		boardPositionOfGhost.setSqrType(SqrType::EMPTY);
		boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());
		if (isCreatureHitWall(creature)) {
			creature.oneMoveBack(_playerKey);
		}
	}
	creature.print(_isWithColor, _board.getDistantceFromStart());
	if (typeid(creature) == typeid(_fruit)) { cout << _fruit.getVal(); }
}

void Game::deleteGhostLastMove(Ghost& ghost) {
	goToXY(ghost.getX(), ghost.getY() + _board.getDistantceFromStart());
	cout << " ";
}

void Game::deleteCreatureLastMove(Creature& creature) {
	goToXY(creature.getX(), creature.getY() + _board.getDistantceFromStart());
	cout << " ";
}



