#include "Location.h"
#include "Object.h"
#include <iostream>

Location::Location(std::string name, std::string description, bool allowsSleep) {
	Location::name = name;
	Location::description = description;
	Location::locationObjects = {};
	Location::allowsSleep = allowsSleep;
}
Location::Location(std::string name, std::string description, std::vector<Object*> lbs) {
	Location::name = name;
	Location::description = description;
	Location::locationObjects = lbs;
}

void Location::addLocationObject(Object* obj) {
	locationObjects.push_back(obj);
}

void Location::removeLocationObject(std::string objectName) {
	auto indexOfObject = std::find_if(
		locationObjects.begin(), 
		locationObjects.end(), 
		[objectName](Object* obj) {
			return obj->getName() == objectName;
		}
	);
	if (indexOfObject != locationObjects.end()) {
		locationObjects.erase(indexOfObject);
	}
}

std::string Location::getName() {
	return name;
}

std::string Location::getDescription() {
	return description;
}
std::vector<Object*> Location::getLocationObjects() {
	return locationObjects;
}
bool Location::canPlayerSleepHere() {
	return allowsSleep;
}