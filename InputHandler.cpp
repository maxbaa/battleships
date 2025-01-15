#include "InputHandler.h"

InputHandler::InputHandler(const std::vector<std::pair<std::string, std::function<void()>>>& options)
    : options(options), currentSelection(0) {}

void InputHandler::handleKeyPress() {
    char key;
    while (true) {
        key = std::cin.get();
        if (key >= '1' && key <= '9') {
            size_t index = key - '1';
            if (index < options.size()) {
                currentSelection = index;
                std::cout << "You selected: " << options[currentSelection].first << std::endl;
                options[currentSelection].second();
                break;
            }
        }
        render();
    }
}

void InputHandler::render() {
    std::cout << "\033[2J\033[1;1H"; // Clear console
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ". " << options[i].first << std::endl;
    }
}

void InputHandler::start() {
    render();
    handleKeyPress();
}

