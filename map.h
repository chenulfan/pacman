#pragma once

#include "square.h"
using std::ifstream;
class Map {
private:
	int _height;
	int _width;
	int _screenHeigh;
	int _screenWidth;
public:
	Square** readMapFromFile(int* foodCounter,int* ghostCounter);
	Square** initArr();
	void CheckBoardSize();
	const int getHeight() const { return _height; }
	const int getWidth() const { return _width; }
};