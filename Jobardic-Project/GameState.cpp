#include "GameStates.h"
#include "GameState.h"
#include <string>
#include <iostream>
#include "InputHandler.h"


GameStates GameState::gameStateTest(std::string userInput) {

	GameStates gameState = GameStates::Null;
	do {

		if (userInput == "restart") {

			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m   \033[40m \033[41m   \033[40m   \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m   \033[41m   \033[40m \033[41m  \n";
			//                     w                           w             a     a            r      r              n                        n           i     i             n                        n            g     g               !     !                                    
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m  \033[41m \033[40m \033[41m \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m  \n";
			//                     w                           w            a                       a            r                       r           n                        n            i     i             n                        n           g                         g            !     !  
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m  \033[40m \033[41m \033[40m  \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m  \n";
			//                     w                           w            a                       a            r     r             n                       n             i     i             n                       n            g                         g            !     !  
			std::cout << "\033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m     \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m  \033[40m \033[41m  \n";
			//                     w                                           w            a     a              r                       r           n                        n            i     i             n                        n           g                        g             !     !  
			std::cout << " you are about to restart y/n?";

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