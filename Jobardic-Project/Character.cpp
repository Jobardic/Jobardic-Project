#include "Character.h"
#include "Object.h"
#include <iostream>

Character::Character(Location* startingLocation) {
	Character::currentLocation = startingLocation;
	Character::inventory = {};
	characterEnergy = MAX_ENERGY;
	characterFood = MAX_FOOD;
	characterThirst = MAX_THIRST;
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

void Character::decreaseEnergy() {
	if (characterEnergy > MIN_ENERGY) {
		characterEnergy--;
	}
}

bool Character::isCharacterExhausted() {
	return characterEnergy <= MIN_ENERGY; // returns true if 0 or less
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

// NEW: Water Well / Thirst functionality

int Character::getThirst() {
	return characterThirst;
}

int Character::getMaxThirst() {
	return MAX_THIRST;
}

void Character::decreaseThirst() {
	if (characterThirst > MIN_THIRST) {
		characterThirst--;
	}
}

void Character::increaseThirst(int amount) {
	if (amount > 0)
	{
		characterThirst += amount;

		if (characterThirst > MAX_THIRST)
		{
			characterThirst = MAX_THIRST;
		}
	}
}


	/*void Character::decreaseFood(int amount) {
		if (amount > 0 && characterFood > 0) {
			characterFood -= amount;
			if (characterFood < 0) {
				characterFood = 0;
			}
		}
	}//

	bool Character::isCharacterStarving() {
		return characterFood <= 0;
	}

	bool Character::isCharacterDehydrated() {
		return characterThirst <= 0;
	}*/
