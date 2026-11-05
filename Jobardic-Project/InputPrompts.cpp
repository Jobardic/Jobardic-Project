#include "InputPrompts.h"
#include "InputChoice.h"
#include<string>

InputPrompts::InputPrompts(std::vector<InputChoice*> inputChoices) {
	InputPrompts::inputChoices = inputChoices;
}

InputChoice* InputPrompts::getChoice(int choice) {
	InputChoice* a = inputChoices.at(choice);
	return a;
}

int InputPrompts::getNumberOfPrompts() {
	int numberOfPrompts = inputChoices.size();
	return numberOfPrompts;
}