#pragma once

#include "Location.h"
#include "InputPrompts.h"
#include<string>

class StoryEvent {

public:
	StoryEvent(std::string desc, Location* location, InputPrompts* inputPrompt);
	std::string getDescription();
	Location* getLocation();
	InputPrompts* getInputPrompt();

private:
	std::string desc;
	Location* location;
	InputPrompts* inputPrompt;

};



//Event(String desc, String location, InputPropmt inputPromt) class - new

// stores and returns a desrciption, locationn and input prompt

//getters

//static string getDescription() - returns description

//static string getLocation() - returns location

//static string getInputPrompt() - returns inputPrompt
