#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Ship.h"
#include "GameConfig.h"

class Player {
public:
	Player(const std::string& name);
	void placeShip(Ship& ship);
	bool reaceiveAttack(int x, int y);

private:
	void initializeShips();
	void initializeBoards();
	void printBoard(std::string board[MAX_X_COORDINATE][MAX_Y_COORDINATE]);
	std::string name;
	std::string playersBoard [MAX_X_COORDINATE][MAX_Y_COORDINATE];
	std::string bombBoard [MAX_X_COORDINATE][MAX_Y_COORDINATE];
	std::vector<Ship> ships;
};
#endif
