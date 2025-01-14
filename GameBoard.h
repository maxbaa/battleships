#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GameConfig.h"
#include "GameTypes.h"
#include <string>
#include <vector>

// Forward declarations
class Ship;
enum class Orientation;

enum class CellStates {
    EMPTY,
    SHIP,
    HIT,
    MISS
};

class GameBoard {
public:
    GameBoard();
    void display(std::string text = "Seekarte") const;
    void addShip(int size, int hits, Orientation orientation, int x, int y, std::string name, std::pair<int, int> colors);
    void deleteShips();
    std::vector<Ship*> getShips() const { return ships; }
    Ship* tryPlaceShip(const std::string& name, int size, int xCoordinate, int yCoordinate, Orientation orientation);
    ShootResult shoot(int x, int y);
    void setCell(int x, int y, CellStates result);
    const CellStates(&getGrid() const)[MAX_X_COORDINATE][MAX_Y_COORDINATE]{ return grid; };
    void setGrid(const CellStates newGrid[MAX_X_COORDINATE][MAX_Y_COORDINATE]);

private:
    CellStates grid[MAX_X_COORDINATE][MAX_Y_COORDINATE];
    std::vector<Ship*> ships;
    std::string getCellState(int x, int y) const;
};

#endif