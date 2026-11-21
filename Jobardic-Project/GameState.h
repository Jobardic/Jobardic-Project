#pragma once

#include <string>
#include "GameStates.h"
#include <iostream>

class GameState {

public:
	static GameStates warning(std::string userInput);
	static GameStates quit(std::string userInput);

};