#pragma once
#include <string>
#include <vector>
#include "Object.h"

class Location
{
public:
	Location(std::string name, std::string description, bool allowsSleep, bool isIndoors); // two new parameters for if the player can sleep here, and if the location is indoors
	Location(std::string name, std::string description, std::vector<Object*> locationObjects);
	std::string getName();
	std::string getDescription();
	std::vector<Object*> getLocationObjects();
	void addLocationObject(Object* obj);
	void removeLocationObject(std::string objectName);
	bool canPlayerSleepHere();  // Getter for allowsSleep
	bool getIndoors();			// Getter for indoors
	Object* findLocationObject(std::string objectName);
	bool hasObject(std::string objectName);

private:
	std::string name;
	std::string description;
	std::vector<Object*> locationObjects;
	bool allowsSleep = false; // by default you shouldn't be able to sleep
	bool indoors;
};

/*
location object:
	new class variable: [bool] allowsSleep
	new constructor that accepts argument for allowsSleep
	set this to true for home bedroom when created
	bool canPlayerSleepHere() - getter function for allowsSleep
*/
