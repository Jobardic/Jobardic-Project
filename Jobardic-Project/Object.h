#pragma once
#include <string>
#include <vector>

class Object
{
public:
	Object(std::string name, std::string description);
	std::string getName();
	std::string getDescription();
private:
	std::string name;
	std::string description;
};

