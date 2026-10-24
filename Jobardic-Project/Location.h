#pragma once
#include <string>
#include <vector>
#include "Object.h"

class Location
{
public:
	Location(std::string name,std::string description);
	Location(std::string name, std::string description, std::vector<Object*> locationObjects);
	std::string getName();
	std::string getDescription();
	std::vector<Object*> getLocationObjects();
	void addConnectedLocation(Location* location);
	void addLocationObject(Object* obj);
	void removeLocationObject(int index);
	bool isNearbyLocation(Location* location);

private:
	std::string name;
	std::string description;
	std::vector<Object*> locationObjects;
};

