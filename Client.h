#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>

class Client {
public:
    Client();
    void connect(const std::string& serverAddress, int port);
    boost::asio::ip::tcp::socket& getSocket();

private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket;
};

#endif