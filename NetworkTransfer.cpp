#include <boost/asio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "NetworkTransfer.h"
#include "Ship.h"

void NetworkTransfer::sendGameBoard(GameBoard gameBoard, boost::asio::ip::tcp::socket& socket)
{
    try {
        std::vector<char> gridBuffer;
        auto grid = gameBoard.getGrid();

        for (int x = 0; x < MAX_X_COORDINATE; ++x) {
            for (int y = 0; y < MAX_Y_COORDINATE; ++y) {
                gridBuffer.push_back(static_cast<char>(grid[x][y]));
            }
        }

        boost::asio::write(socket, boost::asio::buffer(gridBuffer));

        auto ships = gameBoard.getShips();
        std::vector<char> shipBuffer;
        shipBuffer.push_back(static_cast<char>(ships.size()));

        for (const auto ship : ships) {
            std::string name = ship->getName();
            shipBuffer.push_back(static_cast<char>(name.size()));
            shipBuffer.insert(shipBuffer.end(), name.begin(), name.end());
            shipBuffer.push_back(static_cast<char>(ship->getSize()));
            shipBuffer.push_back(static_cast<char>(ship->getHits()));
            shipBuffer.push_back(static_cast<char>(ship->getOrientation()));

            auto coordinates = ship->getCoordinates();
            for (const auto& coord : coordinates) {
                shipBuffer.push_back(static_cast<char>(coord.first));
                shipBuffer.push_back(static_cast<char>(coord.second));
            }

            auto colors = ship->getColors();
            shipBuffer.push_back(static_cast<char>(colors.first));
            shipBuffer.push_back(static_cast<char>(colors.second));
        }
        size_t shipBufferSize = shipBuffer.size();
        boost::asio::write(socket, boost::asio::buffer(&shipBufferSize, sizeof(shipBufferSize)));

        boost::asio::write(socket, boost::asio::buffer(shipBuffer));

        std::cout << "Game board and ships sent successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error sending game board: " << e.what() << std::endl;
    }
}

GameBoard NetworkTransfer::receiveGameBoard(boost::asio::ip::tcp::socket& socket)
{
    try {
        std::vector<char> gridBuffer(MAX_X_COORDINATE * MAX_Y_COORDINATE);
        boost::asio::read(socket, boost::asio::buffer(gridBuffer));

        CellStates tempGrid[MAX_X_COORDINATE][MAX_Y_COORDINATE];

        int index = 0;
        for (int x = 0; x < MAX_X_COORDINATE; ++x) {
            for (int y = 0; y < MAX_Y_COORDINATE; ++y) {
                tempGrid[x][y] = static_cast<CellStates>(gridBuffer[index++]);
            }
        }

        GameBoard gameBoard;
        gameBoard.setGrid(tempGrid);

        size_t shipBufferSize;
        boost::asio::read(socket, boost::asio::buffer(&shipBufferSize, sizeof(shipBufferSize)));

        std::vector<char> shipBuffer(shipBufferSize);
        boost::asio::read(socket, boost::asio::buffer(shipBuffer));

        int shipIndex = 0;
        size_t shipCount = static_cast<size_t>(shipBuffer[shipIndex++]);

        for (size_t i = 0; i < shipCount; ++i) {
            int nameLength = static_cast<int>(shipBuffer[shipIndex++]);
            std::string name(shipBuffer.begin() + shipIndex, shipBuffer.begin() + shipIndex + nameLength);
            shipIndex += nameLength;

            int size = static_cast<int>(shipBuffer[shipIndex++]);
            int hits = static_cast<int>(shipBuffer[shipIndex++]);
            Orientation orientation = static_cast<Orientation>(shipBuffer[shipIndex++]);

            std::vector<std::pair<int, int>> coordinates;
            for (int j = 0; j < size; ++j) {
                int x = static_cast<int>(shipBuffer[shipIndex++]);
                int y = static_cast<int>(shipBuffer[shipIndex++]);
                coordinates.emplace_back(x, y);
            }

            int color1 = static_cast<int>(shipBuffer[shipIndex++]);
            int color2 = static_cast<int>(shipBuffer[shipIndex++]);

            gameBoard.addShip(size, hits, orientation, coordinates[0], name, { color1, color2 });
        }

        return gameBoard;
    }
    catch (const std::exception& e) {
        std::cerr << "Error receiving game board: " << e.what() << std::endl;
        throw;
    }
}
