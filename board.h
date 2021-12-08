#pragma once

#include "map.h"
#include "ghost.h"

class Board {
private:
    int _length;
    Square** _squares;
    int _height;
    int _width;
    int _amountOfGhosts;
    int _distanceFromStart;
    Map _screen;
    //DESTRUCTOR FRO SQUARES

public:
    const int getHeight() const { return _height; }
    const int getWidth() const { return _width; }
    const Square getSquare(const int y, const int x) const { return _squares[y][x]; };
    void printBoard(const bool isWithColor);
    void setTunnels();
    void setSqrType(const int y, const int x, const SqrType sqr) { _squares[y][x].setSqrType(sqr); }
    void getGhosts(Square* ghosts) const;
    void printBanner(bool isWithColor)const;
    void updateActualGameBoardHeight(string* map, int len);
    void initBoardWidth(string firstRow) ;
    int initBoard(Ghost* ghosts, int& amountOfGhosts, Square& pacmanStart, Square& legend);
    void analyzeBoard(string* map, int len, Ghost* ghosts, int& amountOfGhosts, Square& pacmanStart, int& foodCounter);
    Square** initSquares();
    Square getLegendPos(string* map, int len);
};

