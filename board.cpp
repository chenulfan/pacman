
#include "board.h"


bool isWall(const int* arr, const int j);

void Board::printBoard(const bool isWithColor) {
    for (int i = _distanceFromStart; i < _height + _distanceFromStart; i++) {
        for (int j = 0; j < _width; j++) {
            _squares[i - _distanceFromStart][j].print(isWithColor, _distanceFromStart);
        }
    }
}

void Board::initBoardWidth(string firstRow) {
    _width = firstRow.size();
}

int Board::initBoard(Ghost* ghosts, int& ghostCounter, Square& pacmanStart, Square& legend,string filename,int& foodCounter) {
    int type = 0;
    ghostCounter = 0;

    string* map = _screen.getFromFile(filename); 
    if (_screen.getHeight() > 24) { return 5; }
    if (_screen.getWidth() > 79) {return 6;}

    initBoardWidth(map[0]);

    updateActualGameBoardHeight(map, _screen.getHeight());
    updateActualGameBoardWidth(map, _screen.getHeight());

    _squares = initSquares();

    legend = getLegendPos(map, _screen.getHeight());

    return analyzeBoard(map, _screen.getHeight(), ghosts, ghostCounter, pacmanStart, foodCounter);

}

int Board::analyzeBoard(string* map, int len, Ghost* ghosts, int& ghostCounter, Square& pacmanStart, int& foodCounter) {
    int type, start = 0, startCol = 0;
    int lenRow = _width;
    int counterPacman = 0, counterLegend = 0;

    for (int i = _distanceFromStart; i < _height + _distanceFromStart; ++i) {
        for (int j = _distanceFromLeft; j < _width + _distanceFromLeft; ++j) {
            type = convertType(map[i][j]);

            if ((SqrType)type == SqrType::LEGEND) {
                counterLegend++;
                if (counterLegend > 1) {
                    return 3;
                }
                _squares[i - _distanceFromStart][j - _distanceFromLeft].setSquare(j - _distanceFromLeft, i - _distanceFromStart, SqrType::LEGEND);
            }

            else if ((SqrType)type == SqrType::WALL) {
                _squares[i - _distanceFromStart][j - _distanceFromLeft].setSquare(j - _distanceFromLeft, i - _distanceFromStart, SqrType::WALL);
            }

            else if ((SqrType)type == SqrType::FOOD) {
                _squares[i - _distanceFromStart][j - _distanceFromLeft].setSquare(j - _distanceFromLeft, i - _distanceFromStart, SqrType::FOOD);
                foodCounter++;
            }

            else if ((SqrType)type == SqrType::GHOST) {
                Ghost g((int)DIRECTIONS::RIGHT, j - _distanceFromLeft, i - _distanceFromStart);
                ghosts[ghostCounter++] = g;
                if (ghostCounter > 4) 
                {
                    return 4;
                }
                _squares[i - _distanceFromStart][j - _distanceFromLeft].setSquare(j - _distanceFromLeft, i - _distanceFromStart, SqrType::EMPTY);
            }

            else if ((SqrType)type == SqrType::PACMAN) {
                counterPacman++;
                if (counterPacman > 1) { 
                    return 2;
                }
                pacmanStart.setX(j - _distanceFromLeft);
                pacmanStart.setY(i - _distanceFromStart);
                pacmanStart.setSqrType(SqrType::PACMAN);
                _squares[i - _distanceFromStart][j - _distanceFromLeft].setSquare(j - _distanceFromLeft, i - _distanceFromStart, SqrType::EMPTY); // TODO : CHECK IF PACMAN TYPE
            }

            else {
                _squares[i - _distanceFromStart][j - _distanceFromLeft].setSquare(j - _distanceFromLeft, i - _distanceFromStart, SqrType::EMPTY);
            }
        }
        
    }
    return 1;
}



Square Board::getLegendPos(string* map, int len) {
    Square s;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == '&') {
                s.setSquare(j, i, SqrType::LEGEND);
                return s;
            }
        }
    }
}

void Board::resetBoard() {
    for (int i = 0; i < _height; i++)
    {
        delete[] _squares[i];
    }
    _length = 0;
    _height = 0;
    _width = 0;
    _amountOfGhosts = 0;
    _distanceFromStart = 0;
    _distanceFromLeft = 0;
}

Square** Board::initSquares() {
    Square** squares = new Square * [_height];
    for (int i = 0; i < _height; ++i) {
        squares[i] = new Square[_width];
    }
    return squares;
}

void Board::getGhosts(Square* ghosts) const {
    int counter = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_squares[i][j].getSqrType() == SqrType::GHOST) {
                ghosts[counter] = _squares[i][j];
                _squares[i][j].setSqrType(SqrType::EMPTY);
                counter++;
            }
        }
    }
}

void Board::updateActualGameBoardWidth(string* map,int height) {
    int width = 0, distanceFromLeft;
    bool foundStart = false;
    for (int j = _distanceFromStart;j < _height + _distanceFromStart;j++) {
        for (int i = 0; i < map[j].size(); ++i) {
            if (map[j][0] == '#') {
                if (map[j][0] == '#' && map[j][map[j].size() - 1] == '#') {
                    if (map[j].size() - 1 > width) {
                        width = map[j].size();
                        _distanceFromLeft = 0;
                    }
                }
            }
            else {
                if (map[j][i] != '#') 
                    continue; 
                if (map[j][i] == '#' && map[j][map[j].size() - 1] == '#') {
                   if ((map[j].size() - i) > width) {
                        width = map[j].size()  - i;
                        _distanceFromLeft = i;
                    }

                }
            }
        }
    }
    _width = width;
}   

void Board::updateActualGameBoardHeight(string* map, int len) {
    int start = 0, end = 0, counter = 0;
    bool foundFirstRow = false;
    bool foundWall = false;

    for (int i = 0; i < len; i++) {
        foundWall = false;

        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#') {
                foundWall = true;
                break;
            }
        }

        if (foundFirstRow) {
            if (foundWall) {
                end = i;
            }
        }
        else {
            if (foundWall) {
                start = i;
                _distanceFromStart = i;
                foundFirstRow = true;
            }
        }
    }
    _height = end - start + 1;
}

bool isWall(const int* arr, const int j) {
    const int* p = arr;
    while (*p != -1) {
        if (j == *p)
            return true;
        p++;
    }
    return false;
}

//for (int i = 0; i < len; i++) {
//    foundWall = false;
//    for (int j = 0; j < map[i].size(); j++) {
//        if (!firstRowWall) {
//            if (map[i][j] == '#') {
//                foundWall = true;
//                break;
//            }
//        }
//        else if (map[i][j] == '#')
//            counter++;
//    }
//    if (counter == 0 && firstRowWall) {
//        end = i;
//        break;
//    }
//}
//if (end == 0)
//end = len;
//
//_height = end - start;


//void readMapFromFile(int& foodCounter, int& ghostCounter, Square& pacmanStart) {
//
//    int type;
//    Square** arr = nullptr;
//    ifstream file(dafuq);
//    string str;
//
//    _width = getFirstRowSize();
//    _height = getColSize();
//
//    arr = initArr();
//
//    for (int i = 0; i < _height; i++) {
//        getline(file, str);
//        for (int j = 0; j < _width; j++) {
//            type = convertType(str[j]);
//            if ((SqrType)type == SqrType::FOOD) { foodCounter++; }
//            if ((SqrType)type == SqrType::GHOST) { ghostCounter++; }
//            if ((SqrType)type == SqrType::PACMAN) {
//                pacmanStart.setX(j);
//                pacmanStart.setY(i);
//                pacmanStart.setSqrType(SqrType::PACMAN);
//            }
//            arr[i][j].setSquare(j, i, (SqrType)type);
//        }
//    }
//}

