#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>


using namespace std;

enum eSqrType { EMPTY, FOOD, TUNNEL, WALL };

class Square {
    int _x, _y;
    eSqrType _sqrType;
public:
    void setX(int x) { _x = x; };
    void setY(int y) { _y = y; };
    void setSqrType(int sqrType) { _sqrType = (eSqrType)sqrType; };
    void setSquare(int x, int y, int sqrType);

    void print();
};