
#include "board.h"


bool isWall(const int* arr,const int j);

void Board::printBoard(const bool isWithColor) {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
             _squares[i][j].print(isWithColor);
        }
    }
}

int Board::initBoard(int& amountOfGhosts,Square& pacmanStart) {
    int foodCounter = 0;
    int ghostCounter = 0;
    int type = 0;
    _squares = _screen.readMapFromFile(foodCounter,ghostCounter,pacmanStart);
    _height = _screen.getHeight();
    _width = _screen.getWidth();
    amountOfGhosts = ghostCounter;
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
void Board::updateActualGameBoardHeight() {
    int start, end, counter=0;
    bool firstRowWall = false;
    for (int i = 0; i < _height; i++) {
        counter = 0;
        for (int j = 0; j < _width; j++) {
            if (!firstRowWall) {
                if (_squares[i][j].getSqrType() == SqrType::WALL) {
                    start = i;
                    firstRowWall = true;
                    _distanceFromFirstRow = i;
                    break;
                }

            }
            else {
                if (_squares[i][j].getSqrType() == SqrType::WALL) {
                    counter++;
                }
            }
            
        }
        if (counter == 0) {
            end = i - 1;
        }
    }
    _height = start - end; 
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