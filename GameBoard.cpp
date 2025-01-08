#include "GameBoard.h"
#include "Ship.h"
#include <iostream>

GameBoard::GameBoard() {
    for (int i = 0; i < MAX_X_COORDINATE; i++) {
        for (int j = 0; j < MAX_Y_COORDINATE; j++) {
            grid[i][j] = CellStates::EMPTY;
        }
    }
}



/**
 * @return A ShootResult enum representing the result of the shoot
 */
ShootResult GameBoard::shoot(int x, int y) {
    if (grid[x][y] == CellStates::SHIP) {
        grid[x][y] = CellStates::HIT;

        for (Ship* ship : ships) {
            ShootResult result = ship->hit(x, y);
            if (result == ShootResult::SUNK) {
                return ShootResult::SUNK;
            }
            else if (result == ShootResult::HIT) {
                return ShootResult::HIT;
            }
        }
        return ShootResult::HIT;
    }
    else {
        grid[x][y] = CellStates::MISS;
        return ShootResult::MISS;
    }
}


/**
 * @return nullptr if the ship cannot be placed, otherwise a pointer to the ship
 */
Ship* GameBoard::tryPlaceShip(const std::string& name, int size, int xCoordinate, int yCoordinate, Orientation orientation) {
    // Check if ship placement is valid
    for (int i = 0; i < size; i++) {
        int dx = i * (orientation == Orientation::HORIZONTAL ? 1 : 0);
        int dy = i * (orientation == Orientation::HORIZONTAL ? 0 : 1);
        int x = xCoordinate + dx;
        int y = yCoordinate + dy;
        
        if (x < 0 || x >= MAX_X_COORDINATE || y < 0 || y >= MAX_Y_COORDINATE) {
            return nullptr;
        }
        if (grid[x][y] != CellStates::EMPTY) {
            return nullptr;
        }
    }

    // Place the ship
    for (int i = 0; i < size; i++) {
        int dx = i * (orientation == Orientation::HORIZONTAL ? 1 : 0);
        int dy = i * (orientation == Orientation::HORIZONTAL ? 0 : 1);
        int x = xCoordinate + dx;
        int y = yCoordinate + dy;
        grid[x][y] = CellStates::SHIP;
    }
    
    ships.push_back(new Ship(name, size, xCoordinate, yCoordinate, orientation));
    return ships.back();
}

/**
 * Use to display the cell state in the console
 * @return A char representing the state of the cell
 */
char GameBoard::getCellState(int x, int y) const {
    CellStates state = grid[x][y];
    switch (state) {
        case CellStates::EMPTY: return ' ';
        case CellStates::SHIP: return 'S';
        case CellStates::HIT: return 'X';
        case CellStates::MISS: return 'O';
        default: return '?';
    }
}

void GameBoard::display() const {
    std::cout << "Seekarte:" << std::endl << "  ";

    for (int y = 0; y < MAX_Y_COORDINATE; y++) {
        std::cout << "|" << static_cast<char>('A' + y);
    }

    std::cout << std::endl;
    for (int x = 0; x < MAX_X_COORDINATE; x++) {
        if (x != 9) {
            std::cout << (x + 1) << " ";
        }
        else {
            std::cout << (x + 1);
        }

        for (int y = 0; y < MAX_Y_COORDINATE; y++) {
            std::cout << "|" << getCellState(x, y);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}