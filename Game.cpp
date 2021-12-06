#include "Game.h"
#include "square.h"
#include "board.h"
#include <cctype>



void Game::printBanner()const {
	goToXY(0,getHeight() + 2);
	clearConsoleRow();
	if(_isWithColor) changeColor(10);
	cout << "[ Life: " << getHealth() << " | Score: " << getPoints() << " ]";
	goToXY(_pacman.getX(), _pacman.getY());
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

void Game::startGame(bool isWithColor) {
	char prevKey = RIGHT;

	setWithColor(isWithColor);
	setMaxPoints(_board.initBoard(&_numOfGhosts));
	_board.printBoard(isWithColor);
	_pacman.print(isWithColor);
	createGhosts();
	int counterGhostsMoves = 0;
	bool printGhostFlag = 1;
	for (int i = 0; i < _numOfGhosts; i++) { _ghosts[i].print(isWithColor); }
	while (_health != 0 && _points != _maxPoints){
		prevKey = _playerKey;
		Sleep(SPEED);

		if (_kbhit()) { // if any key was hit
			_playerKey = tolower(getKey());  // change direction
			if (_playerKey != LEFT && _playerKey != UP && _playerKey != DOWN && _playerKey != RIGHT && _playerKey != STAY && _playerKey != ESC) {
				_playerKey = prevKey;
			}
		}
		if (_playerKey == ESC) continue;

		switch (_playerKey){
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
		_pacman.print(isWithColor);
		if (printGhostFlag){
			for (int i = 0; i < _numOfGhosts; i++) {
				if (isPacmanHitGhost(_pacman.getPosition(), _ghosts[i])) {
					setHealth();
					if (getHealth() == 0) {
						gameOver(false);
						return;
					}
					resetGameAfterGhostHit();
				}
				if (counterGhostsMoves == 20) {
						counterGhostsMoves = 0;
					}
				else {
						counterGhostsMoves++;
					}
				_ghosts[i].SmartMove(getPacman(), getBoard());
				MoveAndPrintGhost(_ghosts[i]);
				if (isGhostHitPacman(_ghosts[i].getPosition())) {
						setHealth();
						if (getHealth() == 0) {
							gameOver(false);
							return;
						}
						resetGameAfterGhostHit();
					}
					printGhostFlag = 0;
				}
			}
		else {
			printGhostFlag = 1;
		}
		if (isPacmanAteFood()) {
			_board.setSqrType(_pacman.getY(), _pacman.getX(), SqrType::EMPTY);
			setPoints();
		}

		if (isTunnel(_pacman)) {
			deletePacmanLastMove();
			movePacmanThruTunnel(_pacman);
			if (isPacmanAteFood()) setPoints();
		}

	}
	gameOver(true);

}

void Game::movePacmanThruTunnel(Pacman& pacman) {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	if (xPos == 0) _pacman.setX(getWidth()-1);
	else if (xPos == getWidth()-1) _pacman.setX(0);
	else if (yPos == 0) _pacman.setY(getHeight()-1);
	else if (yPos == getHeight()-1) _pacman.setY(0);
}

const bool Game::isTunnel(Pacman& pacman) const {
	const int xPos = pacman.getPosition().getX();
	const int yPos = pacman.getPosition().getY();
	if (xPos == 0 || xPos == getWidth()-1 || yPos == 0 || yPos == getHeight()-1)
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
	goToXY(_pacman.getX(), _pacman.getY());
	cout << " ";
}

void Game::deleteGhostLastMove(Ghost& ghost) {
	goToXY(ghost.getX(), ghost.getY());
	cout << " ";
}

const bool Game::isNextMoveIsAWall(const int x, const int y,  Board b) const {
	Square pos = b.getSquare(y, x);
	return pos.getSqrType() == SqrType::WALL;
}

const bool Game::isGhostHitWall(Square position) const
{
	const int xPos = position.getX();
	const int yPos = position.getY();
	const SqrType sqrType = _board.getSquare(yPos, xPos).getSqrType();
	if (sqrType == SqrType::WALL)
		return true;
	return false;
}

const bool Game::isGhostHitPacman(Square position) 
{
	if (position.getX() == _pacman.getX() && position.getY() == _pacman.getY()) {
		return true;
	}
	return false;
}

void Game::gameOver(const bool isWon) {
	clear(); // clears the console;
	char ch;
	if(isWon)
		cout << "You WON!!" << endl;
	else
		cout << "GAME OVER" << endl;
	cout << "press any key to return to the menu..." << endl;
	cin >> ch;
}

void Game::clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

int Game::getKey()const
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}

void Game::MoveAndPrintGhost(Ghost& ghost) {
	Square boardPositionOfGhost = _board.getSquare(ghost.getY(), ghost.getX());
	deleteGhostLastMove(ghost);
	boardPositionOfGhost.print(_isWithColor);
	
	ghost.Move();
	while (isGhostHitWall(ghost.getPosition())) {
		ghost.oneMoveBack();
		ghost.changeDirection();
		ghost.Move();
	}
	ghost.print(_isWithColor);
}

const bool Game::isPacmanHitGhost(Square position,  Ghost& ghost) const {
	if (position.getX() == ghost.getX() && position.getY() == ghost.getY())
		return true;
	 return false;
 }

void Game::resetGameAfterGhostHit() {
	_pacman.startPosition();
	for (int i = 0; i < _numOfGhosts; i++) {
		deleteGhostLastMove(_ghosts[i]);
		_ghosts[i].changePosition(_ghosts[i].getStartY(), _ghosts[i].getStartX()); // TODO: CHNAGE INIT VALUE MAKE START POSITION
	}
}

void Game::setPoints() { 
	_points = getPoints() + 1; 
	printBanner();
};

void Game::setHealth() { 
	_health = getHealth() - 1;
	printBanner();
};

void Game::printMenu()const {
	cout << endl << " (1) Start a new game without colors" << endl << " (2) Start a new game with colors" << endl
		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
}

void Game::printInstructions()const {
	cout << endl << "The instructions are: " << endl;
	cout << "  Press W to move up" << endl;
	cout << "  Press D to move right" << endl;
	cout << "  Press A to move left" << endl;
	cout << "  Press X to move down" << endl;
	cout << "  Press S to stay in your place" << endl;
	cout << "  You have 4 tunnel each side of the board which you can teleport to other side! TRY THEM" << endl;
	cout << "  Your goal is to eat all the breadcrumbs without being eaten by the ghosts!" << endl;
	cout << "  You have 3 life to achieve that, each time you get eaten by a ghost ur life will be reduce by 1" << endl;
	cout << "  The amount of lifes left will be indicated under the game board, when you reach 0 you lose" << endl;
	cout << "  Have FUN" << endl << endl;
}

void Game::createGhosts(){
	Square* arr = new Square[_numOfGhosts];
	_board.getGhosts(arr);
	for (int i = 0; i < _numOfGhosts; i++) {
		if (i % 2 == 0) {
			Ghost g1((int)DIRECTIONS::RIGHT, getHeight(), getWidth(), arr[i].getX(), arr[i].getY());
			_ghosts[i] = g1;
		}
		else {
			Ghost g2((int)DIRECTIONS::LEFT, getHeight(), getWidth(), arr[i].getX(), arr[i].getY());
			_ghosts[i] = g2;
		}
	}
}


