#pragma once

#include "square.h"

const int TABLE_SIZE = 10;

class Board {
private:
    int _length;
public:
    Square squares[21][77];
    // void getLength();
    // void getSquares();
    void printBoard();
    void initBoard();
};

