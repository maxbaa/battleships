#include "InputHandler.h"

InputHandler::InputHandler(const std::vector<std::pair<std::string, std::function<void()>>>& options)
    : options(options), currentSelection(0) {}

void InputHandler::handleKeyPress() {
    char key;
    while (true) {
        key = getch();
        if (key == '\033') { // Arrow keys are preceded by an escape sequence
            getch(); // Skip the '[' character
            switch (getch()) {
                case 'A': // Up arrow key
                    currentSelection = (currentSelection > 0) ? currentSelection - 1 : options.size() - 1;
                    break;
                case 'B': // Down arrow key
                    currentSelection = (currentSelection < options.size() - 1) ? currentSelection + 1 : 0;
                    break;
            }
        } else if (key == '\n') { // Enter key
            std::cout << "You selected: " << options[currentSelection].first << std::endl;
            if (currentSelection < options.size()) {
                options[currentSelection].second();
            }
            break;
        }
        render();
    }
}

void InputHandler::render() {
    std::cout << "\033[2J\033[1;1H"; // Clear console
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == currentSelection) {
            std::cout << "> " << options[i].first << std::endl;
        } else {
            std::cout << "  " << options[i].first << std::endl;
        }
    }
}

void InputHandler::start() {
    render();
    handleKeyPress();
}

char InputHandler::getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

