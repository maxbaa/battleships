#include "Player.h"
#include <iostream>
#include "Ship.h"
#include <cctype>

Player::Player(const std::string& name)
{
    this->name = name;
    initializeBoards();
    printPlayersBoard();
    initializeShips();
}

void Player::placeShip(Ship& ship) {
    char startXChar;
    int startY;
    char direction;
    bool valid = false;

    while (!valid) {
        std::cout << "Platzierung des Schiffs: " << ship.getName()
            << " (Groesse: " << ship.getSize() << ")" << std::endl;
        std::cout << "Geben Sie die Startkoordinate ein (z.B. A1): ";
        std::cin >> startXChar >> startY;
        std::cout << "Horizontale (H) oder Vertikale (V) Ausrichtung: ";
        std::cin >> direction;

        startXChar = toupper(startXChar);
        int startX = startXChar - 'A';
        startY -= 1;

        if (startX < 0 || startX >= MAX_X_COORDINATE || startY < 0 || startY >= MAX_Y_COORDINATE) {
            std::cout << "Ungueltige Koordinaten. Bitte erneut versuchen." << std::endl;
            continue;
        }

        if (direction != 'H' && direction != 'V' && direction != 'h' && direction != 'v') {
            std::cout << "Ungueltige Eingabe fuer die Ausrichtung." << std::endl;
            continue;
        }

        valid = true;

        for (int i = 0; i < ship.getSize(); ++i) {
            int checkX = startX;
            int checkY = startY;

            if (direction == 'V' || direction == 'v') {
                checkY += i;
            }
            else {
                checkX += i;
            }

            if (checkX >= MAX_X_COORDINATE || checkY >= MAX_Y_COORDINATE || playersBoard[checkY][checkX] != "~") {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Ungueltige Platzierung. Bitte erneut versuchen." << std::endl;
            continue;
        }

        for (int i = 0; i < ship.getSize(); ++i) {
            int placeX = startX;
            int placeY = startY;

            if (direction == 'V' || direction == 'v') {
                placeY += i;
            }
            else {
                placeX += i;
            }

            playersBoard[placeY][placeX] = "S";
            ship.addCoordinates(placeX, placeY);
        }

        std::cout << ship.getName() << " platziert!" << std::endl;
        printPlayersBoard();
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
        ships.emplace_back("Zerstoerer", 3, 0, 0);
        placeShip(ships.back());
    }
    for (int i = 0; i < 4; ++i) {
        ships.emplace_back("U-Boot", 2, 0, 0);
        placeShip(ships.back());
    }
}

void Player::initializeBoards() {
    for (int x = 0; x < MAX_X_COORDINATE; x++) {
        for (int y = 0; y < MAX_Y_COORDINATE; y++) {
            playersBoard[y][x] = "~";
            bombBoard[y][x] = "~";
        }
    }
}

void Player::printPlayersBoard() {
    std::cout << "Seekarte:" << std::endl << "  ";

    for (int y = 0; y < MAX_Y_COORDINATE; y++) {
        std::cout << "|" << static_cast<char>('A' + y);
    }

    std::cout << std::endl;
    for (int x = 0; x < MAX_X_COORDINATE; x++) {
        if (x != 9) {
            std::cout << (x + 1) << " ";
        }
        else {
            std::cout << (x + 1);
        }

        for (int y = 0; y < MAX_Y_COORDINATE; y++) {
            std::cout << "|" << playersBoard[x][y];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
