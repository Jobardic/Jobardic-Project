#include "Character.h"
#include "Object.h"
#include "World.h"
#include "Time.h"
#include <string>

Character::Character(World::LOCATION_ENUMS startingLocation) {
	Character::currentLocation = startingLocation;
	Character::inventory = {};
	characterEnergy = START_ENERGY;
	characterFood = START_FOOD;
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

std::string Character::Wait() {
	Time::passTime(WAIT_HOURS);
	changeEnergy(WAIT_HOURS * WAKE_ENERGY_RATE);
	return "You wait for " + std::to_string(WAIT_HOURS) + " hours...";
}

int Character::getFood() {
	return characterFood;
}

int Character::getMaxFood() {
	return MAX_FOOD;
}

void Character::increaseFood(int amount) {
	if (amount > 0) {
		characterFood += amount;

		if (characterFood > MAX_FOOD) {
			characterFood = MAX_FOOD;
		}
	}
}

void Character::removeInventoryObject(int index) {
	if (index >= 0 &&
		index < static_cast<int>(inventory.size())) {
		inventory.erase(inventory.begin() + index);
	}
}
