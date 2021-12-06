#include "map.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;


using std::cout;
using std::cin;
using std::endl;

const int convertType(const char type);
Square** Map::readMapFromFile(int* foodCounter,int* ghostCounter) {
	int type;
	Square** a = nullptr;
	std::ifstream file("mapa.txt");
	std::string str;
	CheckBoardSize();
	a = initArr();
	for (int i = 0; i < _height; i++) {
		std::getline(file, str);
		for (int j = 0; j < _width; j++) {
			type = convertType(str[j]);
			if ((SqrType)type == SqrType::FOOD){*foodCounter = *foodCounter + 1;}
			if ((SqrType)type == SqrType::GHOST){*ghostCounter = *ghostCounter + 1;}
			a[i][j].setSquare(j, i, (SqrType)type);
		}
	}
	return a;
}
Square** Map::initArr() {
	Square** arr = new Square * [_height];
	for (int i = 0; i < _height ; ++i) {
		arr[i] = new Square[_width];
	}
	return arr;
}
void Map::CheckBoardSize() {
	std::ifstream file("mapa.txt");
	std::string str;
	int lineSize, counterRows = 0, counterCol = 0;
	while (std::getline(file, str) && counterRows < 19) {
		if (counterRows == 0) {
			if (str.size() > 79) { counterCol = 79; }
			else { counterCol = str.size(); }
		}
		counterRows++;
	}
	_width = counterCol;
	_height = counterRows;
	file.clear();
	file.seekg(0);
}
const int convertType(const char type) {
	if (type == ' ') return 1;
	if (type == '%') return 0;
	if (type == '#') return 2;
	if (type == '@') return 3;
	if (type == '$') return 4;
	if (type == '&') return 4;
}