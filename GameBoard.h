#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

class GameBoard {
public:
    GameBoard(int size = 10);
    void display() const;

private:
    int size;
    std::vector<std::vector<int>> grid;
};

#endif