#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Ship.h"
#include "GameConfig.h"

class Player {
public:
	Player(const std::string& name);
	void placeShip(const std::string& name, int size);
	bool reaceiveAttack(int x, int y);

private:
	void initializeShips();
	std::string name;
	std::vector<Ship> ships;
	GameBoard board;

};
#endif
