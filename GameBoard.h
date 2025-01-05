#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "GameConfig.h"

class GameBoard {
public:
    void display() const;

private:
    int size;
    int grid[MAX_X_COORDINATE][MAX_Y_COORDINATE];
};

#endif