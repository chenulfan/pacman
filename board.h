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
    void setTunnels();
    void setSqrType(int y, int x, eSqrType sqr) { _squares[y][x].setSqrType(sqr); }
};

