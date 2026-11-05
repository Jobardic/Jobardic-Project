#include "InputPrompts.h"
#include "InputChoice.h"
#include "Location.h"
#include<string>
#include "StoryEvent.h"

StoryEvent::StoryEvent(std::string desc, Location* location, InputPrompts* inputPrompt) {
	StoryEvent::desc = desc;
	StoryEvent::location = location;
	StoryEvent::inputPrompt = inputPrompt;
}

std::string StoryEvent::getDescription() {
	return desc;
}

Location* StoryEvent::getLocation() {
	return location;
}

InputPrompts* StoryEvent::getInputPrompt() {
	return inputPrompt;
}

