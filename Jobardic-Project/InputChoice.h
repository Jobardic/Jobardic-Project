#pragma once

#include <string>

class InputChoice {

public:
	InputChoice(std::string description);
	std::string getDescription();

private: 
	std::string description;

};


/*
DESIGN
InputChoice(sting desc.) class - new

 stores and returns a desrciption

getters

static string getDescription() - returns descriptiom
*/