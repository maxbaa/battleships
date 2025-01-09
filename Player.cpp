#include "Player.h"
#include <iostream>
#include "Ship.h"
#include <cctype>

Player::Player(const std::string& name)
{
    this->name = name;
    this->state = GameState::PLACING_SHIPS;
    this->gameMode = GameMode::HUMAN_VS_AI;
    this->board = GameBoard();
    this->ships = std::vector<Ship>();
}

void Player::placeShip(const std::string& name, int size) {
    while (true) {
        std::cout << "Platzierung des Schiffs: " << name
            << " (Groesse: " << size << ")" << std::endl;
        
        std::pair<int, int> coordinates = getCoordinates();
        Orientation orientation = getOrientation();

        Ship* newShip = board.tryPlaceShip(name, size, coordinates.first, coordinates.second, orientation);
        if (newShip == nullptr) {
            std::cout << "Ungueltige Platzierung. Bitte erneut versuchen." << std::endl;
            continue;
        }

        std::cout << name << " platziert!" << std::endl;
        board.display();
        break;
    }
}


void Player::initializeShips() {
    placeShip("Schlachtschiff", 5);

    for (int i = 0; i < 1; ++i) {
        placeShip("Kreuzer", 4);
    }
    for (int i = 0; i < 0; ++i) {
        placeShip("Zerstoerer", 3);
    }
    for (int i = 0; i < 0; ++i) {
        placeShip("U-Boot", 2);
    }
}

void Player::attack() {
    std::pair<int, int> coordinates = getCoordinates();
    ShootResult result = board.shoot(coordinates.first, coordinates.second);
    std::cout << "ShootResult: " << (int)result << std::endl;
    if (result == ShootResult::HIT) {
        std::cout << "Treffer!" << std::endl;
    }
    else if (result == ShootResult::SUNK) {
        std::cout << "Treffer! Schiff gesunken!" << std::endl;
    }
    else if (result == ShootResult::MISS) {
        std::cout << "Verfehlt!" << std::endl;
    }
}

std::pair<int, int> Player::getCoordinates() {
    int x, y;
    char xChar;

    while (true) {
        std::cout << "Geben Sie die Koordinate ein (z.B. A1): " << std::endl;

        std::cin >> xChar >> y;
        x = toupper(xChar) - 'A';
        y = y - 1;
        std::cout << "GetCoordinates: x: " << x << " y: " << y << std::endl;

        if (x < 0 || x >= MAX_X_COORDINATE || y < 0 || y >= MAX_Y_COORDINATE) {
            std::cout << "Ungueltige Koordinate. Bitte erneut versuchen." << std::endl;
            continue;
        }

        // y, x because of the way the board is displayed
        return std::make_pair(y, x);
    }
}

Orientation Player::getOrientation() {
    char direction;
    std::cout << "Horizontale (H) oder Vertikale (V) Ausrichtung: ";
    std::cin >> direction;
    return (direction == 'H' || direction == 'h') ? Orientation::HORIZONTAL : Orientation::VERTICAL;
}

void Player::gameLoop() {
    while (state != GameState::GAME_OVER) {
        if (state == GameState::PLACING_SHIPS) {
            initializeShips();
            state = GameState::WAITING_FOR_ATTACK;
        }
        else if (state == GameState::ATTACKING) {
            board.display();
            attack();
            state = GameState::WAITING_FOR_ATTACK;
        }
        else if (state == GameState::WAITING_FOR_ATTACK) {
            std::cout << "Warten auf Gegner..." << std::endl;

            if (gameMode == GameMode::HUMAN_VS_HUMAN) {
                std::cout << "Gegner hat geschossen. Druecken Sie Enter, um zu antworten." << std::endl;
                std::cin.ignore();
                state = GameState::ATTACKING;
            }
            else if (gameMode == GameMode::HUMAN_VS_AI) {
                std::cout << "Gegner hat geschossen. Druecken Sie Enter, um zu antworten." << std::endl;
                std::cin.ignore();
                state = GameState::ATTACKING;
            }
        }
    }
}


