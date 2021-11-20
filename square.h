#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>



using std::cout;
using std::cin;
using std::endl;


void goToXY(int x, int y);
void changeColor(int color);

class Square {

    public:
        enum eSqrType { EMPTY, FOOD, WALL, PACMAN, GHOST };
        const int getX() { return _x; };
        const int getY() { return _y; };
        const int getSqrType() { return _sqrType; };
        void setX(const int x) { _x = x; };
        void setY(const int y) { _y = y; };
        void setSqrType(const int sqrType) { _sqrType = (eSqrType)sqrType; };
        void setSquare(const int x, const int y, const int sqrType);
        void setSquare(const Square& b);
        void print(const bool isWithColor);

    private:
        eSqrType _sqrType;
        int _x, _y;

};