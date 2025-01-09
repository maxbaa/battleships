#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Ship.h"
#include "GameConfig.h"

enum class GameState {
    PLACING_SHIPS,
	ATTACKING,
    WAITING_FOR_ATTACK,
    GAME_OVER
};

enum class GameMode {
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI,
    AI_VS_AI
};


class Player {
public:
	Player(const std::string& name);
	void placeShip(const std::string& name, int size);
	bool reaceiveAttack(int x, int y);
	void gameLoop();
	void attack();
private:
	std::pair<int, int> getCoordinates();
	Orientation getOrientation();
	void initializeShips();
	std::string name;
	std::vector<Ship> ships;
	GameBoard board;
	GameState state;
	GameMode gameMode;

};
#endif
