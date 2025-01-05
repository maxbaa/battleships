#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "GameConfig.h"
#include <vector>

class Ship {
public:
	Ship(const std::string& name, int size, int xCoordinate, int yCoordinate);
	bool isSunk() const;
	void hit();
	void addCoordinates(int x, int y);
	std::string getName();
	int getSize();
private:
	int size;
	int hits;
	std::vector<std::pair<int, int>> coordinates;
	std::string name;
};
#endif
