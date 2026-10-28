#pragma once
#include <unordered_map>
#include <string>
#include "Location.h"

//Manages all locations and the program's ability to reference locations using enumerators
class World
{
	/*
	* public methods
	*	World()                                              - constructor, no arguments.
	*   findLocation(string)                                 - returns the enum of the location which maps t the passed string. returns INVALID_LOCATION if none are found. passed string is processed to remove preceding/following white spaces & remove capitalization.
	*   findLocation(LOCATION_ENUMS)                         - returns a pointer to the location class instance which maps to the passed enum. returns nullptr if none are found.
	*   locationString(LOCATION_ENUMS)                       - returns the name of the location class instance which maps to the passed enum. returns "INVALID_LOCATION" if none are found.
	*   isLocationConnected(LOCATION_ENUMS, LOCATION_ENUMS)  - returns true if the second location is connected to the first location (e.g player can move from location1 -> location2)), returns false if not or if invalid location(s) passed.
	*   outputLocationConnections(LOCATION_ENUMS)            - prints the names of the connected locations of the  location class instance which maps to the passed enum
	* 
	* private methods
	*	createLocation(LOCATION_ENUMS,string,string)         - creates a new location class instance, mapped to the provided enum & initialized with the name (first string) and description (second string) provided.
	*   addConnectedLocation(LOCATION_ENUMS, LOCATION_ENUMS) - connects the second location to the first location (e.g enables the player to move from location1 -> location2)
	* 
	* public data
	*	enum LOCATION_ENUMS                   - an enum type with a possible value for every location the world class constructor will initialize
	*   LOCATION_ENUMS INITIAL_LOCATION       - determines the starting location of the player when the game first starts.
	* 
	* private data
	*	unordered_map<string, LOCATION_ENUMS> locationInputMap                                - maps string values expected from processed player input to the correspending location enums.
	*   unordered_map<LOCATION_ENUMS, vector<LOCATION_ENUMS>> locationConnectionsMap          - maps enums of locations to a list of other locations which are connected to them (e.g player can directly travel from the first location to any location in the list)
	*   
	*/
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
		INNER_WOODS,
		WESTERN_FOREST_EDGE,
		EASTERN_FOREST_EDGE,
		NORTHERN_FOREST_EDGE,

		INVALID_LOCATION
	};
	static const LOCATION_ENUMS INITIAL_LOCATION = HOME_BEDROOM;
	World();
	LOCATION_ENUMS findLocation(std::string name);
	Location* findLocation(LOCATION_ENUMS loc_enum);
	std::string locationString(LOCATION_ENUMS loc_enum);
	bool isValidLocation(LOCATION_ENUMS loc_enum);
	bool isLocationConnected(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2);
	void outputLocationConnections(LOCATION_ENUMS loc_enum);
	

private:
	void createLocation(LOCATION_ENUMS location_enum, std::string name, std::string description);
	void addConnectedLocation(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2);
	std::unordered_map<std::string, LOCATION_ENUMS> locationInputMap = {
		{"home bedroom", HOME_BEDROOM},
		{"home kitchen", HOME_KITCHEN},
		{"home living room", HOME_LIVINGROOM},{"living room", HOME_LIVINGROOM},{"lr", HOME_LIVINGROOM},{"home lr", HOME_LIVINGROOM},{"hlr", HOME_LIVINGROOM},
		{"home bathroom", HOME_BATHROOM},
		{"home front door", HOME_FRONTDOOR},
		{"home front porch", HOME_FRONTPORCH},
		{"home back door", HOME_BACKDOOR},
		{"home backyard", HOME_BACKYARD},
		{"southern forest edge", SOUTHERN_FOREST_EDGE },
		{"inner woods", INNER_WOODS },
		{"western forest edge", WESTERN_FOREST_EDGE },
		{"eastern forest edge", EASTERN_FOREST_EDGE },
		{"northern forest edge", NORTHERN_FOREST_EDGE },

	};

	std::unordered_map<LOCATION_ENUMS, std::vector<LOCATION_ENUMS>> locationConnectionsMap;

	std::unordered_map<LOCATION_ENUMS, Location*> locationEnumToPointer;
};

