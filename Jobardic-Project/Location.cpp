#include "Location.h"
#include <iostream>

Location::Location(std::string name, std::string description) {
	Location::name = name;
	Location::description = description;
	Location::connectedLocations = {};
}
Location::Location(std::string name, std::string description, std::vector<Location*> cls) {
	Location::name = name;
	Location::description = description;
	Location::connectedLocations = cls;

	//The following Makes sure that connected locations are consistent when going back and forth.
	//ex:
	// Location1 is initialized with no connectedLocations
	// Location2 is initialized with Location1 connected
	// 
	// then Location1 needs to be updated to connect to Location2 as well so it goes both ways.
	for (Location* loc : connectedLocations) {
		loc->addConnectedLocation(this);
	}

}
void Location::addConnectedLocation(Location* location) {
	if (isNearbyLocation(location) == false) {
		connectedLocations.push_back(location);
	}
	if (location->isNearbyLocation(this) == false) {
		location->connectedLocations.push_back(this);
	}
}
std::string Location::getName() {
	return name;
}

std::string Location::getDescription() {
	return description;
}

std::vector<Location*> Location::getConnectedLocations() {
	return connectedLocations;
}

bool Location::isNearbyLocation(Location* location) {

	for (Location* loc : connectedLocations) {
		if (location == loc)
		{
			return true;
		}
	}
	return false;
}


std::vector<std::string> Location::getConnectedLocationNames() {
	std::vector<std::string> connectedLocationNames;
	for (Location* loc : connectedLocations) {
		connectedLocationNames.push_back(loc->getName());
	}
	return connectedLocationNames;
}

//For Testing Only

void Location::printConnectedLocationNames() {
	/*
	for (Location* loc : connectedLocations) {
		std::cout << getName() << ": ";
		std::cout << loc->getName() << ", ";
	}
	std::cout << std::endl;
	*/


	for (std::string locName : getConnectedLocationNames()) {
		std::cout << getName() << ": ";
		std::cout << locName << ", ";
	}
	std::cout << std::endl;
}