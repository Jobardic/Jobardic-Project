#pragma once

#include<vector>
#include<string>
#include "InputChoice.h"

class InputPrompts {

public:
	InputPrompts(std::vector<InputChoice*> inputChoices);
	std::string getChoice(int choiceIndex);
	int getNumberOfPrompts();

private:
	std::vector<InputChoice*> inputChoices;
};

/*
InputPrompts(inputChoices(variable)) class - new

stores and returns a number of input choices

getters

static string getChoice(int) - returns a choice
*/