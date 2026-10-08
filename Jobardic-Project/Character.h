#pragma once
#include "Location.h"
#include "Object.h"

class Character
{
public:
	Character(Location* startingLocation);
	void setCurrentLocation(Location* location);
	Location* getCurrentLocation();
	std::vector<Object*> getInventory();
	void pickUpObject(Object* item);
private:
	Location* currentLocation;
	std::vector<Object*> inventory;
};

