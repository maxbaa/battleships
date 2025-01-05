#include "Player.h"
#include <iostream>
#include "Ship.h"

#include "Player.h"
#include <iostream>
#include "Ship.h"

Player::Player(const std::string& name)
{
    this->name = name;
    this->board = std::vector<std::vector<int>>(MAX_X_COORDINATE, std::vector<int>(MAX_Y_COORDINATE, 0));
    initializeShips();
}

void Player::placeShip(Ship& ship) {
    int startX, startY;
    char direction;
    bool valid = false;

    while (!valid) {
        std::cout << "Platzierung des Schiffs: " << ship.getName()
            << " (Größe: " << ship.getSize() << ")\n";
        std::cout << "Geben Sie die Startkoordinate ein (X Y): ";
        std::cin >> startX >> startY;
        std::cout << "Horizontale (H) oder Vertikale (V) Ausrichtung: ";
        std::cin >> direction;

        if (direction != 'H' && direction != 'V' && direction != 'h' && direction != 'v') {
            std::cout << "Ungültige Eingabe für die Ausrichtung.\n";
            continue;
        }

        valid = true;
        for (int i = 0; i < ship.getSize(); ++i) {
            if (direction == 'H' || direction == 'h') {
                if (startX + i >= MAX_X_COORDINATE || board[startX + i][startY] != 0) {
                    valid = false;
                    break;
                }
            }
            else {
                if (startY + i >= MAX_Y_COORDINATE || board[startX][startY + i] != 0) {
                    valid = false;
                    break;
                }
            }
        }

        if (!valid) {
            std::cout << "Ungültige Platzierung. Bitte erneut versuchen.\n";
            continue;
        }

        for (int i = 0; i < ship.getSize(); ++i) {
            if (direction == 'H' || direction == 'h') {
                board[startX + i][startY] = 1;
            }
            else {
                board[startX][startY + i] = 1;
            }
        }
        std::cout << ship.getName() << " platziert!\n";
    }
}


void Player::initializeShips() {
    ships.emplace_back("Schlachtschiff", 5, 0, 0);
    placeShip(ships.back());

    for (int i = 0; i < 2; ++i) {
        ships.emplace_back("Kreuzer", 4, 0, 0);
        placeShip(ships.back());
    }
    for (int i = 0; i < 3; ++i) {
        ships.emplace_back("Zerstörer", 3, 0, 0);
        placeShip(ships.back());
    }
    for (int i = 0; i < 4; ++i) {
        ships.emplace_back("U-Boot", 2, 0, 0);
        placeShip(ships.back());
    }
}
