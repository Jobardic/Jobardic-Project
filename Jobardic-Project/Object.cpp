#include "Object.h"
#include <iostream>

Object::Object(std::string name, std::string description) {
	Object::name = name;
	Object::description = description;
}

std::string Object::getName() {
	return name;
}

std::string Object::getDescription() {
	return description;
}