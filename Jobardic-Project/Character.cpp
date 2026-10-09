#include "Character.h"
#include <iostream>

Character::Character(Location* startingLocation) {
	currentLocation = startingLocation;
	characterEnergy = MAX_ENERGY;
}

Location* Character::getCurrentLocation() {
	return currentLocation;
}
void Character::setCurrentLocation(Location* location) {
	currentLocation = location;
}

int Character::getEnergy() {
	return characterEnergy;
}

int Character::getMaxEnergy() {
	return MAX_ENERGY;
}

void Character::decreaseEnergy() {
	if (characterEnergy > MIN_ENERGY) {
		characterEnergy--;
	}
}

bool Character::isCharacterExhausted() {
	return characterEnergy <= MIN_ENERGY; // returns true if 0 or less
}