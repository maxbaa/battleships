#include "Game.h"
#include <iostream>
#include "Ship.h"

Game::Game(Player& p1, Player& p2) : player1(p1), player2(p2) {}

void Game::play() {
    std::cout << "Welcome to Battleships!" << std::endl;
    std::cout << player1.getName() << " vs " << player2.getName() << std::endl;
    std::cout << "Let's get started by placing our ships" << std::endl;
    initShips(player1);
    initShips(player2);
    while (true) {
        playersTurn(player1, player2);
        playersTurn(player2, player1);
    }
}

void Game::playersTurn(Player& player, Player& opponent) {
    
    AttackResult result = player.attackTurn(opponent.getBoard());
    
    bool allSunk = true;
    // Check if the game is over
    for(auto ship : opponent.getBoard().getShips()) {
        if(!ship->isSunk()) {
            allSunk = false;
            break;
        }
    }
    
    if(allSunk) {
        std::cout << player.getName() << " wins!" << std::endl;
        player.getBoard().display("Your board");
        opponent.getBoard().display("Opponent board");
        std::cout << player.getName() << " wins!" << std::endl;
        std::cout << "Thank you for playing <3" << std::endl;



        exit(0);
    }
}


void Game::initShips(Player& player) {
    player.placeShip("Aircraft Carrier", 5);
    player.placeShip("Battleship", 4);
    player.placeShip("Submarine", 3);
    player.placeShip("Cruiser", 3);
    player.placeShip("Destroyer", 2);
}
