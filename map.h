#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "square.h"

const static std::string FILENAME = "mapa6.txt";
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int convertType(const char type);

class Map {
private:
	int _height;
	int _width;

public:
	char** readMapFromFile(int& foodCounter,int& ghostCounter, Square& pacmanStart);
	Square** initArr();
	const int getHeight() const { return _height; }
	const int getWidth() const { return _width; }
	int getFirstRowSize();
	void checkBoardSize();
	int getColSize();

	string* getFromFile();
};
