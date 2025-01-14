#include "Game.h"
#include <iostream>
#include "Ship.h"
#include "Server.h"
#include "Client.h"
#include "InputHandler.h"

Game::Game(Player &p1, Player &p2, GameMode mode) : player1(p1), player2(p2), mode(mode) {}

void Game::play()
{
    std::cout << "Welcome to Battleships!" << std::endl;
    std::cout << player1.getName() << " vs " << player2.getName() << std::endl;
    std::cout << "Let's get started by placing our ships" << std::endl;
    initShips(player1);
    initShips(player2);

    bool gameIsOver = false;
    while (!gameIsOver)
    {
        gameIsOver = playersTurn(player1, player2);
        if (gameIsOver)
        {
            break;
        }
        gameIsOver = playersTurn(player2, player1);
    }

    // Handle game over
    handleGameOver();
}

void Game::handleGameOver()
{
    std::cout << "Game Over! Press any key to return to main menu" << std::endl;
    
    std::cin.clear(); // clear the error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
    std::cin.get();
}

void Game::startGameServer()
{
    Server server;
    server.start();
    std::cout << "Waiting for a client to connect..." << std::endl;

    std::cout << "Place your ships, Host Player!" << std::endl;
    initShips(player1);

    NetworkTransfer networkTransfer;
    networkTransfer.sendGameBoard(player1.getBoard(), server.getSocket());
    std::cout << "Waiting for Client Player to place ships..." << std::endl;

    int command;
    GameBoard receivedBoard = networkTransfer.receiveGameBoard(server.getSocket());
    player2.setBoard(receivedBoard);

    std::cout << "Both players are ready! Starting the game." << std::endl;

    networkPlay(server.getSocket(), player1, player2, true);
}

void Game::selectStartGameClient()
{
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Connect to localhost", std::bind(&Game::startGameClient, this, "0.0.0.0")},
        {"Enter custom IP", std::bind(&Game::customIpClient, this)},
        {"Back", []() {}}};

    InputHandler inputHandler(options);
    inputHandler.start();
}

void Game::customIpClient()
{
    std::string serverAddress;
    std::cout << "Enter the server address: ";
    std::cin >> serverAddress;
    startGameClient(serverAddress);
}

void Game::startGameClient(std::string serverAddress)
{
    // std::string serverAddress;
    // std::cout << "Enter the server address: ";
    // std::cin >> serverAddress;

    Client client;
    // client.connect("10.130.190.149", 12345);
    try
    {
        client.connect(serverAddress, 12345);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error occurred: " << e.what() << std::endl;
        selectStartGameClient();
        return;
    }

    std::cout << "Place your ships, Client Player!" << std::endl;
    initShips(player1);

    NetworkTransfer networkTransfer;
    networkTransfer.sendGameBoard(player1.getBoard(), client.getSocket());
    std::cout << "Waiting for Host Player to place ships..." << std::endl;

    int command;
    GameBoard receivedBoard = networkTransfer.receiveGameBoard(client.getSocket());
    player2.setBoard(receivedBoard);

    std::cout << "Both players are ready! Starting the game." << std::endl;

    networkPlay(client.getSocket(), player1, player2, false);
}

void Game::startNetworkGame()
{
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Start a server", std::bind(&Game::startGameServer, this)},
        {"Connect to a server", std::bind(&Game::selectStartGameClient, this)}};

    InputHandler inputHandler(options);
    inputHandler.start();
}

void Game::networkPlay(boost::asio::ip::tcp::socket &socket, Player &localPlayer, Player &remotePlayer, bool isServer)
{
    NetworkTransfer networkTransfer;
    bool gameIsOver = false;
    if (isServer)
    {
        while (true)
        {
            gameIsOver = playersTurn(localPlayer, remotePlayer);
            networkTransfer.sendGameBoard(remotePlayer.getBoard(), socket);
            if (gameIsOver)
            {
                break;
            }
            std::cout << "Waiting for the opponent's turn..." << std::endl;
            GameBoard localPlayerBoard = networkTransfer.receiveGameBoard(socket);
            localPlayer.setBoard(localPlayerBoard);
            if (checkIfGameWonByPlayer(remotePlayer, localPlayer))
            {
                break;
            }
        }
    }
    else
    {
        while (true)
        {
            std::cout << "Waiting for the opponent's turn..." << std::endl;
            GameBoard localPlayerBoard = networkTransfer.receiveGameBoard(socket);
            localPlayer.setBoard(localPlayerBoard);
            if (checkIfGameWonByPlayer(remotePlayer, localPlayer))
            {
                break;
            }

            gameIsOver = playersTurn(localPlayer, remotePlayer);
            networkTransfer.sendGameBoard(remotePlayer.getBoard(), socket);

            if (gameIsOver)
            {
                break;
            }
        }
    }

    // Handle game over
    handleGameOver();
}

/**
 * Returns true if the game is over
 */
bool Game::checkIfGameWonByPlayer(Player &player, Player &opponent)
{
    bool allSunk = true;
    // Check if the game is over
    for (auto ship : opponent.getBoard().getShips())
    {
        if (!ship->isSunk())
        {
            allSunk = false;
            break;
        }
    }

    if (allSunk)
    {
        std::cout << player.getName() << " wins!" << std::endl;
        player.getBoard().display("Your board");
        opponent.getBoard().display("Opponent board");
        std::cout << player.getName() << " wins!" << std::endl;
        std::cout << "Thank you for playing <3" << std::endl;
        return true;
    }
    return false;
}

/**
 * Returns true if the game is over
 */
bool Game::playersTurn(Player &player, Player &opponent)
{

    AttackResult result = player.attackTurn(opponent.getBoard());

    return checkIfGameWonByPlayer(player, opponent);
}

void Game::initShips(Player &player)
{
    // player.placeShip("Aircraft Carrier", 5);
    // player.placeShip("Battleship", 4);
    // player.placeShip("Submarine", 3);
    // player.placeShip("Cruiser", 3);
    player.placeShip("Destroyer", 2);
}
