#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <windows.h>
#include "square.h"
#include <locale>
#include <codecvt>
#include <string>
#include <algorithm>
#include <filesystem>
#include <limits.h>
#include <direct.h>

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
	int getFirstRowSize(string FILENAME);
	void checkBoardSize();
	int getColSize(string FILENAME);

	string* getFromFile(string FILENAME);
};
