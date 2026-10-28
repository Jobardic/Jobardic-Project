#pragma once
#include <string>
#include <vector>
#include "Object.h"

class Location
{
public:
	Location(std::string name,std::string description);
	Location(std::string name, std::string description, std::vector<Object*> locationObjects);
	Location(std::string name, std::string description, bool canSleep);
	std::string getName();
	std::string getDescription();
	std::vector<Object*> getLocationObjects();
	void addConnectedLocation(Location* location);
	void addLocationObject(Object* obj);
	void removeLocationObject(int index);
	bool isNearbyLocation(Location* location);
	bool canPlayerSleepHere();  // Getter for allowsSleep

private:
	std::string name;
	std::string description;
	std::vector<Object*> locationObjects;
	bool allowsSleep = false; // by default you shouldn't be able to sleep
};

/*
location object:
	new class variable: [bool] allowsSleep
	new constructor that accepts argument for allowsSleep
	set this to true for home bedroom when created
	bool canPlayerSleepHere() - getter function for allowsSleep
*/
