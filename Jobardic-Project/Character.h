#pragma once
#include "Location.h"

class Character
{
public:
	Character(Location* startingLocation);
	void setCurrentLocation(Location* location);
	Location* getCurrentLocation();
	int getEnergy();
	void decreaseEnergy();
	bool isCharacterExhausted();
private:
	Location* currentLocation;
	int characterEnergy;
	const int MAX_ENERGY = 20;
	const int MIN_ENERGY = 0;
};

