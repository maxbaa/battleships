#ifndef AI_H
#define AI_H

#include "Player.h"
#include "GameTypes.h"
#include <string>

class AI : public Player {
public:
	AI(const std::string& name);
	void placeShip(const std::string& name, int size) override;
	AttackResult attack(GameBoard& enemyBoard) override;
	AttackResult attackTurn(GameBoard& enemyBoard) override;
	GameBoard& getBoard() override;
	GameBoard& getHitBoard() override;

private:
	std::pair<int, int> getRandomCoordinates();
	Orientation getRandomOrientation();
	GameBoard board;
	GameBoard hitBoard;
};

#endif
