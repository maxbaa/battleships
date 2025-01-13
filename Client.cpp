#include "Client.h"
#include "Human.h"
#include "Game.h"
#include <iostream>

using boost::asio::ip::tcp;

Client::Client() : socket(io_context) {}

void Client::connect(const std::string& serverAddress, int port) {
    try {
        tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(serverAddress, std::to_string(port)));
        std::cout << "Connected with player!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
    }
}

boost::asio::ip::tcp::socket& Client::getSocket() {
    return socket;
}