#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
public:
    Game(Player& player1, Player& player2);
    void switchTurn();
    void playTurn(int x, int y);
    bool checkWinner() const;

private:
    Player& player1;
    Player& player2;
    Player* current_turn;
};

#endif