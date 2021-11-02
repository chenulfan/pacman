#pragma once

#include "square.h"

const int TABLE_SIZE = 10;

class Board {
private:
    int _length;
    Square squares[21][39];
public:
    // void getLength();
    // void getSquares();
    void printBoard();
    void initBoard();
};

