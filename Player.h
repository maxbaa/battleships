#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Ship.h"

class Player {
public:
	Player(const std::string name);
	void placeShip(const Ship& ship);
	bool reaceiveAttack(int x, int y);

private:
	std::string name;
	std::vector<std::vector<int>> board;
	std::vector<Ship> ships;
};
#endif
