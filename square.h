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
        int getX() { return _x; };
        int getY() { return _y; };
        int getSqrType() { return _sqrType; };
        void setX(int x) { _x = x; };
        void setY(int y) { _y = y; };
        void setSqrType(int sqrType) { _sqrType = (eSqrType)sqrType; };
        void setSquare(int x, int y, int sqrType);
        void setSquare(Square b);
        void print(bool isWithColor);

    private:
        eSqrType _sqrType;
        int _x, _y;

};