#include "Ship.h"
#include <iostream>

Ship::Ship(const std::string& name, int size, int xCoordinate, int yCoordinate)
{
	this->name = name;
	this->size = size;
    coordinates.emplace_back(xCoordinate, yCoordinate);
}


void Ship::addCoordinates(int x, int y) 
{
    coordinates.emplace_back(x, y);
}

bool Ship::isSunk() const 
{
    return hits >= size;
}

void Ship::hit() 
{
    hits++;
    std::cout << name << " wurde getroffen!\n";
}

int Ship::getSize()
{
    return this->size;
}

std::string Ship::getName()
{
    return this->name;
}
