#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include "NetworkTransfer.h"

class Server {
public:
    Server();
    void start();
    boost::asio::ip::tcp::socket& Server::getSocket();
private:
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
};

#endif