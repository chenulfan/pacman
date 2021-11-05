#pragma once
#include "board.h"
#include "pacman.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#define UP1 119 // Up Arrow 
#define UP2 87 // Up Arrow 
#define DOWN1 120 // Down Arrow 
#define DOWN2 88 // Down Arrow 
#define LEFT1 97  // Left Arrow 
#define LEFT2 65  // Left Arrow 
#define RIGHT1 100 // Right Arrow 
#define RIGHT2 68  // Right Arrow 
#define ESC 27  // Escape Key
#define SPEED 400

class Game {
private:
	Board _board;
    char _playerKey;
	PacMan _pacMan;


public:
	int getKey();
	void startGame();
	bool hitWall(Square position);
	void gameOver();
	void clear();
};

