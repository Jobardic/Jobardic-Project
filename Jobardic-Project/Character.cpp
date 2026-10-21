#include "Character.h"
#include "Object.h"
#include "World.h"
#include <iostream>

Character::Character(World::LOCATION_ENUMS startingLocation) {
	Character::currentLocation = startingLocation;
	Character::inventory = {};
	characterEnergy = MAX_ENERGY;
}

World::LOCATION_ENUMS Character::getCurrentLocation() {
	return currentLocation;
}

std::vector<Object*> Character::getInventory() {
	return inventory;
}

void Character::pickUpObject(Object* item) {
	Character::inventory.push_back(item);
}

void Character::setCurrentLocation(World::LOCATION_ENUMS location) {
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