#include "Game.h"
#include "square.h"
#include "board.h"
#include <cctype>

char playerKeyToDir(char key);
DIRECTIONS charToDir(char dir);
int charToPlayerKey(char dir);

void Game::printBanner()const {
	if (!_isSilentMode) {
		goToXY(_legend.getX(), _legend.getY());
		if (_isWithColor) changeColor(10);
		cout << "Life: " << getHealth() << " | Score: " << getPoints();
		goToXY(_pacman.getX(), _pacman.getY() + _board.getDistantceFromStart());
	}
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

int Game::startGame(bool isWithColor, string filename, Level type, bool saveToFile) {
	char prevKey = RIGHT;
	int maxPoints = 0, result, smartMoveDirection, counterGhostsMoves = 0, fruitCounterMoves = 0;
	bool printCreatureFlag = 1, fruitFlag = false;
	Square pacmanStart;
	int random = 20 + rand() % 30;
	setWithColor(isWithColor);

	if (saveToFile) {
		string fileNameWithoutExtension = filename.substr(0, filename.find("."));
		setStepsFile(fileNameWithoutExtension + ".steps");
		setResultFile(fileNameWithoutExtension + ".result");
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
			_stepsFile << _totalCounterMoves;
		}

		prevKey = _playerKey;

		Sleep(SPEED);

		if (_kbhit()) { 
			_playerKey = tolower(getKey());  
			if (_playerKey != LEFT && _playerKey != UP && _playerKey != DOWN && _playerKey != RIGHT && _playerKey != STAY && _playerKey != ESC) {
				_playerKey = prevKey;
			}
		}

		if (_playerKey == ESC) continue;

		MoveAndPrintCreature(_pacman, _stepsFile);

		if (isPacmanHitGhost(_pacman.getPosition())) {
			if (_saveToFile) {
				_resultFile << _totalCounterMoves << ",";
			}
			return GAME_OVER;
		}

		if (_saveToFile) {
			_stepsFile << ',' << _numOfGhosts;
		}

		if (printCreatureFlag) {

			if (printGhostsAndCheckifGhostHitPacman(type, counterGhostsMoves, _stepsFile)) {
				if (_saveToFile) {
					_resultFile << _totalCounterMoves << ",";
				}
				return GAME_OVER;
			}

			if (isGhostsAteFruit()) {
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				_fruit.resetFruit();
			}


			if (counterGhostsMoves == 25)
				counterGhostsMoves = 0;
			else counterGhostsMoves++;

			if (fruitFlag) {
				if (!(_fruit.getVal() == 0)) {
					MoveAndPrintCreature(_fruit, _stepsFile);
				}
			}
			printCreatureFlag = 0;
		}

		else {
			printCreatureFlag = 1;
			if (_saveToFile) {
				for (int i = 0; i < _numOfGhosts; i++) {
					_stepsFile << ',' << 'S';
				}
				if (fruitFlag) {
					_stepsFile << ',' << 'S';
				}
			}
		}



		if (fruitCounterMoves == random) {
			if (!fruitFlag) {
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				_fruit.setFruit(_board, getLegend());

				_fruit.print(_isWithColor, _board.getDistantceFromStart());

				if (_saveToFile) {
					_stepsFile << ',' << 'F' << ',' << _fruit.getX() << ',' << _fruit.getY() << ',' << _fruit.getVal();
				}

				fruitFlag = true;
				fruitCounterMoves = 0;
			}
			else {
				fruitFlag = false;
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
				fruitCounterMoves = 0;
				_fruit.resetFruit();
				_stepsFile << ',' << 'F' << ',' << 0 << ',' << 0 << ',' << 0;
			}
		}

		if (isPacmanAteFood()) {
			_board.setSqrType(_pacman.getY(), _pacman.getX(), SqrType::EMPTY);
			setPoints();
		}


		if (isTunnel()) {
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
			_stepsFile << ',' << 'F' << ',' << 0 << ',' << 0 << ',' << 0;
		}


		for (int i = 0; i < _numOfGhosts; ++i) {
			if (isGhostAteFruit(_fruit, _ghosts[i])) {
				_board.getSquare(_fruit.getY(), _fruit.getX()).print(isWithColor, _board.getDistantceFromStart());
			}
		}

		fruitCounterMoves++;
		_totalCounterMoves++;

		if (_saveToFile)
			_stepsFile << endl;
	}

	if (_saveToFile) {
		_resultFile << endl << _allPoints << "," << _health;
		_resultFile << endl << _totalCounterMoves;
	}

	return CONTINUE_TO_NEXT_GAME;
}

int Game::loadGame(bool isWithColor, bool isSilentMode, bool& isfinished, string fileName) {

	int maxPoints = 0, result, smartMoveDirection, iterationCounter, counterGhosts;
	ifstream _stepsFile, _resultFile;
	string line, deaths, death, winLine, extraDeath, pointsLine, healthLine;
	char* linecopy;
	Square pacmanStart;

	string fileNameWithoutExtension = fileName.substr(0, fileName.find("."));
	_stepsFile.open(fileNameWithoutExtension + ".steps");
	_resultFile.open(fileNameWithoutExtension + ".result");

	setIsSilentMode(isSilentMode);
	setWithColor(isWithColor);

	result = _board.initBoard(_ghosts, _numOfGhosts, pacmanStart, _legend, fileName, maxPoints);
	if (result != 1) {
		return result;
	}
	setMaxPoints(maxPoints);

	goToXY(0, _board.getDistantceFromStart());

	_pacman = pacmanStart;
	_board.printBoard(isWithColor, _isSilentMode);
	_pacman.print(_isWithColor, _board.getDistantceFromStart(), _isSilentMode);
	printGhosts(isWithColor);
	printBanner();

	getline(_resultFile, deaths, '\n');
	_resultFile.seekg(0);
	
	while (getline(_stepsFile, line, '\n')) {
		char* pch, * fruitX, * fruitY, * fruitVal;

		if (!_isSilentMode) {
			Sleep(SPEED);
		}

		iterationCounter = 0;
		counterGhosts = 0;
		linecopy = new char[line.size()];
		strcpy(linecopy, line.c_str());
		pch = strtok(linecopy, ",");
		while (pch != NULL)
		{
			if (iterationCounter == 1) //pacman 
			{
				MoveAndPrintLoadedCreature(_pacman, *pch);
				if (isPacmanHitGhostLoaded(_pacman.getPosition())) {

					getline(_resultFile, death, ',');
					if (atoi(death.c_str()) != _totalCounterMoves || deaths == "") {
						isfinished = true;
						return TEST_FAILED;
					}
					if (getHealth() == 0)
						goto finish;

					resetGameAfterGhostHit();
				}
			}
			if (iterationCounter >= 3 && iterationCounter < _numOfGhosts + 3) //ghosts 
			{
				MoveAndPrintLoadedCreature(_ghosts[counterGhosts], *pch);

				if (isGhostHitPacman(_ghosts[counterGhosts].getPosition())) {

					getline(_resultFile, death, ',');
					if (atoi(death.c_str()) != _totalCounterMoves || deaths == "") {
						isfinished = true;
						return TEST_FAILED;
					}

					setHealth();
					if (getHealth() == 0)
						goto finish;

					resetGameAfterGhostHit();
				}
				counterGhosts++;
			}

			if (iterationCounter >= _numOfGhosts + 3) //fruit 
			{
				if (*pch == 'F') {
					fruitX = strtok(NULL, ",");
					fruitY = strtok(NULL, ",");
					fruitVal = strtok(NULL, ",");
					if (*fruitX == '0' && *fruitY == '0') {
						_board.getSquare(_fruit.getY(), _fruit.getX())
							.print(_isWithColor, _board.getDistantceFromStart(), _isSilentMode);
						_fruit.resetFruit();
					}
					else {
						_fruit.setFruit(atoi(fruitX), atoi(fruitY), atoi(fruitVal));
						_fruit.print(isWithColor, _board.getDistantceFromStart(), _isSilentMode);
					}
					iterationCounter = iterationCounter + 2;
				}
				else
					MoveAndPrintLoadedCreature(_fruit, *pch);
			}
			pch = strtok(NULL, ",");
			iterationCounter++;
		}

		if (isTunnel()) {
			deletePacmanLastMove();
			movePacmanThruTunnel();
			if (isPacmanAteFood())
				setPoints();
		}
		if (isPacmanAteFood()) {
			_board.setSqrType(_pacman.getY(), _pacman.getX(), SqrType::EMPTY);
			setPoints();
		}
		_totalCounterMoves += 1;
	}

	finish:

	getline(_resultFile, extraDeath, '\n');
	if (_isSilentMode && extraDeath != "") {
		isfinished = true;
		return TEST_FAILED;
	}
	_resultFile.seekg(0);

	getline(_resultFile, line, '\n');
	getline(_resultFile, pointsLine, ',');
	getline(_resultFile, healthLine, '\n');
	getline(_resultFile, winLine, '\n');


	if (winLine == "") {
		isfinished = true;
		if (atoi(death.c_str()) != _totalCounterMoves || deaths == "") 
			return TEST_FAILED;
		if (_isSilentMode) 
			return TEST_PASSED;
		return GAME_OVER;
	}
	else {
		if (atoi(winLine.c_str()) != _totalCounterMoves || atoi(healthLine.c_str()) != _health || atoi(pointsLine.c_str()) != _allPoints) {
			isfinished = true;
			if (_isSilentMode) 
				return TEST_FAILED;
		}
		if (_isSilentMode)
			return TEST_PASSED;
		return CONTINUE_TO_NEXT_GAME;
	}
}

bool Game::isGhostsAteFruit() {
	Square fruitSqr = _fruit.getPosition();
	Square ghostSqr;
	for (int i = 0; i < _numOfGhosts; i++) {
		ghostSqr = _ghosts[i].getPosition();
		if (fruitSqr.getX() == ghostSqr.getX() && fruitSqr.getY() == ghostSqr.getY())
			return true;
	}
	return false;
}

bool Game::printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves, ofstream& _stepsFile) {
	switch (int(type)) {
	case 0:
		for (int i = 0; i < _numOfGhosts; i++) {
			_ghosts[i].SmartMove(_pacman, _board.getArrSquare(), _board.getHeight(), _board.getWidth());
			MoveAndPrintCreature(_ghosts[i], _stepsFile);
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
				MoveAndPrintCreature(_ghosts[i], _stepsFile);
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
					MoveAndPrintCreature(_ghosts[i], _stepsFile);
					if (isGhostHitPacman(_ghosts[i].getPosition())) {
						setHealth();
						if (getHealth() == 0) {
							return true;
						}
						resetGameAfterGhostHit();
					}
				}
				else {
					MoveAndPrintCreature(_ghosts[i], _stepsFile);
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
			MoveAndPrintCreature(_ghosts[i], _stepsFile);
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
	if (!_isSilentMode) {
		for (int i = 0; i < _numOfGhosts; i++) {
			_ghosts[i].print(isWithColor, _board.getDistantceFromStart());
		}
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

const bool Game::isTunnel() {
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
		_ghosts[i].changePosition(_ghosts[i].getStartY(), _ghosts[i].getStartX()); 
	}
	if (_saveToFile) {
		_resultFile << _totalCounterMoves << ",";
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

	if (_saveToFile) {
		_resultFile.close();
		_stepsFile.close();
	}

	_board.resetBoard();
	_points = 0;
	_maxPoints = 0;
	_numOfGhosts = 0;
	_totalCounterMoves = 1;
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

const bool Game::isPacmanHitGhostLoaded(const Square& position) {
	for (int i = 0; i < _numOfGhosts; i++) {
		if ((position.getX() == _ghosts[i].getX() && position.getY() == _ghosts[i].getY())) {
			setHealth();
			return true;
		}
	}
	return false;
}

void Game::MoveAndPrintCreature(Creature& creature, ofstream& _stepsFile) {
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

		_stepsFile << ',' << intToDir(creature.getDirection());
	}
	else {
		boardPositionOfGhost.setSqrType(SqrType::EMPTY);
		boardPositionOfGhost.print(_isWithColor, _board.getDistantceFromStart());
		if (isCreatureHitWall(creature)) {
			creature.oneMoveBack(_playerKey);
			if (_saveToFile) {
				_stepsFile << ',' << 'S';
			}
		}
		else if (_saveToFile) {
			char temp = playerKeyToDir(_playerKey);
			_stepsFile << ',' << temp;
		}
	}
	creature.print(_isWithColor, _board.getDistantceFromStart());
	if (typeid(creature) == typeid(_fruit)) {
		_fruit.print(_isWithColor, _board.getDistantceFromStart());
	}
}

void Game::MoveAndPrintLoadedCreature(Creature& creature, char dir) {
	Square boardPositionOfCreature = _board.getSquare(creature.getY(), creature.getX());

	deleteCreatureLastMove(creature);

	boardPositionOfCreature.print(_isWithColor, _board.getDistantceFromStart(), _isSilentMode);

	if (typeid(creature) != typeid(_pacman)) {
		creature.setDirection(int(charToDir(dir)));
		creature.Move(' ');
	}
	else {
		boardPositionOfCreature.setSqrType(SqrType::EMPTY);
		boardPositionOfCreature.print(_isWithColor, _board.getDistantceFromStart(), _isSilentMode);
		creature.Move(char(charToPlayerKey(dir)));
	}
	if (typeid(creature) == typeid(_fruit)) {
		_fruit.print(_isWithColor, _board.getDistantceFromStart(), _isSilentMode);
	}
	else {
		creature.print(_isWithColor, _board.getDistantceFromStart(), _isSilentMode);
	}

}

void Game::deleteGhostLastMove(Ghost& ghost) {
	goToXY(ghost.getX(), ghost.getY() + _board.getDistantceFromStart());
	_board.getSquare(ghost.getY(), ghost.getX()).print(_isWithColor, _board.getDistantceFromStart());
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