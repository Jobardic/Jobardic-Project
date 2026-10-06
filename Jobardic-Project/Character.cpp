#include "Character.h"
#include <iostream>

Character::Character(Location* startingLocation) {
	currentLocation = startingLocation;
}

Location* Character::getCurrentLocation() {
	return currentLocation;
}
void Character::setCurrentLocation(Location* location) {
	currentLocation = location;
}