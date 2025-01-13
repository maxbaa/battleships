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
	int getHits();
	Orientation getOrientation();
	std::vector<std::pair<int, int>> getCoordinates() const;
	std::pair<int, int> getColors() const;
	void setColors(int color1, int color2);
	void setHits(int hits);

private:
	int size;
	int hits;
	Orientation orientation;
	std::vector<std::pair<int, int>> coordinates;
	std::string name;
	std::pair<int, int> colors;
	
};
#endif
