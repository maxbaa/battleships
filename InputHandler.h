#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <vector>
#include <functional>

class InputHandler {
public:
    InputHandler(const std::vector<std::pair<std::string, std::function<void()>>>& options);
    void start();
private:
    std::vector<std::pair<std::string, std::function<void()>>> options;
    size_t currentSelection;
    void handleKeyPress();
    void render();
};

#endif // INPUTHANDLER_H
