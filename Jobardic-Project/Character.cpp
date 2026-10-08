#include "Character.h"
#include "Object.h"
#include <iostream>

Character::Character(Location* startingLocation) {
	Character::currentLocation = startingLocation;
	Character::inventory = {};
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