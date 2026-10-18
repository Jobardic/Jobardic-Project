#include "Character.h"
#include "Object.h"
#include "Time.h"
#include <string>

Character::Character(Location* startingLocation, int startingEnergy) {
	Character::currentLocation = startingLocation;
	Character::inventory = {};
	characterEnergy = startingEnergy;
}

Location* Character::getCurrentLocation() {
	return currentLocation;
}

std::vector<Object*> Character::getInventory() {
	return inventory;
}

void Character::pickUpObject(Object* item) {
	Character::inventory.push_back(item);
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

void Character::changeEnergy(int amount) {
	characterEnergy += amount;
	if (characterEnergy > MAX_ENERGY) {
		characterEnergy = MAX_ENERGY;
	}
	if (characterEnergy < MIN_ENERGY) {
		characterEnergy = MIN_ENERGY;
	}
}

bool Character::isCharacterExhausted() {
	return characterEnergy <= MIN_ENERGY; // returns true if 0 or less
}

std::string Character::Sleep(bool canSleep) {
	if (!canSleep) {
		return "You can't sleep here.";
	}
	else {
		Time::passTime(SLEEP_HOURS);
		changeEnergy(SLEEP_HOURS * SLEEP_ENERGY_RATE); 
		return "You sleep for " + std::to_string(SLEEP_HOURS) + " hours and wake up feeling refreshed.";
	}
}