#include "Ship.h"
#include <iostream>
#include <algorithm>

Ship::Ship(const std::string& name, int size, int xCoordinate, int yCoordinate, Orientation orientation) : name(name), size(size), hits(0) {
    for (int i = 0; i < size; i++) {
        int dx = i * (orientation == Orientation::HORIZONTAL ? 1 : 0);
        int dy = i * (orientation == Orientation::HORIZONTAL ? 0 : 1);
        coordinates.emplace_back(xCoordinate + dx, yCoordinate + dy);
    }
}

bool Ship::isSunk() const {
    return hits >= size;
}


/**
 * @param x The x coordinate of the shot
 * @param y The y coordinate of the shot
 */
ShootResult Ship::hit(int x, int y) {
    auto hitPosition = std::find(coordinates.begin(), coordinates.end(), std::make_pair(x, y));
    if (hitPosition != coordinates.end()) {
        hits++;
        if (hits == size) {
            return ShootResult::SUNK;
        }
        return ShootResult::HIT;
    }
    return ShootResult::MISS;
}

/**
 * @return A vector of pairs representing the coordinates of the ship
 */
std::vector<std::pair<int, int>> Ship::getCoordinates() const {
    return coordinates;
}

int Ship::getSize()
{
    return this->size;
}

std::string Ship::getName()
{
    return this->name;
}
