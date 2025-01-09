#include "Human.h"
#include <iostream>
#include "Ship.h"
#include <cctype>

Human::Human(const std::string &name) : Player(name), board(), hitBoard()
{
    // Initialize the boards
}

void Human::placeShip(const std::string& name, int size)
{
    while (true) {
        std::pair<int, int> coordinates = getCoordinates();
        Orientation orientation = getOrientation();
        
        if (board.tryPlaceShip(name, size, coordinates.first, coordinates.second, orientation)) {
            break;
        }
        std::cout << "Invalid ship placement. Please try again." << std::endl;
    }
}

AttackResult Human::attackTurn(GameBoard& enemyBoard)
{
    return attack(enemyBoard);
}

AttackResult Human::attack(GameBoard& enemyBoard)
{
    std::pair<int, int> coordinates = getCoordinates();
    AttackResult result;
    result.x = coordinates.first;
    result.y = coordinates.second;
    result.result = enemyBoard.shoot(coordinates.first, coordinates.second);
    return result;
}

std::pair<int, int> Human::getCoordinates()
{
    int x, y;
    char xChar;

    while (true) {
        std::cout << "Enter coordinates (e.g. A1): ";
        std::cin >> xChar >> y;
        
        // Convert letter to number (A=0, B=1, etc.)
        x = toupper(xChar) - 'A';
        y = y - 1; // Convert to 0-based index
        
        if (x >= 0 && x < MAX_X_COORDINATE && y >= 0 && y < MAX_Y_COORDINATE) {
            return std::make_pair(x, y);
        }
        
        std::cout << "Invalid coordinates. Please try again." << std::endl;
    }
}

Orientation Human::getOrientation()
{
    char input;
    while (true) {
        std::cout << "Enter orientation (H for horizontal, V for vertical): ";
        std::cin >> input;
        input = toupper(input);
        
        if (input == 'H') {
            return Orientation::HORIZONTAL;
        } else if (input == 'V') {
            return Orientation::VERTICAL;
        }
        
        std::cout << "Invalid orientation. Please try again." << std::endl;
    }
}

GameBoard& Human::getBoard()
{
    return board;
}

GameBoard& Human::getHitBoard()
{
    return hitBoard;
}

