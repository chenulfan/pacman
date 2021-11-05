#include "Game.h"
#include "square.h"
#include "board.h"

#include "Ghost.h"

int calcMoveX(int x, int y, int direction);
int calcMoveY(int x, int y, int direction);

void Game::startGame() {
	Ghost ghost1(40, 10), ghost2(36, 10);
	_board.initBoard();
	_board.printBoard();
	_pacMan.print();
	Square _blank;
	_blank.setSquare(_pacMan.getX(), _pacMan.getY(), 0); //square to delete the trace of pacman
	while (_playerKey != ESC)
	{

		Sleep(SPEED);

		if (_kbhit()) // if any key was hit
			_playerKey = getKey();  // change direction
		_blank.print(); // deletes trace
		switch (_playerKey)
		{
		case RIGHT1:
		case RIGHT2:
			_pacMan.setX(calcMoveX(_pacMan.getX(), _pacMan.getY(), 1));
			_blank.setX(calcMoveX(_blank.getX(), _blank.getY(), 1));
			break;
		case LEFT1:
		case LEFT2:
			_pacMan.setX(calcMoveX(_pacMan.getX(), _pacMan.getY(), 0));
			_blank.setX(calcMoveX(_blank.getX(), _blank.getY(), 0));
			break;
		case UP1:
		case UP2:
			_pacMan.setY(calcMoveY(_pacMan.getX(), _pacMan.getY(), 1));
			_blank.setY(calcMoveY(_blank.getX(), _blank.getY(), 1));
			break;
		case DOWN1:
		case DOWN2:
			_pacMan.setY(calcMoveY(_pacMan.getX(), _pacMan.getY(), 0));
			_blank.setY(calcMoveY(_blank.getX(), _blank.getY(), 0));
			break;
		}
		if (hitWall(_pacMan.getPosition())) { //checks if the new move hit a wall
			gameOver();
			break;
		}
		printGhosts(ghost1, ghost2);
		_pacMan.print(); //new print
	}
}

// directon: 1 = RIGHT , 0 = LEFT
int calcMoveX(int x, int y, int direction) {
	if (x == 0 && y == COL_SIZE / 2)
		return ROW_SIZE - 2;
	else if (x == ROW_SIZE && y == COL_SIZE / 2)
		return 2;
	else if (direction == 1)
		return x + 2;
	return x - 2;
}

// directon: 1 = UP , 0 = DOWN
int calcMoveY(int x, int y, int direction) {
	if (x == ROW_SIZE / 2 && y == 0)
		return COL_SIZE - 1;
	else if (x == ROW_SIZE / 2 && y == COL_SIZE)
		return 1;
	else if (direction)
		return y - 1;
	return y + 1;
}



bool Game::hitWall(Square position) //return true if pacman's new position is a wall
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

 void Game::printGhosts(Ghost &ghost1, Ghost &ghost2) {
	 ghost1.trailDelete();
	 ghost2.trailDelete();
	 int dirGhost1 = ghost1.randomMove();
	 int dirGhost2 = ghost2.randomMove();
	 while (hitWall(ghost1.getPosition()))
	 {
		 ghost1.randomMove();
	 }
	 ghost1.print();
	 while (hitWall(ghost2.getPosition())) {
		 ghost2.randomMove();
	 }
	 ghost2.print();
}
