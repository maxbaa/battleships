#ifndef GAME_H
#define GAME_H

#include "Human.h"
#include "AI.h"
#include "GameTypes.h"
#include <boost/asio.hpp>
class Game {
public:
    Game(Player& player1, Player& player2);
    void play();
    void startNetworkGame();
    void networkPlay(boost::asio::ip::tcp::socket& socket, Player& localPlayer, Player& remotePlayer, bool isServer);
private:
    void playersTurn(Player& player, Player& opponent);
    void initShips(Player& player);
    Player& player1;
    Player& player2;
};

#endif