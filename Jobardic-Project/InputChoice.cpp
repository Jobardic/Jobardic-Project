#include "InputChoice.h"
#include<string>

InputChoice::InputChoice(std::string description) {
	InputChoice::description = description;
}

std::string InputChoice::getDescription() {
	return description;
}