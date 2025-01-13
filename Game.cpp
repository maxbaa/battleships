#include "Game.h"
#include <iostream>
#include "Ship.h"
#include "Server.h"
#include "Client.h"

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

void Game::startNetworkGame() {
    int choice;
    std::cout << "Select an option:\n1. Start a server\n2. Connect to a server\nEnter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
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

        networkPlay(server.getSocket(), player1, player2);
    } 
    else if (choice == 2) {
        std::string serverAddress;
        std::cout << "Enter the server address: ";
        //std::cin >> serverAddress;

        Client client;
        client.connect("192.168.178.73", 12345);
        

        std::cout << "Place your ships, Client Player!" << std::endl;
        initShips(player1);

        NetworkTransfer networkTransfer;
        networkTransfer.sendGameBoard(player1.getBoard(), client.getSocket());
        std::cout << "Waiting for Host Player to place ships..." << std::endl;

        int command;
        GameBoard receivedBoard = networkTransfer.receiveGameBoard(client.getSocket());
        player2.setBoard(receivedBoard);

        std::cout << "Both players are ready! Starting the game." << std::endl;

        networkPlay(client.getSocket(), player1, player2);
    } 
    else {
        std::cout << "Invalid choice. Exiting..." << std::endl;
    }
}

void Game::networkPlay(boost::asio::ip::tcp::socket& socket, Player& localPlayer, Player& remotePlayer) {
    NetworkTransfer networkTransfer;
    bool isMyTurn = true;
    while (true) {
        if (isMyTurn) {
            playersTurn(localPlayer, remotePlayer);
            networkTransfer.sendGameBoard(localPlayer.getBoard(), socket);
            isMyTurn = false;
        }
        else {
            std::cout << "Waiting for the opponent's turn..." << std::endl;
            GameBoard updatedBoard = networkTransfer.receiveGameBoard(socket);
            remotePlayer.setBoard(updatedBoard);
            isMyTurn = true;
        }
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
    //player.placeShip("Submarine", 3);
    //player.placeShip("Cruiser", 3);
    //player.placeShip("Destroyer", 2);
}
