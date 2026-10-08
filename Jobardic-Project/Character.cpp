#include "Character.h"
#include <iostream>

Character::Character(Location* startingLocation) {
	currentLocation = startingLocation;
	characterEnergy = MAX_ENERGY; // Set initial energy to MAX_ENERGY (20)
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

void Character::decreaseEnergy() {
	if (characterEnergy > MIN_ENERGY) {
		characterEnergy--;
	}
}

bool Character::isCharacterExhausted() {
	return characterEnergy <= MIN_ENERGY; // returns true if 0 or less
}

/*character object :

new class variable : energy(private)

set health to 20 in constructor

int getEnergy(0 - 20)

void decreaseEnergy(by 1)*/