#ifndef PLAYER_H
#define PLAYER_H

#include "GameBoard.h"
#include "GameTypes.h"
#include <string>

class Player {
public:
    Player(const std::string& name) : name(name) {}
    virtual ~Player() = default;
    
    virtual void placeShip(const std::string& name, int size) = 0;
    virtual AttackResult attack(GameBoard& enemyBoard) = 0;
    virtual AttackResult attackTurn(GameBoard& enemyBoard) = 0;
    virtual GameBoard& getBoard() = 0;
    virtual GameBoard& getHitBoard() = 0;
    
    std::string getName() const { return name; }

protected:
    std::string name;
};

#endif 