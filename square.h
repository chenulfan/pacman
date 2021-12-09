#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;


using std::cout;
using std::cin;
using std::endl;


void goToXY(int x, int y);
void changeColor(int color);

enum class SqrType { EMPTY, FOOD, WALL, PACMAN, GHOST,LEGEND };

class Square {

    private:
        SqrType _sqrType;
        int _x, _y;

    public:
        const int getX() const { return _x; };
        const int getY() const { return _y; };
        SqrType getSqrType()const { return _sqrType; };
        void setX(const int x) { _x = x; };
        void setY(const int y) { _y = y; };
        void setSqrType(const SqrType sqrType) { _sqrType = (SqrType)sqrType; } ;
        void setSquare(const int x, const int y, const SqrType sqrType);
        void setSquare(const Square& b);
        void print(const bool isWithColor, int distacneFromStart);
        void printBanner(bool isWithColor);

};

