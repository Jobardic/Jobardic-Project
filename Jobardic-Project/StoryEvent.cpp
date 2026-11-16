#include "InputPrompts.h"
#include "InputChoice.h"
#include "Location.h"
#include <string>
#include "StoryEvent.h"

StoryEvent::StoryEvent(std::string desc, Location* location, InputPrompts* inputPrompt) {
	StoryEvent::desc = desc;
	StoryEvent::location = location;
	StoryEvent::inputPrompt = inputPrompt;
}
StoryEvent::StoryEvent(int time[3], std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> objects, World* w) {
	daySchedule = time[0];
	hourSchedule = time[1];
	minuteSchedule = time[2];

	//ToDo / technical debt: 
	// clean up incoming "objects" argument to not include things like duplicate items
	// make world class static such that storyevent doesn't need to keep track of the world its applying to
	objectsToAddToLocations = objects;
	world = w;
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

void StoryEvent::attemptEvent() {
	int currentTime = (Time::getDay() * 24 * 60) + (Time::getHour() * 60) + Time::getMinute();
	int eventTime = (daySchedule * 24 * 60) + (hourSchedule * 60) + minuteSchedule;

	if (currentTime >= eventTime) {
		for (const auto& mapping : objectsToAddToLocations) {
			for (const auto& object : mapping.second) {
				world->findLocation(mapping.first)->addLocationObject(object);
			}
		}
	}
}
bool StoryEvent::addsObjectsToLocations() {
	return (objectsToAddToLocations.empty());
}
bool StoryEvent::hasExecuted() {
	return executed;
}
int StoryEvent::getDayThreshold() {
	return daySchedule;
}
int StoryEvent::getHourThreshold() {
	return hourSchedule;
}
int StoryEvent::getMinuteThreshold() {
	return minuteSchedule;
}