#pragma once
#include "board.h"
#include "GameObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#define UP 72  // Up Arrow 
#define DOWN 80 // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77  // Right Arrow 
#define ESC 27  // Escape Key
#define SPEED 400

class Game {
private:
	Board _board;
    char _playerKey;
	GameObject _pacMan;


public:
	int getKey();
	void startGame();
	bool hitWall(Square position);
	void gameOver();
	void clear();
};

