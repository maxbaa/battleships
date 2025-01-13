#ifndef PLAYER_H
#define PLAYER_H

#include "GameBoard.h"
#include "GameTypes.h"
#include <string>
#include <iostream>

class Player {
public:
    Player(const std::string& name) : name(name) {}
    virtual ~Player() = default;
    
    virtual void placeShip(const std::string& name, int size) = 0;
    virtual AttackResult attack(GameBoard& enemyBoard) = 0;
    virtual AttackResult attackTurn(GameBoard& enemyBoard) = 0;
    virtual GameBoard& getBoard() = 0;
    virtual GameBoard& getHitBoard() = 0;
    virtual void setBoard(const GameBoard& newBoard) {
        std::cerr << "setBoard not implemented for this player type." << std::endl;
    }
    std::string getName() const { return name; }

protected:
    std::string name;
};

#endif 