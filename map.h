#pragma once

#include "square.h"

#include <string>
#include <filesystem>
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
	Square** initArr();
	const int getHeight() const { return _height; }
	const int getWidth() const { return _width; }
	int getFirstRowSize(string FILENAME);
	int getColSize(string FILENAME);

	string* getFromFile(string FILENAME);
};
