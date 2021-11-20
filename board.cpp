
#include "board.h"
#include "map.h"


bool isWall(const int* arr,const int j);
const int convertType(char type);

void Board::printBoard(const bool isWithColor) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            _squares[i][j].print(isWithColor);
        }
    }
}

int Board::initBoard() {
    int foodCounter = 0;
    int type;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            type = convertType(map[i][j]);
            if (type == Square::FOOD)
                ++foodCounter;
            _squares[i][j].setSquare(j, i, type );
        }
    }
    return foodCounter;
}

const int convertType(const char type) {
    if (type == ' ') return 0;
    if (type == '&') return 1;
    if (type == '#') return 2;
    if (type == '@') return 3;
    if (type == '$') return 4;
}


bool isWall(const int* arr,const int j) {
    const int* p = arr;
    while (*p != -1) {
        if (j == *p)
            return true;
        p++;
    }
    return false;
}

Square Board::getSquare(const int x,const int y) {
    return _squares[x][y]; 
};
