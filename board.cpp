
#include "board.h"

const int row_length = 39;
const int col_length = 11;

bool isWall(const int* arr, int j);

void Board::printBoard() {
    for (int i = 0; i < col_length; i++) {
        for (int j = 0; j < row_length; j++) {
            squares[i][j].print();
        }
    }
}

void Board::initBoard() {

    const int row1And9[3] = { 10,28,-1 };
    const int row2And8[19] = { 1,2,3,7, 8,9,11, 12, 13, 25, 26, 27, 29, 30, 31, 35, 36, 37,-1 };
    const int row3And7[3] = { 4,34,-1 };
    const int row4[15] = { 4, 8, 9, 10, 14, 15, 16, 22, 23, 24, 28, 29, 30, 34,-1 };
    const int row5[3] = { 14,24,-1 };
    const int row6[20] = { 4, 8, 9, 10, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 30, 34,-1 };


    for (int i = 0; i < col_length; i++) {
        for (int j = 0; j < row_length; j++) {
            //row 1 enums
            if (i == 1 || i == 9) {
                if (isWall(row1And9, j))
                    squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 2 == 0)
                        squares[i][j].setSquare(j, i, 1);
                    else
                        squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 2 enums
            if (i == 2 || i == 8) {
                if (isWall(row2And8, j)) {
                    if (j % 2 == 0)
                        squares[i][j].setSquare(j, i, 1);
                    else
                        squares[i][j].setSquare(j, i, 0);
                }
                else
                    squares[i][j].setSquare(j, i, 3);
            }
            //row 3 enums
            if (i == 3 || i == 7) {
                if (isWall(row3And7, j))
                    squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 2 == 0)
                        squares[i][j].setSquare(j, i, 1);
                    else
                        squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 4 enums
            if (i == 4) {
                if (isWall(row4, j))
                    squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 2 == 0)
                        squares[i][j].setSquare(j, i, 1);
                    else
                        squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 5 enums
            if (i == 5) {
                if (isWall(row5, j))
                    squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 2 == 0)
                        squares[i][j].setSquare(j, i, 1);
                    else
                        squares[i][j].setSquare(j, i, 0);
                }
            }
            //row 6 enums
            if (i == 6) {
                if (isWall(row6, j))
                    squares[i][j].setSquare(j, i, 3);
                else {
                    if (j % 2 == 0)
                        squares[i][j].setSquare(j, i, 1);
                    else
                        squares[i][j].setSquare(j, i, 0);
                }
            }

            if (i == 0 || i == 10 || j == 0 || j == 38) {
                squares[i][j].setSquare(j, i, 3);

            }
        }
    }
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