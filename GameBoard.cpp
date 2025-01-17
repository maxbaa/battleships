#include "GameBoard.h"
#include "Ship.h"
#include <iostream>

GameBoard::GameBoard()
{
    for (int i = 0; i < MAX_X_COORDINATE; i++)
    {
        for (int j = 0; j < MAX_Y_COORDINATE; j++)
        {
            grid[i][j] = CellStates::EMPTY;
        }
    }
}

/**
 * @return A ShootResult enum representing the result of the shoot
 */
ShootResult GameBoard::shoot(int x, int y)
{
    if (grid[x][y] == CellStates::SHIP)
    {
        setCell(x, y, CellStates::HIT);

        for (Ship *ship : ships)
        {
            ShootResult result = ship->hit(x, y);
            if (result == ShootResult::SUNK)
            {
                return ShootResult::SUNK;
            }
            else if (result == ShootResult::HIT)
            {
                return ShootResult::HIT;
            }
        }
        return ShootResult::INVALID;
    }
    else if (grid[x][y] == CellStates::EMPTY)
    {
        setCell(x, y, CellStates::MISS);
        return ShootResult::MISS;
    }
    else
    {
        return ShootResult::INVALID;
    }
}

void GameBoard::setCell(int x, int y, CellStates result)
{
    grid[x][y] = result;
}

void GameBoard::setGrid(const CellStates newGrid[MAX_X_COORDINATE][MAX_Y_COORDINATE]) {
    for (int x = 0; x < MAX_X_COORDINATE; ++x) {
        for (int y = 0; y < MAX_Y_COORDINATE; ++y) {
            grid[x][y] = newGrid[x][y];
        }
    }
}

/**
 * @return nullptr if the ship cannot be placed, otherwise a pointer to the ship
 */
Ship *GameBoard::tryPlaceShip(const std::string &name, int size, int xCoordinate, int yCoordinate, Orientation orientation)
{
    // std::cout << "tryPlaceShip" << size << " " << xCoordinate << " " << yCoordinate << " " << (orientation == Orientation::HORIZONTAL ? "H" : "V") << std::endl;
    // Check if ship placement is valid
    for (int i = 0; i < size; i++)
    {
        int dx = i * (orientation == Orientation::HORIZONTAL ? 0 : 1);
        int dy = i * (orientation == Orientation::HORIZONTAL ? 1 : 0);
        int x = xCoordinate + dx;
        int y = yCoordinate + dy;

        if (x < 0 || x >= MAX_X_COORDINATE || y < 0 || y >= MAX_Y_COORDINATE)
        {
            return nullptr;
        }
        if (grid[x][y] != CellStates::EMPTY)
        {
            std::cout << "tryPlaceShip" << size << " " << xCoordinate << " " << yCoordinate << " " << (orientation == Orientation::HORIZONTAL ? "H" : "V") << " failed" << " at " << x << " " << y << std::endl;
            return nullptr;
        }
    }

    // Place the ship
    for (int i = 0; i < size; i++)
    {
        int dx = i * (orientation == Orientation::HORIZONTAL ? 0 : 1);
        int dy = i * (orientation == Orientation::HORIZONTAL ? 1 : 0);
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
std::string GameBoard::getCellState(int x, int y) const
{
    // If cell part of a sunk ship, display with an -
    for (Ship *ship : ships)
    {
        for (auto coord : ship->getCoordinates())
        {
            if (coord.first == x && coord.second == y && ship->isSunk())
            {
                auto colors = ship->getColors();
                std::string color = "\033[1;" + std::to_string(colors.first) + ";" + std::to_string(colors.second) + "m";
                std::string reset = "\033[0m";
                return color.append("-").append(reset);
            }
        }
    }

    CellStates state = grid[x][y];
    switch (state)
    {
    case CellStates::EMPTY:
        return " ";
    case CellStates::SHIP:
    {
        for (Ship *ship : ships)
        {
            for (auto coord : ship->getCoordinates())
            {
                if (coord.first == x && coord.second == y)
                {
                    auto colors = ship->getColors();
                    std::string color = "\033[1;" + std::to_string(colors.first) + ";" + std::to_string(colors.second) + "m";
                    std::string reset = "\033[0m";
                    return color.append("S").append(reset);
                }
            }
        }
    }
    case CellStates::HIT:
        return "X";
    case CellStates::MISS:
        return "O";
    default:
        return "?";
    }
}

void GameBoard::display(std::string name) const
{
    std::cout << name << std::endl
              << "  ";

    for (int y = 0; y < MAX_Y_COORDINATE; y++)
    {
        std::cout << "|" << static_cast<char>('A' + y);
    }

    std::cout << std::endl;
    for (int x = 0; x < MAX_X_COORDINATE; x++)
    {
        if (x != 9)
        {
            std::cout << (x + 1) << " ";
        }
        else
        {
            std::cout << (x + 1);
        }

        for (int y = 0; y < MAX_Y_COORDINATE; y++)
        {
            std::cout << "|" << getCellState(x, y);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void GameBoard::addShip(int size, int hits, Orientation orientation, int x, int y, std::string name, std::pair<int, int> colors)
{
    Ship* ship = new Ship(name, size, x, y, orientation);
    ship->setHits(hits);
    ship->setColors(colors.first, colors.second);
    ships.push_back(ship);
}

void GameBoard::deleteShips() {
    for (int i = 0; i < ships.size(); i++) {
        delete ships[i];
    }
}