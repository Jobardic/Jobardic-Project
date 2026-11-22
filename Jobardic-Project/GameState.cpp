#include "GameStates.h"
#include "GameState.h"
#include <string>
#include <iostream>
#include "InputHandler.h"

#include <windows.h>

GameStates GameState::gameStateTest(std::string userInput) {

	GameStates gameState = GameStates::Null;
	do {


		if (userInput == "restart") {

			system("cls");
			//warning();
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m   \033[40m \033[41m   \033[40m   \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m   \033[41m   \033[40m \033[41m  \n";
			//                     w                           w             a     a            r      r              n                        n           i     i             n                        n            g     g               !     !                                    
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m  \033[41m \033[40m \033[41m \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m  \n";
			//                     w                           w            a                       a            r                       r           n                        n            i     i             n                        n           g                         g            !     !  
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m  \033[40m \033[41m \033[40m  \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m      \033[40m \033[41m  \n";
			//                     w                           w            a                       a            r     r             n                       n             i     i             n                       n            g              g       !     !  
			std::cout << "\033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m     \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m     \n";
			//                     w                                           w            a     a              r                       r           n                        n            i     i             n                        n           g                        g             !     !  
			std::cout << "\033[41m   \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m    \033[41m  \033[40m \033[41m  \n\033[40m \033[0m \n";
			//                       w                        w           a                         a          r                       r           n                        n            i     i              n                        n            g     g               !     !  
			std::cout << "\033[1m\033[4mYou are about to restart.\nAre you sure you want to proceed?\n\nyes\nno\n\n\033[0m";

			if (InputHandler::getAndCompareUserInput("yes")) {
				gameState = GameStates::Restart;
				OutputDebugStringA("boink");
			}
			else if (InputHandler::getAndCompareUserInput("no")) {
				gameState = GameStates::Running;
				OutputDebugStringA("boink");
			}
			else {
				std::cout << "Please chooose a valid option.\n";
			}

		}

		else if (userInput == "quit") {

			system("cls");
			//warning();
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m   \033[40m \033[41m   \033[40m   \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m   \033[41m   \033[40m \033[41m  \n";
			//                     w                           w             a     a            r      r              n                        n           i     i             n                        n            g     g               !     !                                    
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m  \033[41m \033[40m \033[41m \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m  \n";
			//                     w                           w            a                       a            r                       r           n                        n            i     i             n                        n           g                         g            !     !  
			std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m  \033[40m \033[41m \033[40m  \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m      \033[40m \033[41m  \n";
			//                     w                           w            a                       a            r     r             n                       n             i     i             n                       n            g              g       !     !  
			std::cout << "\033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m     \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m     \n";
			//                     w                                           w            a     a              r                       r           n                        n            i     i             n                        n           g                        g             !     !  
			std::cout << "\033[41m   \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m    \033[41m  \033[40m \033[41m  \n\033[40m \033[0m \n";
			//                       w                        w           a                         a          r                       r           n                        n            i     i              n                        n            g     g               !     !  
			std::cout << "\033[1m\033[4mYou are about to restart.\nAre you sure you want to proceed?\n\nyes\nno\n\n\033[0m";
			if (InputHandler::getAndCompareUserInput("yes")) {
				gameState = GameStates::Quit;
				OutputDebugStringA("boink");
			}
			else if (InputHandler::getAndCompareUserInput("no")) {
				gameState = GameStates::Running;
				OutputDebugStringA("boink");
			}
			else {
				std::cout << "Please chooose a valid option.\n";
			}

		}

	} while (gameState == GameStates::Null);

	return gameState;
}

void warning() {
	std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m   \033[40m \033[41m   \033[40m   \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m   \033[41m   \033[40m \033[41m  \n";
	//                     w                           w             a     a            r      r              n                        n           i     i             n                        n            g     g               !     !                                    
	std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m  \033[41m \033[40m \033[41m \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m  \n";
	//                     w                           w            a                       a            r                       r           n                        n            i     i             n                        n           g                         g            !     !  
	std::cout << "\033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m  \033[40m \033[41m \033[40m  \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m  \033[41m \033[40m \033[41m      \033[40m \033[41m  \n";
	//                     w                           w            a                       a            r     r             n                       n             i     i             n                       n            g              g       !     !  
	std::cout << "\033[41m  \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m     \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m  \033[40m \033[41m \033[40m \033[41m  \033[40m  \033[41m     \n";
	//                     w                                           w            a     a              r                       r           n                        n            i     i             n                        n           g                        g             !     !  
	std::cout << "\033[41m   \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m   \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m \033[40m \033[41m  \033[40m \033[41m \033[40m   \033[41m  \033[40m \033[41m  \033[40m \033[41m  \033[40m    \033[41m  \033[40m \033[41m  \n\033[40m \033[0m \n";
	//                       w                        w           a                         a          r                       r           n                        n            i     i              n                        n            g     g               !     !  
}