#pragma once
#include <string>
#include <vector>
#include "Object.h"

class Location
{
public:
	Location(std::string name,std::string description);
	Location(std::string name, std::string description, std::vector<Location*> connectedLocations, std::vector<Object*> locationObjects);
	std::string getName();
	std::string getDescription();
	std::vector<std::string> getConnectedLocationNames();
	std::vector<Location*> getConnectedLocations();
	std::vector<Object*> getLocationObjects();
	void addConnectedLocation(Location* location);
	void addLocationObject(Object* obj);
	bool isNearbyLocation(Location* location);

	//For Testing Only
	void printConnectedLocationNames();
private:
	std::string name;
	std::string description;
	std::vector<Location*> connectedLocations;
	std::vector<Object*> locationObjects;
};

