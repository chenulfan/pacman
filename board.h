#pragma once

#include "map.h"

class Board {
private:
    int _length;
    Square** _squares;
    int _height;
    int _width;
    int _amountOfGhosts;
    Map _screen;
    //DESTRUCTOR FRO SQUARES
public:
    const int getHeight() const { return _height; }
    const int getWidth() const { return _width; }
    const Square getSquare(const int y, const int x) const { return _squares[y][x]; };
    void printBoard(const bool isWithColor);
    int initBoard(int* amountOfGhosts);
    void setTunnels();
    void setSqrType(const int y, const int x, const SqrType sqr) { _squares[y][x].setSqrType(sqr); }
    void getGhosts(Square* ghosts) const;
};

