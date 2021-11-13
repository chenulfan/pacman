#include "square.h"

void Square::print(bool isWithColor) {
    switch (_sqrType) {
        case 0: {
            goToXY(_x, _y);
            cout << " ";
            break;
        }
        case 1: {
            goToXY(_x, _y);
            if(isWithColor)
                changeColor(9);
            cout << char(250);
            break;
        }
        case 2: {
            goToXY(_x, _y);
            if (isWithColor)
                changeColor(5);
            cout << char(219);
            break;
        }
        case 3: {
            goToXY(_x, _y);
            if (isWithColor)
                changeColor(6);
            cout << "@";
            break;
        }
        case 4: {
            goToXY(_x, _y);
            if (isWithColor)
                changeColor(12);
            cout << "$";
            break;
        }
    }
}

void changeColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Square::setSquare(int x, int y, int sqrType) {
    this->setX(x);
    this->setY(y);
    this->setSqrType(sqrType);
}
void Square::setSquare(Square sqr) {
    this->setX(sqr._x);
    this->setY(sqr._y);
    this->setSqrType(sqr._sqrType);
}

void goToXY(int x, int y)
{
    static HANDLE hConsoleOutput = NULL;
    if (NULL == hConsoleOutput)
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwCursorPosition = { x, y };
    cout.flush();
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}