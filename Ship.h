#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "GameConfig.h"
#include "GameBoard.h"
#include <vector>

enum class Orientation {
    HORIZONTAL = 1,
    VERTICAL = 0
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
