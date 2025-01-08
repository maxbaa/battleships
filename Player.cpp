#include "Player.h"
#include <iostream>
#include "Ship.h"
#include <cctype>

Player::Player(const std::string& name)
{
    this->name = name;


    initializeShips();  
}

void Player::placeShip(const std::string& name, int size) {
    char startXChar;
    int startY;
    char direction;
    bool valid = false;

    while (!valid) {
        std::cout << "Platzierung des Schiffs: " << name
            << " (Groesse: " << size << ")" << std::endl;
        std::cout << "Geben Sie die Startkoordinate ein (z.B. A1): ";
        std::cin >> startXChar >> startY;
        std::cout << "Horizontale (H) oder Vertikale (V) Ausrichtung: ";
        std::cin >> direction;

        startXChar = toupper(startXChar);
        int startX = startXChar - 'A';
        startY -= 1;
        Orientation orientation = (direction == 'H' || direction == 'h') ? 
            Orientation::HORIZONTAL : Orientation::VERTICAL;



        Ship* newShip = board.tryPlaceShip(name, size, startX, startY, orientation);
        if (newShip == nullptr) {
            std::cout << "Ungueltige Platzierung. Bitte erneut versuchen." << std::endl;
            continue;
        }

        valid = true;
        
        std::cout << name << " platziert!" << std::endl;
        board.display();
    }
}


void Player::initializeShips() {
    placeShip("Schlachtschiff", 5);

    for (int i = 0; i < 2; ++i) {
        placeShip("Kreuzer", 4);
    }
    for (int i = 0; i < 3; ++i) {
        placeShip("Zerstoerer", 3);
    }
    for (int i = 0; i < 4; ++i) {
        placeShip("U-Boot", 2);
    }
}


