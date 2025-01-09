#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "GameTypes.h"
#include <vector>
#include <utility>  // for std::pair

enum class Orientation {
    HORIZONTAL = 0,
    VERTICAL = 1
};



class Ship {
public:
	Ship(const std::string& name, int size, int xCoordinate, int yCoordinate, Orientation orientation);
	bool isSunk() const;
	ShootResult hit(int x, int y);
	std::string getName();
	int getSize();
	std::vector<std::pair<int, int>> getCoordinates() const;

private:
	int size;
	int hits;
	Orientation orientation;
	std::vector<std::pair<int, int>> coordinates;
	std::string name;
};
#endif
