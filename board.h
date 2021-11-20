#pragma once

#include "square.h"

class Board {
private:
    int _length;
    Square _squares[19][70];
public:
    Square getSquare(const int x, const int y);
    void printBoard(const bool isWithColor);
    int initBoard();
    void setTunnels();
    void setSqrType(const int y, const int x, const Square::eSqrType sqr) { _squares[y][x].setSqrType(sqr); }
};

