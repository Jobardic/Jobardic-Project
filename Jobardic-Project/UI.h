#pragma once

#include <string>
#include "InputPrompts.h"
#include "StoryEvent.h"
#include "Commands.h"
#include<iostream>

class UI {

public:
	static void displayOutput(StoryEvent);
	static Commands parseUserInput(std::string userInput);
	//std::string getInputPrompt(std::string userInput);

};



/*
static displayOutput(event) - prints formatted event to console

static string getUserInput() - returns user input to caller after removing leading & trailing white space and changing all alphabetic chars to lower case

static string getUserInput(string inputPrompt) - outputs a formatted inputPrompt
*/