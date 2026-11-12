#include "InputPrompts.h"
#include "InputChoice.h"
#include "Location.h"
#include "StoryEvent.h"
#include "Commands.h"
#include "UI.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>




void UI::displayOutput(StoryEvent* storyEvent) {
	std::cout << storyEvent->getDescription() << "\n";
	InputPrompts* prompts = storyEvent->getInputPrompt();
	int numberOfPrompts = prompts->getNumberOfPrompts();
	for (int i = 0; i < numberOfPrompts; i++) {
		std::cout << storyEvent->getInputPrompt()->getChoice(i) << "\n";
	}
}

Commands UI::parseUserInput(std::string userInput) {
	
	Commands input = Commands::Null;
	userInput.erase(remove_if(userInput.begin(), userInput.end(), [](unsigned char ch) {
		return isspace(ch);
		}), userInput.end());

	if (userInput == "==>" || userInput == "=>" || userInput == "continue" || userInput == "keepgoing") {
		input = Commands::Progress;
	}

	else {
		input = Commands::Null;
	}

	return input;
}

//std::string getInputPrompt(string userInput) {

//}