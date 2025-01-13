#ifndef NETWORKTRANSFER_H
#define NETWORKTRANSFER_H

#include <boost/asio.hpp>
#include "GameTypes.h"
#include <vector>
#include "GameBoard.h"
#include "GameConfig.h"
#include "Ship.h"

class NetworkTransfer {
public:
	void sendGameBoard(GameBoard gameBoard, boost::asio::ip::tcp::socket& socket);
	GameBoard receiveGameBoard(boost::asio::ip::tcp::socket& socket);
};

#endif