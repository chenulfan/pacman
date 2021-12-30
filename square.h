#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;

void goToXY(int x, int y);
void changeColor(int color);

enum class SqrType { EMPTY, FOOD, WALL, PACMAN, GHOST,LEGEND, FRUIT };

class Square {

    private:
        SqrType _sqrType;
        int _x;
        int _y;

    public:
        const int getX() const { return _x; };
        const int getY() const { return _y; };
        SqrType getSqrType()const { return _sqrType; };
        void setX(const int x) { _x = x; };
        void setY(const int y) { _y = y; };
        void setSqrType(const SqrType sqrType) { _sqrType = (SqrType)sqrType; } ;
        void setSquare(const int x, const int y, const SqrType sqrType);
        void setSquare(const Square& b);
        void print(const bool isWithColor, int distacneFromStart, bool isSilentMode = false)const;
        void printBanner(bool isWithColor, bool isSilentMode = false);

};

