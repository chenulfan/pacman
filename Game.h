#pragma once

#include "fruit.h"
#include "Ghost.h"

static const int SPEED = 50;

void clearConsoleRow();

enum class Level { BEST, GOOD, NOVICE };

const static int TEST_FAILED = -1;
const static int TEST_PASSED = -2;
const static int GAME_OVER = 1;
const static int CONTINUE_TO_NEXT_GAME = 0;

char intToDir(int num);

class Game {

private:
    Board _board;
    char _playerKey = STAY;
    Pacman _pacman;
    int _health = 3;
    int _points = 0;
    int _allPoints = 0;
    int _maxPoints = 0;
    bool _isWithColor = false;
    bool _isSilentMode = false;
    int _numOfGhosts = 0;
    int _totalCounterMoves = 1;
    Ghost _ghosts[4];
    Square _legend;
    Fruit _fruit;
    bool _saveToFile = false;
    ofstream _stepsFile;
    ofstream _resultFile;


public:
    int getKey()const;
    const int getPoints() const { return _allPoints; };
    const int getHealth() const { return _health; };
    const int getMaxPoints() const { return _maxPoints; };
    Board getBoard() const { return _board; };
    Pacman getPacman() const { return _pacman; }
    Square getLegend() const { return _legend; }
    const int getHeight() const { return _board.getHeight(); }
    const int getWidth() const { return _board.getWidth(); }
    ofstream& getStepsFile() { return _stepsFile; };
    ofstream& getResultFile() { return _resultFile; };
    bool getIsSilentMode() { return _isSilentMode; };

    void setMaxPoints(const int num) { _maxPoints = num; };
    void setPoints();
    void setHealth();
    void setPlayerKey(char newKey) { _playerKey = newKey; };
    void setStepsFile(string fileName) { _stepsFile.open(fileName); };
    void setResultFile(string fileName) { _resultFile.open(fileName); };
    void setIsSilentMode( bool isSilentMode) { _isSilentMode = isSilentMode; };

    const bool isCreatureHitWall(Creature& creature) const;
    const bool isPacmanHitGhost(const Square& position);
    const bool isPacmanHitGhostLoaded(const Square& position);
    const bool isCreatureInTunnel(Creature& creature);
    const bool isPacmanAteFood() const;
    const bool isTunnel();
    const bool isPacmanAteFruit(const Fruit& fruit) const;
    const bool isGhostAteFruit(const Fruit& fruit, const Ghost& ghost) const;
    const bool isGhostHitPacman(Square position);\

    bool isGhostsAteFruit();
    
    void deletePacmanLastMove();
    void deleteCreatureLastMove(Creature& creature);
    void deleteGhostLastMove(Ghost& ghost);

    int startGame(const bool withColor, string filename, Level type, bool saveToFile);
    int loadGame(const bool withColor, bool isSilent, bool& isfinished, string boardFileName);
    void printBanner()const;
    void setWithColor(const bool isWithColor) { _isWithColor = isWithColor; };
    void resetGameAfterGhostHit();
    void resetGame();
    bool printGhostsAndCheckifGhostHitPacman(Level type, int counterGhostsMoves, ofstream& file);
    void movePacmanThruTunnel();
    void MoveAndPrintCreature(Creature& creature, ofstream& file);
    void MoveAndPrintLoadedCreature(Creature& creature, char dir);
    void printGhosts(int isWithColor);
    void isParallelTunnelIsFood(int yPos, int xPos);
};