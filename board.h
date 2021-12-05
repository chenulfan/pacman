#pragma once

#include "square.h"

class Board {
private:
    int _length;
    Square _squares[19][70];
public:
    const Square getSquare(const int y, const int x) const { return _squares[y][x]; };
    void printBoard(const bool isWithColor);
    int initBoard();
    void setTunnels();
    void setSqrType(const int y, const int x, const SqrType sqr) { _squares[y][x].setSqrType(sqr); }
};

