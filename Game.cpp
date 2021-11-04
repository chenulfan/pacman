#include "Game.h"
#include "square.h"
#include "board.h"

void Game::startGame() {
	_board.initBoard();
	_board.printBoard();
	_pacMan.print();
	Square _blank;
	_blank.setSquare(_pacMan._x, _pacMan._y, 0); //square to delete the trace of pacman
	while (_playerKey != ESC)
	{
	
		// sleeps for half a second before continuing to the next command
		Sleep(600);

		// only if a key was hit we read what key code it was
		if (_kbhit()) // if any key was hit
			_playerKey = getKey();  // change direction
		// make a move in current direction if no change
		_blank.print(); // deletes trace
		switch (_playerKey)
		{
			// each case update pacman and blank to the new position according to the key pressed
		case RIGHT:
			_pacMan.setX((_pacMan._x)+1);
			_blank.setX((_blank._x) + 1);
			break;
		case DOWN:
			_pacMan.setY((_pacMan._y) + 1);
			_blank.setY((_blank._y) + 1);

			break;
		case LEFT:
			_pacMan.setX((_pacMan._x) - 1);
			_blank.setX((_blank._x) - 1);
			break;
		case UP:
			_pacMan.setY((_pacMan._y) - 1);
			_blank.setY((_blank._y) - 1);
			break;
		}
		if (hitWall(_pacMan._position)) //checks if the new move hit a wall
		{
			gameOver();
			break;
		}
		_pacMan.print(); //new print
		
		}

	}


bool Game::hitWall(Square position) //return true if pacman's new position is a wall
{
	if (_board.squares[position._y][position._x]._sqrType == WALL){
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