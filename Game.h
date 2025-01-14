#ifndef GAME_H
#define GAME_H

#include "Human.h"
#include "AI.h"
#include "GameTypes.h"
#include <boost/asio.hpp>

enum GameMode
{
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI,
    AI_VS_AI,
    MULTIPLAYER
};

class Game {
public:
    Game(Player& player1, Player& player2, GameMode mode);
    void play();
    void startNetworkGame();
    void networkPlay(boost::asio::ip::tcp::socket& socket, Player& localPlayer, Player& remotePlayer, bool isServer);
private:
    void handleGameOver();
    bool checkIfGameWonByPlayer(Player& player, Player& opponent);
    void startGameServer();
    void startGameClient(std::string serverAddress);
    void selectStartGameClient();
    void customIpClient();
    bool playersTurn(Player& player, Player& opponent);
    void initShips(Player& player);
    Player& player1;
    Player& player2;
    GameMode mode;
};

#endif