#pragma once

#include "map.h"
#include "ghost.h"

class Ghost;
class Board {
    private:
        Square** _squares;
        int _length;
        int _height;
        int _width;
        int _amountOfGhosts;
        int _distanceFromStart;
        int _distanceFromLeft;
        Map _screen;

    public:
        virtual ~Board() {
            for (int i = 0; i < _height; i++) {
                delete[] _squares[i];
            }
            delete[] _squares;
        };

        const int getHeight() const { return _height; }
        const int getWidth() const { return _width; }
        const int getDistantceFromStart() const { return _distanceFromStart; }
        const int getDistantceFromLeft() const { return _distanceFromLeft; }
        const Square& getSquare(const int y, const int x) const { return _squares[y][x]; };
        Square** getArrSquare() { return _squares; }
        void printBoard(const bool isWithColor, bool isSilentMode = false);
        void setSqrType(const int y, const int x, const SqrType sqr) { _squares[y][x].setSqrType(sqr); }
        void getGhosts(Square* ghosts) const;
        void updateActualGameBoardHeight(string* map, int len);
        void updateActualGameBoardWidth(string* map,int height);
        void initBoardWidth(string firstRow) ;
        int initBoard(Ghost* ghosts, int& amountOfGhosts, Square& pacmanStart, Square& legend,string filename,int& foodCounter);
        int analyzeBoard(string* map, int len, Ghost* ghosts, int& amountOfGhosts, Square& pacmanStart, int& foodCounter);
        Square** initSquares();
        Square getLegendPos(string* map, int len);
        void resetBoard();

    private:
        bool isWall(const int* arr, const int j);
};

