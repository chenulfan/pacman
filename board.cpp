
#include "board.h"


bool isWall(const int* arr,const int j);


void Board::printBoard(const bool isWithColor) {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            _squares[i][j].print(isWithColor);
        }
    }
}

int Board::initBoard(int* amountOfGhosts) {
    int foodCounter = 0;
    int ghostCounter = 0;
    int type = 0;
    _squares = _screen.readMapFromFile(&foodCounter,&ghostCounter);
    _height = _screen.getHeight();
    _width = _screen.getWidth();
    *amountOfGhosts = ghostCounter;
    return foodCounter;
}
void Board::getGhosts(Square* ghosts) const {
    int counter = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_squares[i][j].getSqrType() == SqrType::GHOST) {
                ghosts[counter] = _squares[i][j];
                _squares[i][j].setSqrType(SqrType::EMPTY);
                counter++;
            }
        }
    }
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
