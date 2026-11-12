#include "Character.h"
#include "Object.h"
#include "World.h"
#include "Time.h"
#include <string>
#include <cmath>

Character::Character(World::LOCATION_ENUMS startingLocation) {
	Character::currentLocation = startingLocation;
	Character::inventory = {};
	characterEnergy = START_ENERGY;
	characterFood = START_FOOD;
	characterWater = MAX_WATER;
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

float Character::getEnergy() {
	return characterEnergy;
}
int Character::getEnergyCeiling() {
	return std::ceil(characterEnergy); // returns energy rounded up to integer for display purposes
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
	passTime(0, fromIndoors ? I_MOVE_MINUTES : O_MOVE_MINUTES, false);
}

void Character::lookTime(bool indoors) {
	passTime(0, indoors ? I_LOOK_MINUTES : O_LOOK_MINUTES, false);
}

void Character::eatTime() {
	passTime(0, EAT_MINUTES, false);
}

void Character::drinkTime() {
	passTime(0, DRINK_MINUTES, false);
}

std::string Character::Sleep(bool canSleep) {
	if (!canSleep) {
		return "You can't sleep here.\n";
	}
	else {
		passTime(SLEEP_HOURS, 0, true);
		return "You sleep for " + std::to_string(SLEEP_HOURS) + " hours and wake up feeling refreshed.\n";
	}
}

std::string Character::Wait() {
	passTime(WAIT_HOURS, 0, false);
	return "You wait for " + std::to_string(WAIT_HOURS) + " hours...\n";
}

void Character::passTime(int hours, int minutes, bool sleeping) {
	Time::passTime(hours, minutes);
	float timeInHours = hours + minutes / 60.0;

	if (sleeping) {
		changeEnergy(SLEEP_ENERGY_RATE * timeInHours);
		changeFood(FOOD_RATE * SLEEP_MOD * timeInHours); 
		changeWater(WATER_RATE * SLEEP_MOD * timeInHours); 
	}
	else {
		changeEnergy(WAKE_ENERGY_RATE * timeInHours);
		changeFood(FOOD_RATE * timeInHours); 
		changeWater(WATER_RATE * timeInHours);
	}
}

float Character::getFood() {
	return characterFood;
}
int Character::getFoodCeiling() {
	return std::ceil(characterFood); // returns food rounded up to integer for display purposes
}
int Character::getMaxFood() {
	return MAX_FOOD;
}

void Character::changeFood(int amount) {
	characterFood += amount;
	if (characterFood > MAX_FOOD) {
		characterFood = MAX_FOOD;
	}
	if (characterFood < MIN_FOOD) {
		characterFood = MIN_FOOD;
	}
}

void Character::removeInventoryObject(int index) {
	if (index >= 0 &&
		index < static_cast<int>(inventory.size())) {
		inventory.erase(inventory.begin() + index);
	}
}

// NEW: Water Well / Thirst functionality

float Character::getWater() {
	return characterWater;
}
int Character::getWaterCeiling() {
	return std::ceil(characterWater); // returns water rounded up to integer for display purposes
}
int Character::getMaxWater() {
	return MAX_WATER;
}

void Character::decreaseWater() {
	if (characterWater > MIN_WATER) {
		characterWater--;
	}
}

void Character::changeWater(int amount) {
	characterWater += amount;
	if (characterWater > MAX_WATER) {
		characterWater = MAX_WATER;
	}
	if (characterWater < MIN_WATER) {
		characterWater = MIN_WATER;
	}
}

bool Character::isCharacterDead() 
{
	return characterFood <= 0 || characterWater <= 0 || characterEnergy <= 0;
}
