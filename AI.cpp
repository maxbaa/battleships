#include "AI.h"
#include <iostream>
#include "Ship.h"
#include <cctype>

AI::AI(const std::string &name) : Player(name), board(), hitBoard()
{
    // Initialize the boards
}

void AI::placeShip(const std::string& name, int size)
{
    while (true) {
        std::pair<int, int> coordinates = getRandomCoordinates();
        Orientation orientation = getRandomOrientation();
        
        if (board.tryPlaceShip(name, size, coordinates.first, coordinates.second, orientation)) {
            break;
        }
    }
}

AttackResult AI::attackTurn(GameBoard& enemyBoard)
{
    return attack(enemyBoard);
}

AttackResult AI::attack(GameBoard& enemyBoard)
{
    std::pair<int, int> coordinates = getRandomCoordinates();
    AttackResult result;
    result.x = coordinates.first;
    result.y = coordinates.second;
    result.result = enemyBoard.shoot(coordinates.first, coordinates.second);
    return result;
}

std::pair<int, int> AI::getRandomCoordinates()
{
    int x = rand() % MAX_X_COORDINATE;
    int y = rand() % MAX_Y_COORDINATE;
    return std::make_pair(x, y);
}

Orientation AI::getRandomOrientation()
{
    int orientation = rand() % 2;
    return static_cast<Orientation>(orientation);
}

GameBoard& AI::getBoard()
{
    return board;
}

GameBoard& AI::getHitBoard()
{
    return hitBoard;
}

