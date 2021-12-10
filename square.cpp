#include "square.h"

void Square::print(const bool isWithColor, int distacneFromStart)const {
    switch (_sqrType) {
    case SqrType::EMPTY: {
            goToXY(_x, _y + distacneFromStart);
            cout << " ";
            break;
        }
        case SqrType::FOOD: {
            goToXY(_x, _y + distacneFromStart);
            if(isWithColor)
                changeColor(9);
            cout << char(250);
            break;
        }
        case SqrType::WALL: {
            goToXY(_x, _y + distacneFromStart);
            if (isWithColor)
                changeColor(5);
            cout << char(219);
            break;
        }
        case SqrType::PACMAN: {
            goToXY(_x, _y + distacneFromStart);
            if (isWithColor)
                changeColor(6);
            cout << "@";
            break;
        }
        case SqrType::GHOST: {
            goToXY(_x, _y + distacneFromStart);
            if (isWithColor)
                changeColor(12);
            cout << "$";
            break;
        }        
        case SqrType::FRUIT: {
            goToXY(_x, _y + distacneFromStart);
            if (isWithColor)
                changeColor(2);
            break;
        }
    }
}

void changeColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


void Square::setSquare(const int x, const int y, const SqrType sqrType) {
    this->setX(x);
    this->setY(y);
    this->setSqrType(sqrType);
}
void Square::setSquare(const Square& sqr) {
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
