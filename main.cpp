#include "Game.h"
#include "Human.h"
#include "AI.h"
#include "InputHandler.h"
#include <iostream>



void startGame(GameMode mode)
{
    std::cout << "Starting game..." << std::endl;

    switch (mode)
    {
    case HUMAN_VS_HUMAN:
    {
        std::string player1Name;
        std::cout << "Enter name for Player1: ";
        std::getline(std::cin, player1Name);

        std::string player2Name;
        std::cout << "Enter name for Player2: ";
        std::getline(std::cin, player2Name);

        Human player1(player1Name);
        Human player2(player2Name);
        Game game(player1, player2, mode);
        game.play();
        break;
    }
    case HUMAN_VS_AI:
    {
        Human player("Player");
        AI computer("Computer");
        Game game(player, computer, mode);
        game.play();
        break;
    }
    case AI_VS_AI:
    {
        AI player1("AI 1");
        AI player2("AI 2");
        Game game(player1, player2, mode);
        game.play();
        break;
    }
    case MULTIPLAYER:
    {
        std::string playerName;
        std::cout << "Enter your name: ";
        std::getline(std::cin, playerName);

        srand(time(nullptr));

        Human player(playerName);
        Human computer("Remote Player");

        Game game(player, computer, mode);
        game.startNetworkGame();
    }
    }
}

void selectGameMode()
{
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Human vs Human", []()
         { startGame(GameMode::HUMAN_VS_HUMAN); }},
        {"Human vs AI", []()
         { startGame(GameMode::HUMAN_VS_AI); }},
        {"AI vs AI", []()
         { startGame(GameMode::AI_VS_AI); }},
        {"Mulitplayer", []()
         { startGame(GameMode::MULTIPLAYER); }}};

    InputHandler inputHandler(options);
    inputHandler.start();
}

void showOptions()
{
    std::cout << "Showing options..." << std::endl;
    // Implement options logic here
}

void exitGame()
{
    std::cout << "Exiting game..." << std::endl;
    exit(0);
}

void mainMenu()
{
    std::vector<std::pair<std::string, std::function<void()>>> options = {
        {"Start Game", selectGameMode},
        {"Options", showOptions},
        {"Exit", exitGame}};

    InputHandler inputHandler(options);
    inputHandler.start();
}

int main()
{
    std::cout << "Welcome to Battleships!" << std::endl;
    while (true)
    {
        mainMenu();
    }

    return 0;
}
