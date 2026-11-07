#include "InputHandler.h"

std::string InputHandler::normalizeInput(std::string input) {
    //Erase white spaces in the beginning 
    for (int i = 0; i < input.length(); i++) {
        if (std::isspace(input[i])) {
            input.erase(i, 1);
            i--;
        }
        else {
            break;
        }
    }
    //Erase white spaces in the end
    for (int i = input.length() - 1; i >= 0; i--) {
        if (std::isspace(input[i])) {
            input.erase(i, 1);
        }
        else {
            break;
        }
    }
    //remove capitalization
    for (int i = 0; i < input.length(); i++) {
        input[i] = std::tolower(input[i]);
    }

    return input;
}

std::string InputHandler::getUserInput() {
    std::string userInput;
    std::getline(std::cin, userInput);
    return normalizeInput(userInput);
}

bool InputHandler::getAndCompareUserInput(std::string comparison) {
    std::string userInput = getUserInput();
    return (userInput == normalizeInput(comparison));
}

void InputHandler::waitForUser() {
    std::string any_input;
    std::cout << "Press Enter to continue...";
    std::getline(std::cin, any_input);
}

