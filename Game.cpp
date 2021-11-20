#include "Game.h"
#include "square.h"
#include "board.h"
#include <cctype>

const int COL_SIZE = 19;
const int ROW_SIZE = 70;


void Game::printBanner() {
	goToXY(0,COL_SIZE + 2);
	clearConsoleRow();
	if(_isWithColor) changeColor(10);
	cout << "[ Life: " << getHealth() << " | Score: " << getPoints() << " ]";
	goToXY(_pacman.getX(), _pacman.getY());
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

void Game::startGame(bool isWithColor) {

    Ghost ghost1(0,34, 9), ghost2(2,34, 11);
	char prevKey = RIGHT;

	setWithColor(isWithColor);
	
	setMaxPoints(_board.initBoard());
	_board.printBoard(isWithColor);
	printBanner();

	_pacman.print(isWithColor);
	ghost1.print(isWithColor);
	ghost2.print(isWithColor);

	int counterGhostsMoves = 0;
	bool printGhostFlag = 1;
	
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

		if (isPacmanHitGhost(_pacman.getPosition(), ghost1, ghost2)) {
			setHealth();
			if (getHealth() == 0) {	
				gameOver();
				return;
			}
			resetGameAfterGhostHit(ghost1, ghost2);
		}
		if (isPacmanAteFood()) {
			_board.setSqrType(_pacman.getY(), _pacman.getX(), Square::EMPTY);
			setPoints();
		}

		if (isTunnel(_pacman)) {
			deletePacmanLastMove();
			movePacmanThruTunnel(_pacman);
			if (isPacmanAteFood()) setPoints();
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
			if (isGhostHitPacman(ghost1.getPosition())) {
				setHealth();
				if (getHealth() == 0) {
					gameOver();
					return;
				}
				resetGameAfterGhostHit(ghost1, ghost2);
			}
			MoveAndPrintGhost(ghost2);
			if (isGhostHitPacman(ghost2.getPosition())) {
				setHealth();
				if (getHealth() == 0) {
					gameOver();
					return;
				}
				resetGameAfterGhostHit(ghost1, ghost2);
			}
			printGhostFlag = 0;
		}
		else
			printGhostFlag = 1;   
	}

}

void Game::movePacmanThruTunnel(Pacman& pacman) {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	if (xPos == 0) _pacman.setX(ROW_SIZE-1);
	else if (xPos == ROW_SIZE-1) _pacman.setX(0);
	else if (yPos == 0) _pacman.setY(COL_SIZE-1);
	else if (yPos == COL_SIZE-1) _pacman.setY(0);
}

const bool Game::isTunnel(Pacman& pacman) {
	const int xPos = pacman.getPosition().getX();
	const int yPos = pacman.getPosition().getY();
	if (xPos == 0 || xPos == ROW_SIZE-1 || yPos == 0 || yPos == COL_SIZE-1)
		return true;
	return false;
}

const bool Game::isPacmanAteFood() {
	const int xPos = _pacman.getPosition().getX();
	const int yPos = _pacman.getPosition().getY();
	const int sqrType = _board.getSquare(yPos, xPos).getSqrType();
	return sqrType == Square::FOOD;
}

void Game::deletePacmanLastMove() {
	_board.setSqrType(_pacman.getY(), _pacman.getX(), Square::EMPTY);
	goToXY(_pacman.getX(), _pacman.getY());
	cout << " ";
}

void Game::deleteGhostLastMove(Ghost& ghost) {
	goToXY(ghost.getX(), ghost.getY());
	cout << " ";
}

const bool Game::isNextMoveIsAWall(const int x, const int y,  Board b) {
	Square pos = b.getSquare(y, x);
	return pos.getSqrType() == Square::WALL;
}

const bool Game::isGhostHitWall(Square position) 
{
	const int xPos = position.getX();
	const int yPos = position.getY();
	const int sqrType = _board.getSquare(yPos, xPos).getSqrType();
	if (sqrType == Square::WALL)
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
	boardPositionOfGhost.print(_isWithColor);
	
	ghost.Move();
	while (isGhostHitWall(ghost.getPosition())) {
		ghost.oneMoveBack();
		ghost.changeDirection();
		ghost.Move();
	}
	ghost.print(_isWithColor);
}

const bool Game::isPacmanHitGhost(Square position,  Ghost& ghost1,  Ghost& ghost2) {
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
	cout << endl << " (1) Start a new game without colors" << endl << " (2) Start a new game with colors" << endl
		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
}

void Game::printInstructions() {
	cout << "The instructions are: " << endl;
	cout << "Press W to move up" << endl;
	cout << "Press D to move right" << endl;
	cout << "Press A to move left" << endl;
	cout << "Press X to move down" << endl;
	cout << "Press S to stay in your place" << endl;
	cout << "You have 4 tunnel each side of the board which you can teleport to other side! TRY THEM" << endl;
	cout << "Your goal is to eat all the breadcrumbs without being eaten by the ghosts!" << endl;
	cout << "You have 3 life to achieve that, each time you get eaten by a ghost ur life will be reduce by 1" << endl;
	cout << "The amount of lifes left will be indicated under the game board, when you reach 0 you lose" << endl;
	cout << "Have FUN" << endl;
}

