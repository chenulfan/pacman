#include "map.h"



string* Map::getFromFile(string FILENAME) {
	ifstream f(FILENAME);
	string str;
	_height = getColSize(FILENAME);
	int index = 0;
	string* arrOfStr = new string[_height];

	while (getline(f, str)) {
		arrOfStr[index++] = str;
	}

	return arrOfStr;
}


//
//Square** Map::readMapFromFile(int& foodCounter,int& ghostCounter, Square& pacmanStart) {
//
//	int type;
//	Square** arr = nullptr;
//	ifstream file(dafuq);
//	string str;
//
//	_width = getFirstRowSize();
//	_height = getColSize();
//
//	arr = initArr();
//	
//	for (int i = 0; i < _height; i++) {
//		getline(file, str);
//		for (int j = 0; j < _width; j++) {
//			type = convertType(str[j]);
//			if ((SqrType)type == SqrType::FOOD){foodCounter++;}
//			if ((SqrType)type == SqrType::GHOST){ghostCounter++;}
//			if ((SqrType)type == SqrType::PACMAN) { 
//				pacmanStart.setX(j); 
//				pacmanStart.setY(i); 
//				pacmanStart.setSqrType(SqrType::PACMAN); 
//			}
//			arr[i][j].setSquare(j, i, (SqrType)type);
//		}
//	}
//	return arr;
//}

Square** Map::initArr() {
	Square** arr = new Square * [_height];
	for (int i = 0; i < _height ; ++i) {
		arr[i] = new Square[_width];
	}
	return arr;
}

int Map::getFirstRowSize(string FILENAME) {
	ifstream file(FILENAME);
	string str;
	getline(file, str);
	int firstRowSize = str.size();
	if (firstRowSize > 79) { firstRowSize = 79; }
	file.clear();
	file.seekg(0);
	return firstRowSize;
}

int Map::getColSize(string FILENAME) {
	ifstream file(FILENAME);
	string str;
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