#include "Ship.h"
#include <iostream>
#include <algorithm>

Ship::Ship(const std::string &name, int size, int xCoordinate, int yCoordinate, Orientation orientation) : name(name), size(size), hits(0)
{
    for (int i = 0; i < size; i++)
    {
        int dx = i * (orientation == Orientation::HORIZONTAL ? 0 : 1);
        int dy = i * (orientation == Orientation::HORIZONTAL ? 1 : 0);
        coordinates.emplace_back(xCoordinate + dx, yCoordinate + dy);
    }

    int foregroundColor = rand() % 7;
    int backgroundColor = rand() % 7;
    // make sure the colors are not the same
    while (foregroundColor == backgroundColor)
    {
        backgroundColor = rand() % 7;
    }

    /**        foreground background
        black        30         40
        red          31         41
        green        32         42
        yellow       33         43
        blue         34         44
        magenta      35         45
        cyan         36         46
        white        37         47
     */

    this->colors = std::make_pair(foregroundColor + 30, backgroundColor + 40);
}

/**
 * @return A pair of integers representing the colors of the ship
 */

std::pair<int, int> Ship::getColors() const
{
    return colors;
}

void Ship::setColors(int color1, int color2)
{
    colors.first = color1;
    colors.second = color2;
}

void Ship::setHits(int hits)
{
    this->hits = hits;
}

bool Ship::isSunk() const
{
    return hits >= size;
}

/**
 * @param x The x coordinate of the shot
 * @param y The y coordinate of the shot
 */
ShootResult Ship::hit(int x, int y)
{
    auto hitPosition = std::find(coordinates.begin(), coordinates.end(), std::make_pair(x, y));
    if (hitPosition != coordinates.end())
    {
        hits++;
        if (hits == size)
        {
            return ShootResult::SUNK;
        }
        return ShootResult::HIT;
    }
    return ShootResult::MISS;
}

/**
 * @return A vector of pairs representing the coordinates of the ship
 */
std::vector<std::pair<int, int>> Ship::getCoordinates() const
{
    return coordinates;
}

int Ship::getSize()
{
    return this->size;
}

int Ship::getHits()
{
    return hits;
}

Orientation Ship::getOrientation()
{
    return orientation;
}

std::string Ship::getName()
{
    return this->name;
}

