#ifndef GAME_H
#define GAME_H

#include "Human.h"
#include "AI.h"
#include "GameTypes.h"

class Game {
public:
    Game(Player& player1, Player& player2);
    void play();

private:
    void playersTurn(Player& player, Player& opponent);
    Player& player1;
    Player& player2;
};

#endif