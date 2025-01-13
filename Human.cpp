#include "Human.h"
#include <iostream>
#include "Ship.h"
#include <cctype>

Human::Human(const std::string &name) : Player(name), board(), hitBoard()
{
    // Initialize the boards
}

void Human::placeShip(const std::string &name, int size)
{
    std::cout << "Placing " << name << " (size " << size << ")" << std::endl;
    while (true)
    {
        std::pair<int, int> coordinates = getCoordinates();
        Orientation orientation = getOrientation();

        if (board.tryPlaceShip(name, size, coordinates.first, coordinates.second, orientation))
        {
            break;
        }
        std::cout << "Invalid ship placement. Please try again." << std::endl;
    }
    board.display("Your board after placing " + name);
}

AttackResult Human::attackTurn(GameBoard &enemyBoard)
{

    board.display("Your board");
    auto res = attack(enemyBoard);
    hitBoard.display("Hitboard");
    return res;
}

AttackResult Human::attack(GameBoard &enemyBoard)
{
    std::pair<int, int> coordinates = getCoordinates();
    AttackResult result;
    result.x = coordinates.first;
    result.y = coordinates.second;
    result.result = enemyBoard.shoot(coordinates.first, coordinates.second);

    if (result.result == ShootResult::INVALID)
    {
        std::cout << "Invalid attack. Please try again." << std::endl;
        return attack(enemyBoard);
    }

    hitBoard.setCell(coordinates.first, coordinates.second, (result.result == ShootResult::HIT || result.result == ShootResult::SUNK) ? CellStates::HIT : CellStates::MISS);
    return result;
}

std::pair<int, int> Human::getCoordinates()
{
    int x, y;
    char xChar;

    while (true)
    {
        std::cout << "Enter coordinates (e.g. A1): ";
        std::cin >> xChar >> y;

        // Convert letter to number (A=0, B=1, etc.)
        x = toupper(xChar) - 'A';
        y = y - 1; // Convert to 0-based index

        if (x >= 0 && x < MAX_X_COORDINATE && y >= 0 && y < MAX_Y_COORDINATE)
        {
            // KEEP THIS LINE due to the way we display the board
            return std::make_pair(y, x);
        }

        std::cout << "Invalid coordinates. Please try again." << std::endl;
    }
}

Orientation Human::getOrientation()
{
    char input;
    while (true)
    {
        std::cout << "Enter orientation (H for horizontal, V for vertical): ";
        std::cin >> input;
        input = toupper(input);

        if (input == 'H')
        {
            return Orientation::HORIZONTAL;
        }
        else if (input == 'V')
        {
            return Orientation::VERTICAL;
        }

        std::cout << "Invalid orientation. Please try again." << std::endl;
    }
}

GameBoard &Human::getBoard()
{
    return board;
}

GameBoard &Human::getHitBoard()
{
    return hitBoard;
}

void Human::setBoard(const GameBoard& newBoard)
{
    board.deleteShips();
    board = newBoard;
}
