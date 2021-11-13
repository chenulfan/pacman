#pragma once

#include "square.h"

class Board {
private:
    int _length;
    Square _squares[19][70];
public:
    Square getSquare(int x, int y);
    void printBoard(bool isWithColor);
    int initBoard();
    void setTunnels();
    void setSqrType(int y, int x, eSqrType sqr) { _squares[y][x].setSqrType(sqr); }
};

