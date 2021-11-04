#include "square.h"



void goToXY(int x, int y);

void Square::print() {

    switch (_sqrType) {
    case 0: {
        goToXY(_x, _y);
        cout << " ";
        break;
    }
    case 1: {
        goToXY(_x, _y);
        cout << "*";
        break;
    }
    case 2: {
        goToXY(_x, _y);
        cout << "@";
        break;
    }
    case 3: {
        goToXY(_x, _y);
        cout << "O";
        break;
    }
    case 4: {
        goToXY(_x, _y);
        cout << "@";
        break;
    }
    }
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