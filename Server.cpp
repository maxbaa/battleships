#include "Server.h"
#include <iostream>

using boost::asio::ip::tcp;

Server::Server()
    : socket(ioContext),
    acceptor(ioContext, tcp::endpoint(tcp::v4(), 12345)) {}

void Server::start() {
    try {
        std::cout << "Waiting for connection..." << std::endl;
        acceptor.accept(socket);
        std::cout << "Connected with player!" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}

boost::asio::ip::tcp::socket& Server::getSocket() {
    return socket;
}