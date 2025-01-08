#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "GameConfig.h"
#include <string>
#include <vector>

// Forward declare Ship class instead of including Ship.h
class Ship;
enum class Orientation;  // Forward declare Orientation enum

enum class CellStates {
    EMPTY,
    SHIP,
    HIT,
    MISS
};

enum class ShootResult {
    HIT,
    MISS,
    SUNK
};

class GameBoard {
public:
    GameBoard();
    void display() const;
    std::vector<Ship*> getShips() const { return ships; }
    Ship* tryPlaceShip(const std::string& name, int size, int xCoordinate, int yCoordinate, Orientation orientation);
    ShootResult shoot(int x, int y);

private:
    CellStates grid[MAX_X_COORDINATE][MAX_Y_COORDINATE];
    std::vector<Ship*> ships;
    char getCellState(int x, int y) const;
};

#endif