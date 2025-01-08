#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <string>

class NetworkConnection {
public:
    NetworkConnection(const std::string& ipAddress, int port);
    ~NetworkConnection();

private:
    std::string ipAddress;
    int port;
    bool isConnected;
};

#endif