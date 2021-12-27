#include "Game.h"
#include "square.h"
#include "board.h"
#include <cctype>

char playerKeyToDir(char key);
DIRECTIONS charToDir(char dir);
int charToPlayerKey(char dir);

void Game::printBanner()const {
	goToXY(_legend.getX(), _legend.getY());
	if (_isWithColor) changeColor(10);
	cout << "Life: " << getHealth() << " | Score: " << getPoints();
	goToXY(_pacman.getX(), _pacman.getY() + _board.getDistantceFromStart());
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

int Game::startGame(bool isWithColor, string filename, Level type, bool saveToFile) {
	char prevKey = RIGHT;
	ofstream file;
	int maxPoints = 0, result, smartMoveDirection, counterGhostsMoves = 0, fruitCounterMoves = 0, totalCounterMoves = 1;
	bool printCreatureFlag = 1, fruitFlag = false;
	Square pacmanStart;
	int random = 20 + rand() % 30;
	setWithColor(isWithColor);

	if (saveToFile) {
		file.open("test.txt");
		_saveToFile = true;
	}

	result = _board.initBoard(_ghosts, _numOfGhosts, pacmanStart, _legend, filename, maxPoints);
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

		if (saveToFile) {
			file << totalCounterMoves;
		}

		prevKey = _playerKey;
		Sleep(SPEED);

		if (_kbhit()) { // if any key was hit
			_playerKey = tolower(getKey());  // change direction
			if (_playerKey != LEFT && _playerKey != UP && _playerKey != DOWN && _playerKey != RIGHT && _playerKey != STAY && _playerKey != ESC) {
				_playerKey = prevKey;
			}
		}

		if (_playerKey == ESC) continue;

		MoveAndPrintCreature(_pacman, file);

		if (isPacmanHitGhost(_pacman.getPosition())) {
			return 1;
		}

		//save to file num of ghosts
		if (_saveToFile) {
			file << ',';
			file << _numOfGhosts;
		}

		if (printCreatureFlag) {

			if (printGhostsAndCheckifGhostHitPacman(type, counterGhostsMoves, file)) {
				return 1;
			}

			if (counterGhostsMoves == 25)
				counterGhostsMoves = 0;
			else counterGhostsMoves++;

			if (fruitFlag) {
				if (!(_fruit.getVal() == 0)) {
					MoveAndPrintCreature(_fruit, file);
				}
			}
			printCreatureFlag = 0;
		}

		else {
			printCreatureFlag = 1;
			if (_saveToFile) {
				for (int i = 0; i < _numOfGhosts; i++) {
					file << ',';
					file << 'S';
				}
				if (fruitFlag) {
					file << ',';
					file << 'S';
				}
			}
		}

		if (fruitCounterMoves == random) {
			if (!fruitFlag) {
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				_fruit.setFruit(_board, getLegend());
				_fruit.getPosition().print(isWithColor, _board.getDistantceFromStart());
				cout << _fruit.getVal();
				if (_saveToFile) {
					file << ',';
					file << 'F';
					file << ',';
					file << _fruit.getX();
					file << ',';
					file << _fruit.getY();
				}
				fruitFlag = true;
				fruitCounterMoves = 0;
			}
			else {
				fruitFlag = false;
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				fruitCounterMoves = 0;
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

		fruitCounterMoves++;
		totalCounterMoves++;
		if (_saveToFile) {
			file << '\n';
		}
	}
	return 0;
}

int Game::loadGame(bool isWithColor, string boardFileName,string gameFile) {
	fstream file;
	string line;
	char* linecopy;
	file.open(gameFile);
	int maxPoints = 0, result, smartMoveDirection,iterationCounter,counterGhosts;
	Square pacmanStart;
	setWithColor(isWithColor);
	result = _board.initBoard(_ghosts, _numOfGhosts, pacmanStart, _legend, boardFileName, maxPoints);
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
	while (getline(file, line)) {
		Sleep(SPEED);
		iterationCounter = 0;
		counterGhosts = 0;
		linecopy = new char[line.size()];
		strcpy(linecopy, line.c_str());
		char* pch,* fruitX,* fruitY;
		pch = strtok(linecopy, ",");
		while (pch != NULL)
		{
			if (iterationCounter == 1) //pacman 
			{
				MoveAndPrintLoadedCreature(_pacman, *pch);
				if (isPacmanHitGhost(_pacman.getPosition())) {
					return 1;
				}
			}
			if (iterationCounter >= 3 && iterationCounter < (_numOfGhosts + 3)) //ghosts 
			{
				MoveAndPrintLoadedCreature(_ghosts[counterGhosts], *pch);
				counterGhosts++;
			}
			if (iterationCounter >= _numOfGhosts + 3)//fruit 
			{
				if (*pch == 'F') {
					fruitX = strtok(NULL, ",");
					fruitY = strtok(NULL, ",");
					iterationCounter = iterationCounter + 2;
				}
			}
			pch = strtok(NULL, ",");
			iterationCounter++;
		}
	}
	int wtf = 5;
	return 0;

}

bool Game::printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves, ofstream& file) {
	switch (int(type)) {
	case 0:
		for (int i = 0; i < _numOfGhosts; i++) {
			_ghosts[i].SmartMove(_pacman, _board.getArrSquare(), _board.getHeight(), _board.getWidth());
			MoveAndPrintCreature(_ghosts[i], file);
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
		for (int i = 0; i < _numOfGhosts; i++) {
			if (counterGhostsMoves < 20) {
				_ghosts[i].SmartMove(_pacman, _board.getArrSquare(), _board.getHeight(), _board.getWidth());
				MoveAndPrintCreature(_ghosts[i], file);
				if (isGhostHitPacman(_ghosts[i].getPosition())) {
					setHealth();
					if (getHealth() == 0) {
						return true;
					}
					resetGameAfterGhostHit();
				}
			}
			else {
				if (counterGhostsMoves == 20) {
					_ghosts[i].changeDirection();
					MoveAndPrintCreature(_ghosts[i], file);
					if (isGhostHitPacman(_ghosts[i].getPosition())) {
						setHealth();
						if (getHealth() == 0) {
							return true;
						}
						resetGameAfterGhostHit();
					}
				}
				else {
					MoveAndPrintCreature(_ghosts[i], file);
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
		for (int i = 0; i < _numOfGhosts; i++) {
			if (counterGhostsMoves == 20) {
				_ghosts[i].changeDirection();
			}
			MoveAndPrintCreature(_ghosts[i], file);
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
		_pacman.setX(getWidth() - 2);
		isParallelTunnelIsFood(yPos, getWidth() - 1);
	}
	else if (xPos == getWidth() - 1) {
		_pacman.setX(1);
		isParallelTunnelIsFood(yPos, 0);
	}
	else if (yPos == 0) {
		_pacman.setY(getHeight() - 2);
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

	if (ret)
		return true;
	return false;
}


const bool Game::isCreatureHitWall(Creature& creature) const {
	const int xPos = creature.getX();
	const int yPos = creature.getY();
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

const bool Game::isGhostHitPacman(Square position) {
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
	_playerKey = STAY;
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

void Game::MoveAndPrintCreature(Creature& creature, ofstream& file) {
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
		// save to file ghost i

		file << ',';
		file << intToDir(creature.getDirection());
	}
	else {
		boardPositionOfGhost.setSqrType(SqrType::EMPTY);
		boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());
		if (isCreatureHitWall(creature)) {
			creature.oneMoveBack(_playerKey);
			if (_saveToFile) {
				file << ',';
				file << 'S';
			}
		}
		else if (_saveToFile) {
			char temp = playerKeyToDir(_playerKey);
			file << ',';
			file << temp;
		}
	}
	creature.print(_isWithColor, _board.getDistantceFromStart());
	if (typeid(creature) == typeid(_fruit)) { cout << _fruit.getVal(); }
}

void Game::MoveAndPrintLoadedCreature(Creature& creature,char dir) {
	Square boardPositionOfGhost = _board.getSquare(creature.getY(), creature.getX());
	deleteCreatureLastMove(creature);
	boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());

	if (typeid(creature) != typeid(_pacman)) {
		creature.setDirection(int(charToDir(dir)));
		creature.Move(' ');
	}
	else {
		boardPositionOfGhost.setSqrType(SqrType::EMPTY);
		boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());
		creature.Move(char(charToPlayerKey(dir)));
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



char playerKeyToDir(char key) {
	switch (key) {
	case UP:
		return 'U';
	case DOWN:
		return 'D';
	case LEFT:
		return 'L';
	case RIGHT:
		return 'R';
	case STAY:
		return 'S';
	}
}

char intToDir(int num) {
	switch (num) {
	case (int)DIRECTIONS::RIGHT:
		return 'R';
	case (int)DIRECTIONS::LEFT:
		return 'L';
	case (int)DIRECTIONS::UP:
		return 'U';
	case (int)DIRECTIONS::DOWN:
		return 'D';
	}
}

int charToPlayerKey(char dir) {
	switch (dir) {
	case 'U':
		return UP;
	case 'D':
		return DOWN;
	case 'L':
		return LEFT;
	case 'R':
		return RIGHT;
	case 'S':
		return STAY;
	}
}

DIRECTIONS charToDir(char dir) {
	switch (dir) {
	case 'U':
		return DIRECTIONS::UP;
	case 'D':
		return DIRECTIONS::DOWN;
	case 'L':
		return DIRECTIONS::LEFT;
	case 'R':
		return DIRECTIONS::RIGHT;
	}
}