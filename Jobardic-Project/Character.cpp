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
	characterThirst = MAX_THIRST;
}

World::LOCATION_ENUMS Character::getCurrentLocation() {
	return currentLocation;
}

std::vector<Object*> Character::getInventory() {
	return inventory;
}

bool Character::hasItem(std::string objectName) {
	return (findInventoryObject(objectName) != nullptr);
}

void Character::pickUpObject(Object* item) {
	Character::inventory.push_back(item);
}

void Character::dropInventoryObject(std::string objectName) {
	std::string normalizedName = InputHandler::normalizeInput(objectName);

	auto indexOfObject = std::find_if(
		inventory.begin(),
		inventory.end(),
		[normalizedName](Object* obj) {
			return InputHandler::normalizeInput(obj->getName()) == normalizedName;
		}
	);
	if (indexOfObject != inventory.end()) {
		inventory.erase(indexOfObject);
	}
}

Object* Character::findInventoryObject(std::string objectName) {
	std::string normalizedName = InputHandler::normalizeInput(objectName);
	auto indexOfObject = std::find_if(
		inventory.begin(),
		inventory.end(),
		[normalizedName](Object* obj) {
			return InputHandler::normalizeInput(obj->getName()) == normalizedName;
		}
	);

	if (indexOfObject != inventory.end()) {
		return *indexOfObject;
	}
	else {
		return nullptr;
	}
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

void Character::moveTime(bool fromIndoors) {
	Time::passTime(0, fromIndoors ? I_MOVE_MINUTES : O_MOVE_MINUTES);
}

void Character::lookTime(bool indoors) {
	Time::passTime(0, indoors ? I_LOOK_MINUTES : O_LOOK_MINUTES);
}

void Character::eatTime() {
	Time::passTime(0, EAT_MINUTES);
}

void Character::drinkTime() {
	Time::passTime(0, DRINK_MINUTES);
}

std::string Character::Sleep(bool canSleep) {
	if (!canSleep) {
		return "You can't sleep here.\n";
	}
	else {
		Time::passTime(SLEEP_HOURS, 0);
		changeEnergy(SLEEP_HOURS * SLEEP_ENERGY_RATE); 
		return "You sleep for " + std::to_string(SLEEP_HOURS) + " hours and wake up feeling refreshed.\n";
	}
}

std::string Character::Wait() {
	Time::passTime(WAIT_HOURS, 0);
	changeEnergy(WAIT_HOURS * WAKE_ENERGY_RATE);
	return "You wait for " + std::to_string(WAIT_HOURS) + " hours...\n";
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

bool Character::isCharacterDead() 
{
	return characterFood <= 0 || characterThirst <= 0 || characterEnergy <= 0;
}
