#pragma once

#include "square.h"

const int TABLE_SIZE = 10;

class Board {
private:
    int _length;
    Square _squares[21][77];
public:
    // void getLength();
    Square getSquare(int x, int y);
    void printBoard();
    void initBoard();
};

