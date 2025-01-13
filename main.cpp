#include "Game.h"
#include "Human.h"
#include "AI.h"
#include <iostream>

int main() {
    std::cout << "Welcome to Battleships!" << std::endl;

    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    srand(time(nullptr));

    Human player(playerName);
    Human computer("Remote Player");

    Game game(player, computer);
    game.startNetworkGame();

    return 0;
}
