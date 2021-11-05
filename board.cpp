
#include "board.h"

const int row_length = 77;
const int col_length = 21;

bool isWall(const int* arr, int j);


void Board::printBoard() {
    for (int i = 0; i < col_length; i++) {
        for (int j = 0; j < row_length; j++) {
            _squares[i][j].print();
        }
    }
}

void Board::initBoard() {


    //walls arrays for row
    const int row1And9[3] = { 20,56,-1 };
    const int row2And8[] = { 8,10,12,20,28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48,56,64,66,68,-1 };
    const int row3And7[3] = { 8,68,-1 };
    const int row4[15] = { 8, 16, 18, 20, 28, 30, 32, 44, 46, 48, 56, 58, 60, 68,-1 };
    const int row5[3] = { 28,48,-1 };
    const int row6[20] = { 8, 16, 18, 20, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 56, 58, 60, 68,-1 };

    for (int i = 0; i < col_length; i++) {
        for (int j = 0; j < row_length; j++) {
            //row 1 enums
            if (i == 2 || i == 18) {
                if (isWall(row1And9, j))
                    _squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 4 == 0)
                        _squares[i][j].setSquare(j, i, 1);
                    else
                        _squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 2 enums
            if (i == 4 || i == 16) {
                if (isWall(row2And8, j)) {
                    _squares[i][j].setSquare(j, i, 3);
                }
                else
                    if (j % 4 == 0)
                        _squares[i][j].setSquare(j, i, 1);
                    else
                        _squares[i][j].setSquare(j, i, 0);
            }
            //row 3 enums
            if (i == 6 || i == 14) {
                if (isWall(row3And7, j))
                    _squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 4 == 0)
                        _squares[i][j].setSquare(j, i, 1);
                    else
                        _squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 4 enums
            if (i == 8) {
                if (isWall(row4, j))
                    _squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 4 == 0)
                        _squares[i][j].setSquare(j, i, 1);
                    else
                        _squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 5 enums
            if (i == 10) {
                if (isWall(row5, j))
                    _squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 4 == 0)
                        _squares[i][j].setSquare(j, i, 1);
                    else
                        _squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 6 enums
            if (i == 12) {
                if (isWall(row6, j))
                    _squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 4 == 0)
                        _squares[i][j].setSquare(j, i, 1);
                    else
                        _squares[i][j].setSquare(j, i, 0);
                }
            }
            //FILLERS
            if (i == 1 || i == 3 || i == 19 || i == 17) {
                if (isWall(row1And9, j))
                    _squares[i][j].setSquare(j, i, 3);
            }

            if (i == 5 || i == 7 || i == 13 || i == 15) {
                if (isWall(row3And7, j))
                    _squares[i][j].setSquare(j, i, 3);
            }
            if (i == 9 || i == 11) {
                if (isWall(row5, j))
                    _squares[i][j].setSquare(j, i, 3);
            }
            if (i == 0 || i == 20 || j == 0 || j == 76) {
                _squares[i][j].setSquare(j, i, 3);

            }
        }
    }
    setTunnels();
}

bool isWall(const int* arr, int j) {
    const int* p = arr;
    while (*p != -1) {
        if (j == *p)
            return true;
        p++;
    }
    return false;
}

Square Board::getSquare(int x, int y) { 
    return _squares[x][y]; 
};

void Board::setTunnels() {
    _squares[0][38].setSqrType(2);
    _squares[20][38].setSqrType(2);
    _squares[10][0].setSqrType(2);
    _squares[10][76].setSqrType(2);

}

