#include "Game.h"
#include <iostream>

Game::Game(Player& p1, Player& p2) : player1(p1), player2(p2) {}

void Game::play() {
    while (true) {
        playersTurn(player1, player2);
        playersTurn(player2, player1);
    }
}

void Game::playersTurn(Player& player, Player& opponent) {
    AttackResult result = player.attackTurn(opponent.getBoard());
    // Handle result...
}

