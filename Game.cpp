#include "Game.h"
#include "square.h"
#include "board.h"
#include <cctype>

const int COL_SIZE = 19;
const int ROW_SIZE = 70;
const int MAX_POINTS = 100;

void Game::changeColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


void Game::printBanner() {
	goToXY(0,COL_SIZE + 2);
	clearConsoleRow();
	changeColor(10);
	cout << "[ life: " << getHealth() << " | points: " << getPoints() << " ]";
	changeColor(12);

	goToXY(_pacman.getX(), _pacman.getY());
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

void Game::startGame() {

    Ghost ghost1(0,34, 9), ghost2(2,34, 11);
	char prevKey = RIGHT;
	_board.initBoard();
	_board.printBoard();
	printBanner();
	ghost1.print();
	ghost2.print();
	_pacman.print();
	int counterGhostsMoves = 0;
	bool printGhostFlag = 1;
	
	while (_health != 0 || _points != MAX_POINTS){
		prevKey = _playerKey;
		Sleep(SPEED);

		if (_kbhit()) { // if any key was hit
			_playerKey = getKey();  // change direction
			if (_playerKey != LEFT && _playerKey != UP && _playerKey != DOWN && _playerKey != RIGHT && _playerKey != STAY && _playerKey != ESC) {
				_playerKey = prevKey;
			}
		}
		if (_playerKey == ESC) continue;

		switch (tolower(_playerKey)){
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
		_pacman.print(); 

		if (isPacmanHitGhost(_pacman.getPosition(), ghost1, ghost2)) {
			setHealth();
			if (getHealth() == 0) {
				gameOver();
				return;
			}
			resetGameAfterGhostHit(ghost1, ghost2);
		}
		if (isTunnel(_pacman)) {
			deletePacmanLastMove();
			movePacmanThruTunnel(_pacman);
		}
		if (isPacmanAteFood()) {
			_board.setSqrType(_pacman.getY(), _pacman.getX(), EMPTY);
			setPoints();
		}
		if (printGhostFlag) {
			if (counterGhostsMoves == 20) {
				ghost1.changeDirection();
				ghost2.changeDirection();
				counterGhostsMoves = 0;
			}
			else {
				counterGhostsMoves++;
			}
			MoveAndPrintGhost(ghost1);
			MoveAndPrintGhost(ghost2);
			printGhostFlag = 0;
		}
		else
			printGhostFlag = 1;   
	}

}

void Game::movePacmanThruTunnel(Pacman& pacman) {
	int xPos = _pacman.getPosition().getX();
	int yPos = _pacman.getPosition().getY();
	if (xPos == 0) _pacman.setX(ROW_SIZE);
	else if (xPos == ROW_SIZE) _pacman.setX(0);
	else if (yPos == 0) _pacman.setY(COL_SIZE);
	else if (yPos == COL_SIZE) _pacman.setY(0);
	
}

bool Game::isTunnel(Pacman& pacman) {
	int xPos = pacman.getPosition().getX();
	int yPos = pacman.getPosition().getY();
	if (xPos == 0 || xPos == ROW_SIZE || yPos == 0 || yPos == COL_SIZE)
		return true;
	return false;
}

bool Game::isPacmanAteFood() {
	int xPos = _pacman.getPosition().getX();
	int yPos = _pacman.getPosition().getY();
	int sqrType = _board.getSquare(yPos, xPos).getSqrType();
	return sqrType == FOOD;
}

void Game::deletePacmanLastMove() {
	_board.setSqrType(_pacman.getY(), _pacman.getX(), EMPTY);
	goToXY(_pacman.getX(), _pacman.getY());
	cout << " ";
}

void Game::deleteGhostLastMove(Ghost& ghost) {
	goToXY(ghost.getX(), ghost.getY());
	cout << " ";
}

bool isNextMoveIsAWall(int x, int y,  Board b) {
	Square pos = b.getSquare(y, x);
	return pos.getSqrType() == WALL;
}

bool Game::isGhostHitWall( Square position) //return true if pacman's new position is a wall
{
	int xPos = position.getX();
	int yPos = position.getY();
	int sqrType = _board.getSquare(yPos, xPos).getSqrType();
	if (sqrType == WALL)
		return true;
	return false;
}

void Game::gameOver() {
	clear(); // clears the console;
	cout << "GAME OVER LOSER";
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

int Game::getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}

void Game::MoveAndPrintGhost(Ghost& ghost) {
	Square boardPositionOfGhost = _board.getSquare(ghost.getY(), ghost.getX());
	deleteGhostLastMove(ghost);
	boardPositionOfGhost.print();
	

	ghost.Move();
	while (isGhostHitWall(ghost.getPosition())) {
		ghost.oneMoveBack();
		ghost.changeDirection();
		ghost.Move();
	}
	ghost.print();
}

bool Game::isPacmanHitGhost(Square position, Ghost& ghost1, Ghost& ghost2) {
	 if (position.getX() == ghost1.getX() && position.getY() == ghost1.getY())
		 return true;
	 if (position.getX() == ghost2.getX() && position.getY() == ghost2.getY())
		 return true;
	 return false;
 }

void Game::resetGameAfterGhostHit(Ghost& ghost1, Ghost& ghost2) {
	_pacman.startPosition();
	deleteGhostLastMove(ghost1);
	deleteGhostLastMove(ghost2);
	ghost1.changePosition(9, 34);
	ghost2.changePosition(11, 34);
}

void Game::setPoints() { 
	_points = getPoints() + 1; 
	printBanner();
};

void Game::setHealth() { 
	_health = getHealth() - 1;
	printBanner();
};

void Game::printMenu() {
	cout << endl << " (1) Start a new game" << endl
		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
}

void Game::printInstructions() {
	cout << "The instructions are: " << endl << endl;
}

