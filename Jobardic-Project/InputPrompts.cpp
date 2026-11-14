#include "InputPrompts.h"
#include "InputChoice.h"
#include<string>

InputPrompts::InputPrompts(std::vector<InputChoice*> inputChoices) {
	InputPrompts::inputChoices = inputChoices;
}

std::string InputPrompts::getChoice(int choice) {
	std::string a = inputChoices.at(choice)->getDescription();
	return a;
}

int InputPrompts::getNumberOfPrompts() {
	int numberOfPrompts = inputChoices.size();
	return numberOfPrompts;
}