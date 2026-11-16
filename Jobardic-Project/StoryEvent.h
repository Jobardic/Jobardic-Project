#pragma once

#include "Location.h"
#include "InputPrompts.h"
#include "World.h"
#include "Time.h"
#include <string>
#include <unordered_map>

class StoryEvent {

public:
	StoryEvent(std::string desc, Location* location, InputPrompts* inputPrompt);
	StoryEvent(int time[3],std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> objects, World* w);
	std::string getDescription();
	Location* getLocation();
	InputPrompts* getInputPrompt();

	void attemptEvent();
	bool addsObjectsToLocations();
	bool hasExecuted();
	int getDayThreshold();
	int getHourThreshold();
	int getMinuteThreshold();


private:
	std::string desc;
	Location* location;
	InputPrompts* inputPrompt;

	int daySchedule;
	int hourSchedule;
	int minuteSchedule;
	bool executed = false;
	std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> objectsToAddToLocations;
	//ToDo / technical debt: make world class static such that storyevent doesn't need to keep track of the world its applying to
	World* world;

};



//Event(String desc, String location, InputPropmt inputPromt) class - new

// stores and returns a desrciption, locationn and input prompt

//getters

//static string getDescription() - returns description

//static string getLocation() - returns location

//static string getInputPrompt() - returns inputPrompt
