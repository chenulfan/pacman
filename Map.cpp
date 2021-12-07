#include "map.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std; 

const static std::string dafuq = "mapa2.txt";
using std::cout;
using std::cin;
using std::endl;

const int convertType(const char type);

Square** Map::readMapFromFile(int& foodCounter,int& ghostCounter, Square& pacmanStart) {
	std::ifstream file(dafuq);
	std::string str;
	_width = getFirstRowSize();
	_height = getColSize();
	int type;
	Square** a = nullptr;
	a = initArr();
	for (int i = 0; i < _height; i++) {
		getline(file, str);
		for (int j = 0; j < _width; j++) {
			type = convertType(str[j]);
			if ((SqrType)type == SqrType::FOOD){foodCounter++;}
			if ((SqrType)type == SqrType::GHOST){ghostCounter++;}
			if ((SqrType)type == SqrType::PACMAN) { 
				pacmanStart.setX(j); 
				pacmanStart.setY(i); 
				pacmanStart.setSqrType(SqrType::PACMAN); 
			}
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

int Map::getFirstRowSize() {
	std::ifstream file(dafuq);
	std::string str;
	std::getline(file, str);
	int firstRowSize = str.size();
	if (firstRowSize > 79) { firstRowSize = 79; }
	file.clear();
	file.seekg(0);
	return firstRowSize;
}

int Map::getColSize() {
	std::ifstream file(dafuq);
	std::string str;
	int colSize = 0;
	while (std::getline(file, str)) {
		colSize++;
	}
	if (colSize > 24) { colSize = 24; }
	file.clear();
	file.seekg(0);
	return colSize;
}

const int convertType(const char type) {
	if (type == '%') return 0;
	if (type == ' ') return 1;
	if (type == '#') return 2;
	if (type == '@') return 3;
	if (type == '$') return 4;
	if (type == '&') return 5;
}