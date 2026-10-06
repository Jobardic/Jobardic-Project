#pragma once
#include "Location.h"

class Character
{
public:
	Character(Location* startingLocation);
	void setCurrentLocation(Location* location);
	Location* getCurrentLocation();
private:
	Location* currentLocation;

};

