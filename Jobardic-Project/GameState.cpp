#include "GameStates.h"
#include <string>
#include <iostream>
#include "InputHandler.h"


GameStates warning(std::string userInput) {

	GameStates gameState = GameStates::Null;
	do {

		if (userInput == "restart") {

			std::cout << "warning you are about to restart y/n?";

			if (InputHandler::getAndCompareUserInput("yes")) {
				gameState = GameStates::Restart;
			}
			else if (InputHandler::getAndCompareUserInput("no")) {
				gameState = GameStates::Running;
			}
			else {
				std::cout << "Please chooose a valid option.";
			}

		}

		else if (userInput == "quit") {

			std::cout << "warning you are about to quit y/n?";
			if (InputHandler::getAndCompareUserInput("yes")) {
				gameState = GameStates::Quit;
			}
			else if (InputHandler::getAndCompareUserInput("no")) {
				gameState = GameStates::Running;
			}
			else {
				std::cout << "Please chooose a valid option.";
			}

		}

	} while (gameState == GameStates::Null);

	return gameState;
}