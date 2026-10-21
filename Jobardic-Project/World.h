#pragma once
#include <unordered_map>
#include <string>
#include "Location.h"

//Manages all locations and the program's ability to reference locations using enumerators
class World
{
public:
	enum LOCATION_ENUMS {
		HOME_BEDROOM,
		HOME_KITCHEN,
		HOME_LIVINGROOM,
		HOME_BATHROOM,
		HOME_FRONTDOOR,
		HOME_FRONTPORCH,
		HOME_BACKDOOR,
		HOME_BACKYARD,
		SOUTHERN_FOREST_EDGE,

		INVALID_LOCATION
	};
	World();
	LOCATION_ENUMS findLocation(std::string name);
	Location* findLocation(LOCATION_ENUMS loc_enum);
	std::string locationString(LOCATION_ENUMS loc_enum);
	bool isValidLocation(LOCATION_ENUMS loc_enum);
	bool isLocationConnected(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2);

private:
	void createLocation(LOCATION_ENUMS location_enum, std::string name, std::string description);
	std::unordered_map<std::string, LOCATION_ENUMS> locationInputMap = {
		{"home bedroom", HOME_BEDROOM},
		{"home kitchen", HOME_KITCHEN},
		{"home living room", HOME_LIVINGROOM},{"living room", HOME_LIVINGROOM},{"lr", HOME_LIVINGROOM},{"home lr", HOME_LIVINGROOM},{"hlr", HOME_LIVINGROOM},
		{"home bathroom", HOME_BATHROOM},
		{"home front door", HOME_FRONTDOOR},
		{"home front porch", HOME_FRONTPORCH},
		{"home back door", HOME_BACKDOOR},
		{"home backyard", HOME_BACKYARD},
		{"southern forest edge", SOUTHERN_FOREST_EDGE}

	};
	std::unordered_map<LOCATION_ENUMS, std::string> locationOutputMap = {
		{HOME_BEDROOM,"Home Bedroom"},
		{HOME_KITCHEN, "Home Kitchen"},
		{HOME_LIVINGROOM,"Home Living Room"},
		{HOME_BATHROOM,"Home Bathroom"},
		{HOME_FRONTDOOR,"Home Front Door"},
		{HOME_FRONTPORCH,"Home Front Porch"},
		{HOME_BACKDOOR,"Home Back Door"},
		{HOME_BACKYARD,"Home Backyard"},
		{SOUTHERN_FOREST_EDGE,"Southern Forest Edge"},
		{INVALID_LOCATION, "Invalid Location"}

	};
	std::unordered_map<LOCATION_ENUMS, Location*> locationEnumToPointer;
};

