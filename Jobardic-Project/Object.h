#pragma once
#include <string>
#include <vector>

class Object
{
public:
	Object(std::string name, std::string description);
	//Object(std::string name, std::string description, std::vector<Location*> connectedLocations);
	std::string getName();
	std::string getDescription();
private:
	std::string name;
	std::string description;
};

