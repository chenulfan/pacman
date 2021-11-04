#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>


using namespace std;

enum eSqrType { EMPTY, FOOD, TUNNEL, WALL ,PACMAN};

class Square {
public:
    eSqrType _sqrType;
    int _x, _y;
    void setX(int x) { _x = x; };
    void setY(int y) { _y = y; };
    void setSqrType(int sqrType) { _sqrType = (eSqrType)sqrType; };
    void setSquare(int x, int y, int sqrType);
    void setSquare(Square b);

    void print();
};