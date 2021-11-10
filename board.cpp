
#include "board.h"
#include "map.h"


bool isWall(const int* arr, int j);
int convertType(char type);

void Board::printBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            _squares[i][j].print();
        }
    }
}

void Board::initBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            _squares[i][j].setSquare(j, i, convertType(map[i][j]));
        }
    }
}

int convertType(char type) {
    if (type == ' ') return 0;
    if (type == '&') return 1;
    if (type == '#') return 2;
    if (type == '@') return 3;
    if (type == '$') return 4;
}


bool isWall(const int* arr, int j) {
    const int* p = arr;
    while (*p != -1) {
        if (j == *p)
            return true;
        p++;
    }
    return false;
}

Square Board::getSquare(int x, int y) { 
    return _squares[x][y]; 
};
