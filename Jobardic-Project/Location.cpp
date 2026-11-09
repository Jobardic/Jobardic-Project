#include "Location.h"
#include "Object.h"
#include "InputHandler.h"
#include <iostream>
#include <string>

Location::Location(std::string name, std::string description, bool allowsSleep, bool isIndoors) {
	Location::name = name;
	Location::description = description;
	Location::locationObjects = {};
	Location::allowsSleep = allowsSleep;
	Location::indoors = isIndoors;
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
	std::string normalizedName = InputHandler::normalizeInput(objectName);

	auto indexOfObject = std::find_if(
		locationObjects.begin(),
		locationObjects.end(),
		[normalizedName](Object* obj) {
			return InputHandler::normalizeInput(obj->getName()) == normalizedName;
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
bool Location::getIndoors() {
	return indoors;
}

Object* Location::findLocationObject(std::string objectName) {
	std::string normalizedName = InputHandler::normalizeInput(objectName);
	auto indexOfObject = std::find_if(
		locationObjects.begin(),
		locationObjects.end(),
		[normalizedName](Object* obj) {
			return InputHandler::normalizeInput(obj->getName()) == normalizedName;
		}
	);

	if (indexOfObject != locationObjects.end()) {
		return *indexOfObject;
	}
	else {
		return nullptr;
	}
}

bool Location::hasObject(std::string objectName) {
	return (findLocationObject(objectName) != nullptr);
}