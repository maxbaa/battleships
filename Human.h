#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "GameTypes.h"
#include <string>

class Human : public Player {
public:
	Human(const std::string& name);
	void placeShip(const std::string& name, int size) override;
	AttackResult attack(GameBoard& enemyBoard) override;
	AttackResult attackTurn(GameBoard& enemyBoard) override;
	GameBoard& getBoard() override;
	GameBoard& getHitBoard() override;
	void setHitBoard(AttackResult result);
	void receiveAttack(int x, int y);

private:
	std::pair<int, int> getCoordinates();
	Orientation getOrientation();
	GameBoard board;
	GameBoard hitBoard;
};

#endif
