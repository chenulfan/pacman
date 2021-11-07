#include "Game.h"
#include "square.h"
#include "board.h"

void Game::printBanner() {
	goToXY(0,COL_SIZE + 2);
	clearConsoleRow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "[ life: " << getHealth() << " | points: " << getPoints() << " ]";
	SetConsoleTextAttribute(hConsole,12);
	goToXY(_pacman.getX(), _pacman.getY());
}

void clearConsoleRow() {
	printf("%c[2K", 27);
}

void Game::startGame() {
	Square _blank, currPosition;
  
  Ghost ghost1(0,40, 10), ghost2(2,36, 10);
	ghost1.print();
	ghost2.print();
	_board.initBoard();
	_board.printBoard();
	printBanner();
	_pacman.print();

	_blank.setSquare(_pacman.getX(), _pacman.getY(), 0); //square to delete the trace of pacman
	
	while (_playerKey != ESC){
		Sleep(SPEED);

		if (_kbhit()) // if any key was hit
			_playerKey = getKey();  // change direction
		_blank.print(); // deletes trace

		switch (_playerKey){
			case RIGHT1:
			case RIGHT2:
				if (!isNextMoveIsAWall(_pacman.getX() + 2, _pacman.getY(), _board)) {
					_pacman.setX(calcMoveX(_pacman.getX(), _pacman.getY(), 1));
					_blank.setX(calcMoveX(_blank.getX(), _blank.getY(), 1));
				}
				break;
			case LEFT1:
			case LEFT2:
				if (!isNextMoveIsAWall(_pacman.getX() - 2, _pacman.getY(), _board)) {
					_pacman.setX(calcMoveX(_pacman.getX(), _pacman.getY(), 0));
					_blank.setX(calcMoveX(_blank.getX(), _blank.getY(), 0));
				}
				break;
			case UP1:
			case UP2:
				if (!isNextMoveIsAWall(_pacman.getX(), _pacman.getY() - 1, _board)) {
					_pacman.setY(calcMoveY(_pacman.getX(), _pacman.getY(), 1));
					_blank.setY(calcMoveY(_blank.getX(), _blank.getY(), 1));
				}
				break;
			case DOWN1:
			case DOWN2:
				if (!isNextMoveIsAWall(_pacman.getX(), _pacman.getY() + 1, _board)) {
					_pacman.setY(calcMoveY(_pacman.getX(), _pacman.getY(), 0));
					_blank.setY(calcMoveY(_blank.getX(), _blank.getY(), 0));
				}
				break;
		}

		switch (whatPacmanMet(_pacman)) {
			case FOOD:
				setPoints();
				printBanner();
				break;
		}
    
    if (hitGhost(_pacman.getPosition(), ghost1,ghost2)){
				gameOver();
				break;
			}
			printGhosts(ghost1, ghost2);
			if (hitGhost(_pacman.getPosition(), ghost1, ghost2)) {
				gameOver();
				break;
			}
		_pacman.print(); //new print
	}
}


bool isNextMoveIsAWall(int x, int y,  Board b) {
	Square pos = b.getSquare(y, x);
	return pos.getSqrType() == WALL;
}

eSqrType Game::whatPacmanMet(Pacman pacman) {
	int xPos = pacman.getPosition().getX();
	int yPos = pacman.getPosition().getY();
	Square s = _board.getSquare(yPos, xPos);
	int sqrType = _board.getSquare(yPos, xPos).getSqrType();
	return (eSqrType)sqrType;
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



bool Game::hitWall( Square position) //return true if pacman's new position is a wall
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

 void Game::printGhosts(Ghost &ghost1,Ghost &ghost2) {
	 ghost1.trailDelete();
	 ghost2.trailDelete();
	 ghost1.Move();
	 while (hitWall(ghost1.getPosition())) {
		 ghost1.changeDir();
	 }
	 ghost1.print();
	 ghost2.Move();
	 while (hitWall(ghost2.getPosition())) {
		 ghost2.changeDir();
	 }
	 ghost2.print();
}
bool Game::hitGhost(Square position, Ghost& ghost1, Ghost& ghost2) {
	 if (position.getX() == ghost1.getX() && position.getY() == ghost1.getY()) {
		 return true;
	 }
	 if (position.getX() == ghost2.getX() && position.getY() == ghost2.getY()) {
		 return true;
	 }
	 return false;
 }

void Game::pacmanStay(Square& _blank) {
	//switch (_playerKey)
	//{
	//case RIGHT1:
	//case RIGHT2:
	//	_pacman.setX((_pacman.getX()) - 2);
	//	_blank.setX((_blank.getX()) - 2);
	//	break;
	//case LEFT1:
	//case LEFT2:
	//	_pacman.setX((_pacman.getX()) + 2);
	//	_blank.setX((_blank.getX()) + 2);
	//	break;
	//case UP1:
	//case UP2:
	//	_pacman.setY((_pacman.getY()) + 1);
	//	_blank.setY((_blank.getY()) + 1);
	//	break;
	//case DOWN1:
	//case DOWN2:
	//	_pacman.setY((_pacman.getY()) - 1);
	//	_blank.setY((_blank.getY()) - 1);
	//	break;
	//}
}

void Game::printMenu() {
	cout << endl << " (1) Start a new game" << endl
		<< " (8) Present instructions and keys" << endl << " (9) EXIT" << endl;
}

void Game::printInstructions() {
	cout << "The instructions are: " << endl;
}