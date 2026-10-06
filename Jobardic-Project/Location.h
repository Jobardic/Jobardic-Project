#pragma once
#include <string>
#include <vector>

class Location
{
	

public:

	Location(std::string name,std::string description);
	Location(std::string name, std::string description, std::vector<Location*> connectedLocations);
	std::string getName();
	std::string getDescription();
	std::vector<std::string> getConnectedLocationNames();
	std::vector<Location*> getConnectedLocations();
	void addConnectedLocation(Location* location);
	bool isNearbyLocation(Location* location);

	//For Testing Only
	void printConnectedLocationNames();
private:
	std::string name;
	std::string description;
	std::vector<Location*> connectedLocations;

};

