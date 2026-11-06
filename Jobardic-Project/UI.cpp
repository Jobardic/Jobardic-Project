#include "InputPrompts.h"
#include "InputChoice.h"
#include "Location.h"
#include "StoryEvent.h"
#include "Commands.h"
#include<algorithm>
#include<string>
#include<iostream>
#include<cctype>



void displayOutput(StoryEvent* storyEvent) {
	std::cout << storyEvent->getDescription() << "\n";
	int numberOfPrompts = storyEvent->getInputPrompt()->getNumberOfPrompts();
	for (int i = 0; i < numberOfPrompts; i++) {
		std::cout << storyEvent->getInputPrompt()->getChoice(i) << "\n";
	}
}

Commands parseUserInput(std::string userInput) {
	
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