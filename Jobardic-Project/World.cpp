#include "World.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <random>
#include <ctime>
#include <cctype>
#include "StoryEvent.h"
#include "EventManager.h"

/*
* 
* World class which manages all location class instances. 
* 
* Scope includes: initializing locations and objects in the world,
                  placing the objects into specific locations,
*                 establishing connections between locations which allow player travel between them
*                 processing and mapping player input to matching locations
*                 creating story events and adding them to the EventManager
* 
* 
* 
*/

/*
    To add locations to the world:
         1) add a new enum value to the LOCATION_ENUMS initialization in World.h. 
         2) add a new "createLocation()" function call in the constructor function "World()"
              provide it the new enum value, as well as a name and description strings.
              additionally, add two bool values: the first is for if the player can sleep, the second for if the location is indoors
         3) add new "addConnectedLocations()" function calls to the constructor to allow traversal to/from the location by the player
               e.g if we want the player to be able to be able to traverse NEWLOCATION -> OTHERLOCATION,
                           addConnectedLocations(NEWLOCATION, OTHERLOCATION)
                   if we want the player to be able to move back (OTHERLOCATION -> NEWLOCATION),
                           addConnectedLocations(OTHERLOCATION, NEWLOCATION)
            unless you want an explicitly one-way path you must add both versions of the function call
         4) add entries of {string, LOCATION_ENUM} to the locationInputMap

                the strings are what the player can input after the "Move" action to move to the inputted location.
                each entry string must have no spaces before all or after all characters and no capitalization
                    e.g  "  new_location", "new_location    ", "New_Location" will not work.
                at least one entry with a string directly matching the location name must be added 
                    e.g if the new location is called "Big House" with enum BIG_HOUSE, 
                        add an entry {"big house",BIG_HOUSE}
                strings must be unique to their entry
                    e.g {"big house", BIG_HOUSE_ONE},{"big house", BIG_HOUSE_TWO} will not work
                    but {"big house", BIG_HOUSE},{"bh", BIG_HOUSE} will work.                      

	To add objects to the world:
		1) create a new object in the World() constructor function
			e.g Object* newObject = new Object("object name", "object description");
		2) add the desired number copies of the object to the desired locations using the placeObjects() function
			e.g placeObjects(newObject, {LOCATION_ENUM1, LOCATION_ENUM2}, 2, false);
				- the first argument is the object pointer
				- the second argument is a vector of location enums where the object can be placed
				- the third argument is how many copies of the object to place in random locations from the provided vector
				- the fourth argument is a bool for if duplicates are allowed (e.g if true, all copies could be placed in one location, if false, each copy will be placed in a different location)

    To add new story events:
           1) create new story event in World() constructor by adding a new line initalizing it. More details on its parameters in StoryEvent.cpp
              e.g       StoryEvent* event = new StoryEvent(event_time,event_objects, this);
          2) add the story event to the EventManager by calling EventManager's addEvent method in the World() constructor
              e.g        EventManager::addEvent(event);
*/

//World Constructor
//initializes all locations and objects with their intended data.
World::World() {
    createLocation(HOME_BEDROOM, "Home Bedroom", "You are now in your bedroom.", true, true, 0.0);
    createLocation(HOME_KITCHEN, "Home Kitchen", "You are now in your kitchen.", false, true, 0.0);
    createLocation(HOME_LIVINGROOM, "Home Living Room", "You are now in your living room.", false, true, 0.0);
    createLocation(HOME_BATHROOM, "Home Bathroom", "You are now in your bathroom.", false, true, 0.0);
    createLocation(HOME_FRONTDOOR, "Home Front Door", "You are now at the front door to your home from the inside", false, true, 0.0);
    createLocation(HOME_FRONTPORCH, "Home Front Porch", "You are now outside on your front porch. Your mailbox is mounted just right of your doorbell.", false, false, 0.0);
    createLocation(HOME_BACKDOOR, "Home Back Door", "You are now at the back door to your home from the inside", false, true, 0.0);
    createLocation(HOME_BACKYARD, "Home Backyard", "You are now outside in your backyard", false, false, 0.0);
    createLocation(SOUTHERN_FOREST_EDGE, "Southern Forest Edge", "You are now standing at the edge of the forest behind your backyard, which is the southern-most area of the forest.", false, false, 0.0);
    createLocation(INNER_WOODS, "Inner Woods", "You are now standing in the middle of the forest. It is eerie and quiet.", false, false, 0.0);
    createLocation(WESTERN_FOREST_EDGE, "Western Forest Edge", "You are now standing at the western edge of the forest.", false, false, 0.0);
    createLocation(EASTERN_FOREST_EDGE, "Eastern Forest Edge", "You are now standing at the eastern edge of the forest.", false, false, 0.0);
    createLocation(NORTHERN_FOREST_EDGE, "Northern Forest Edge", "You are now standing at the northern edge of the forest.", false, false, 0.0);
    createLocation(HOME_LAWN, "Home Lawn", "The front lawn of your home. You haven't mowed it in a few weeks.", false, false, 0.0);
    createLocation(LINCOLN_COURT, "Lincoln Court", "The street you live on. There are a few abandoned houses on it.", false, false, 0.01);
    createLocation(THREE_LINCOLN_COURT_FRONT_DOOR, "3 Lincoln Court Front Door", "The front door of one of the abandoned houses on your street.", false, false, 0.3);
    createLocation(FOUR_LINCOLN_COURT_FRONT_DOOR, "4 Lincoln Court Front Door", "The front door of one of the abandoned houses on your street.", false, false, 0.4);
    createLocation(NORTH_HUESTON_AVE, "North Hueston Ave", "The northern section of the distributary road connected to your street. There are some more abandonded houses here.", false, false, 0.0);
    createLocation(TWELVE_HUESTON_AVE_FRONT_DOOR, "12 Hueston Ave Front Door", "The front door of one of the abandoned houses on Hueston Ave.", false, false, 0.3);
    createLocation(FOURTEEN_HUESTON_AVE_FRONT_DOOR, "14 Hueston Ave Front Door", "The front door of one of the abandoned houses on Hueston Ave.", false, false, 0.5);
    createLocation(SOUTH_HUESTON_AVE, "South Hueston Ave", "The northern section of the distributary road connected to your street. There are some more abandonded houses here.", false, false, 0.0);
    createLocation(FIVE_HUESTON_AVE_FRONT_DOOR, "5 Hueston Ave Front Door", "The front door of one of the abandoned houses on Hueston Ave.", false, false, 0.4);
    createLocation(THREE_HUESTON_AVE_FRONT_DOOR, "3 Hueston Ave Front Door", "The front door of one of the abandoned houses on Hueston Ave. It has a silver lock.", false, false, 0.1);
    createLocation(THREE_HUESTON_AVE_LIVING_ROOM, "3 Hueston Ave Living Room", "The interior of one of the abandoned houses on Hueston Ave. It is dusty and barren.", false, true, 0.2);
    // ^ This location opens up after you find the silver key
    createLocation(SIX_HUESTON_AVE_FRONT_DOOR, "6 Hueston Ave Front Door", "The front door of one of the abandoned houses on Hueston Ave.", false, false, 0.4);
    createLocation(ONE_HUESTON_AVE_FRONT_DOOR, "1 Hueston Ave Front Door", "The front door of one of the abandoned houses on Hueston Ave.", false, false, 0.5);
    createLocation(EAST_MAIN_STREET, "East Main Street", "The eastern part of the Main Street in your town.", false, false, 0.0);
    createLocation(ONE_TWELVE_MAIN_STREET_FRONT_DOOR, "112 Main Street Front Door", "The front door of one of the abandoned houses on Main Street.", false, false, 0.2);
    createLocation(ONE_TWELVE_MAIN_STREET_SIDE_DOOR, "112 Main Street Side Door", "The side door of one of the abandoned houses on Main Street.", false, false, 0.2);
    createLocation(TOWN_DINER_ENTRANCE, "Town Diner Entrance", "The entrance of the most notable diner in your town.", false, false, 0.15);
    createLocation(TOWN_DINER_BACKLOT, "Town Diner Backlot", "The backlot of your town diner. It has parking spaces and a dumpster", false, false, 0.5);
    createLocation(WEST_MAIN_STREET, "West Main Street", "The western part of the Main Street in your town.", false, false, 0.0);
    createLocation(GROCERY_STORE_ENTRANCE, "Grocery Store Entrance", "The entrance of the main grocery store in your town. It is closed for repairs.", false, false, 0.15);
    createLocation(GROCERY_STORE_BACKLOT, "Grocery Store Backlot", "The back of the main grocery store in your town. It has parking spaces and a dumpster", false, false, 0.5);
    createLocation(CONSTRUCTION_DEPOT_ENTRANCE, "Construction Depot Entrance", "The entrance to the construction store in your town. It says it should open within the week.", false, false, 0.0);
    createLocation(CONSTRUCTION_DEPOT_INTERIOR, "Construction Depot Interior", "The inside of the construction store in your town. It has many useful tools and materials", false, true, 0.0);
    // ^ This location opens after 10 days
    createLocation(ARCADE_ENTRANCE, "Arcade Entrance", "The entrance of the arcade in your town. You have no desire to go in.", false, false, 0.0);
    createLocation(ARCADE_ALLEY, "Arcade Alley", "The alley on the side of the arcade. It is dark and long.", false, false, 0.2);
    createLocation(TOWN_PARK, "Town Park", "The main park in your town. It has a playground, garden, and a lot of grass to walk your dog on.", false, false, 0.1);
    createLocation(TOWN_GARDEN, "Town Garden", "The town garden has many freshly grown vegetables and fruits, but many are no in season right now.", false, false, 0.0);
	createLocation(WATER_WELL, "Water Well", "You are now standing at a water well. You can fill your bucket with fresh water here.", false, false, 0.0);


    Object* chewtoy = new Object("Chewtoy", "It is your dog's favorite chewtoy, which reminds you that you haven't seen your dog all morning");
    Object* burger = new Object("Burger", "A delicious burger that can last you a day");
    Object* dog = new Object("Your Dog", "Your beloved bet you've had for years! His favorite toy is his chewtoy");
    Object* firewood = new Object("Firewood", "Wood that can be used for a long fire for warmth");
    Object* wooden_planks = new Object("Wooden Planks", "Wood that can be used for a fire or to board up your house");
    Object* coal = new Object("Coal", "Fuel that can be used for a long fire for warmth");
    Object* fire_axe = new Object("Fire Axe", "A tool that be used to chop wood or as a weapon");
    Object* silver_key = new Object("Silver key", "A key that goes to a lock you think you've seen before");
    Object* half_generator = new Object("Generator", "A half full generator that can be used for warmth for multiple days");
    Object* cabbage = new Object("Cabbage", "A delicious vegetable you can eat");
    Object* potato_bag = new Object("Bag of Potatoes", "A starchy plant you can eat for multiple days");
    Object* wallet = new Object("Wallet", "A random wallet with $70 in it! There's no identification inside");
    Object* dog_food_bag = new Object("Dog Food Bag", "A bag of food for your dog!");
    Object* bucket = new Object("Bucket", "A bucket which can be used to collect water from the well.");
    Object* sandwich = new Object("Sandwich", "A meal that can last you a day");
    Object* corn_bag = new Object("Bag of Corn", "Some vegetables that can last you a day");
    Object* rice_bag = new Object("Bag of Rice", "A starch that can last you a day");
    Object* chicken_bucket = new Object("Bucket of Chicken", "A meal that can last you a day");
    Object* lo_mein = new Object("Box of Lo Mein", "A meal that can last you a day");
    Object* broccoli_bag = new Object("Bag of Broccoli", "A vegetable that can last you a day");
    Object* carrot_bag = new Object("Bag of Carrots", "A vegetable that can last you a day");
    Object* tree_branch = new Object("Tree Branch", "A branch fallen from a tree nearby, could be used as a weapon");


    Object* weather_report_letter = new Object("NOAA Report Letter", "\"WEATHER ADVISORY:\n   Residents are advised to stay indoors and exercise caution for the next 48 hours\n   due to predicted incoming heavy rainfall and thunder\"");
    int weather_report_time[3] = { 2,0,0 }; //Day 2, Hour 0, Minute 0
    std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> weather_report_objects = { 
        {HOME_FRONTPORCH,{weather_report_letter}}
    };
    StoryEvent* addWeatherReportToMailboxEvent = new StoryEvent(weather_report_time,weather_report_objects, this);
    EventManager::addEvent(addWeatherReportToMailboxEvent);
    
    
    Object* foodLoot[10] = {burger, cabbage, potato_bag, sandwich, corn_bag, rice_bag, chicken_bucket, lo_mein, broccoli_bag, carrot_bag};
    //Array of food that is used for loot generation

    //ToDo: combine the connected location adding & item adding w/ createLocation() function

    addConnectedLocation(HOME_BEDROOM, HOME_LIVINGROOM);
    addConnectedLocation(HOME_LIVINGROOM, HOME_BEDROOM);

    addConnectedLocation(HOME_BEDROOM, HOME_BATHROOM);
    addConnectedLocation(HOME_BATHROOM, HOME_BEDROOM);

    addConnectedLocation(HOME_LIVINGROOM, HOME_KITCHEN);
    addConnectedLocation(HOME_KITCHEN, HOME_LIVINGROOM);

    addConnectedLocation(HOME_LIVINGROOM, HOME_BATHROOM);
    addConnectedLocation(HOME_BATHROOM, HOME_LIVINGROOM);

    addConnectedLocation(HOME_LIVINGROOM, HOME_BACKDOOR);
    addConnectedLocation(HOME_BACKDOOR, HOME_LIVINGROOM);

    addConnectedLocation(HOME_BACKDOOR, HOME_BACKYARD);
    addConnectedLocation(HOME_BACKYARD, HOME_BACKDOOR);

    addConnectedLocation(HOME_KITCHEN, HOME_FRONTDOOR);
    addConnectedLocation(HOME_FRONTDOOR, HOME_KITCHEN);

    addConnectedLocation(HOME_FRONTDOOR, HOME_FRONTPORCH);
    addConnectedLocation(HOME_FRONTPORCH, HOME_FRONTDOOR);

    addConnectedLocation(HOME_BACKYARD, SOUTHERN_FOREST_EDGE);
    addConnectedLocation(SOUTHERN_FOREST_EDGE, HOME_BACKYARD);

    addConnectedLocation(INNER_WOODS, SOUTHERN_FOREST_EDGE);
    addConnectedLocation(SOUTHERN_FOREST_EDGE, INNER_WOODS);

    addConnectedLocation(INNER_WOODS, WESTERN_FOREST_EDGE);
    addConnectedLocation(WESTERN_FOREST_EDGE, INNER_WOODS);

    addConnectedLocation(INNER_WOODS, EASTERN_FOREST_EDGE);
    addConnectedLocation(EASTERN_FOREST_EDGE, INNER_WOODS);

    addConnectedLocation(INNER_WOODS, NORTHERN_FOREST_EDGE);
    addConnectedLocation(NORTHERN_FOREST_EDGE, INNER_WOODS);

    addConnectedLocation(HOME_FRONTPORCH, HOME_LAWN);
    addConnectedLocation(HOME_LAWN, HOME_FRONTPORCH);

    addConnectedLocation(LINCOLN_COURT, HOME_LAWN);
    addConnectedLocation(HOME_LAWN, LINCOLN_COURT);

    addConnectedLocation(LINCOLN_COURT, THREE_LINCOLN_COURT_FRONT_DOOR);
    addConnectedLocation(THREE_LINCOLN_COURT_FRONT_DOOR, LINCOLN_COURT);

    addConnectedLocation(LINCOLN_COURT, FOUR_LINCOLN_COURT_FRONT_DOOR);
    addConnectedLocation(FOUR_LINCOLN_COURT_FRONT_DOOR, LINCOLN_COURT);

    addConnectedLocation(LINCOLN_COURT, NORTH_HUESTON_AVE);
    addConnectedLocation(NORTH_HUESTON_AVE, LINCOLN_COURT);

    addConnectedLocation(TWELVE_HUESTON_AVE_FRONT_DOOR, NORTH_HUESTON_AVE);
    addConnectedLocation(NORTH_HUESTON_AVE, TWELVE_HUESTON_AVE_FRONT_DOOR);

    addConnectedLocation(FOURTEEN_HUESTON_AVE_FRONT_DOOR, NORTH_HUESTON_AVE);
    addConnectedLocation(NORTH_HUESTON_AVE, FOURTEEN_HUESTON_AVE_FRONT_DOOR);

    addConnectedLocation(SOUTH_HUESTON_AVE, NORTH_HUESTON_AVE);
    addConnectedLocation(NORTH_HUESTON_AVE, SOUTH_HUESTON_AVE);

    addConnectedLocation(SOUTH_HUESTON_AVE, FIVE_HUESTON_AVE_FRONT_DOOR);
    addConnectedLocation(FIVE_HUESTON_AVE_FRONT_DOOR, SOUTH_HUESTON_AVE);

    addConnectedLocation(SOUTH_HUESTON_AVE, THREE_HUESTON_AVE_FRONT_DOOR);
    addConnectedLocation(THREE_HUESTON_AVE_FRONT_DOOR, SOUTH_HUESTON_AVE);

    addConnectedLocation(HOME_BACKYARD, WATER_WELL);
    addConnectedLocation(WATER_WELL, HOME_BACKYARD);

    addConnectedLocation(FIVE_HUESTON_AVE_FRONT_DOOR, THREE_HUESTON_AVE_FRONT_DOOR);
    addConnectedLocation(THREE_HUESTON_AVE_FRONT_DOOR, FIVE_HUESTON_AVE_FRONT_DOOR);

    addConnectedLocation(THREE_HUESTON_AVE_LIVING_ROOM, THREE_HUESTON_AVE_FRONT_DOOR);
    addConnectedLocation(THREE_HUESTON_AVE_FRONT_DOOR, THREE_HUESTON_AVE_LIVING_ROOM);

    addConnectedLocation(SOUTH_HUESTON_AVE, SIX_HUESTON_AVE_FRONT_DOOR);
    addConnectedLocation(SIX_HUESTON_AVE_FRONT_DOOR, SOUTH_HUESTON_AVE);

    addConnectedLocation(SOUTH_HUESTON_AVE, ONE_HUESTON_AVE_FRONT_DOOR);
    addConnectedLocation(ONE_HUESTON_AVE_FRONT_DOOR, SOUTH_HUESTON_AVE);

    addConnectedLocation(SOUTH_HUESTON_AVE, EAST_MAIN_STREET);
    addConnectedLocation(EAST_MAIN_STREET, SOUTH_HUESTON_AVE);

    addConnectedLocation(ONE_TWELVE_MAIN_STREET_FRONT_DOOR, EAST_MAIN_STREET);
    addConnectedLocation(EAST_MAIN_STREET, ONE_TWELVE_MAIN_STREET_FRONT_DOOR);

    addConnectedLocation(ONE_TWELVE_MAIN_STREET_FRONT_DOOR, ONE_TWELVE_MAIN_STREET_SIDE_DOOR);
    addConnectedLocation(ONE_TWELVE_MAIN_STREET_SIDE_DOOR, ONE_TWELVE_MAIN_STREET_FRONT_DOOR);

    addConnectedLocation(TOWN_DINER_ENTRANCE, EAST_MAIN_STREET);
    addConnectedLocation(EAST_MAIN_STREET, TOWN_DINER_ENTRANCE);

    addConnectedLocation(TOWN_DINER_ENTRANCE, TOWN_DINER_BACKLOT);
    addConnectedLocation(TOWN_DINER_BACKLOT, TOWN_DINER_ENTRANCE);

    addConnectedLocation(WEST_MAIN_STREET, EAST_MAIN_STREET);
    addConnectedLocation(EAST_MAIN_STREET, WEST_MAIN_STREET);

    addConnectedLocation(WEST_MAIN_STREET, GROCERY_STORE_ENTRANCE);
    addConnectedLocation(GROCERY_STORE_ENTRANCE, WEST_MAIN_STREET);

    addConnectedLocation(GROCERY_STORE_BACKLOT, GROCERY_STORE_ENTRANCE);
    addConnectedLocation(GROCERY_STORE_ENTRANCE, GROCERY_STORE_BACKLOT);

    addConnectedLocation(TOWN_DINER_BACKLOT, GROCERY_STORE_BACKLOT);
    addConnectedLocation(GROCERY_STORE_BACKLOT, TOWN_DINER_BACKLOT);

    addConnectedLocation(WEST_MAIN_STREET, CONSTRUCTION_DEPOT_ENTRANCE);
    addConnectedLocation(CONSTRUCTION_DEPOT_ENTRANCE, WEST_MAIN_STREET);

    addConnectedLocation(CONSTRUCTION_DEPOT_INTERIOR, CONSTRUCTION_DEPOT_ENTRANCE);
    addConnectedLocation(CONSTRUCTION_DEPOT_ENTRANCE, CONSTRUCTION_DEPOT_INTERIOR);

    addConnectedLocation(WEST_MAIN_STREET, ARCADE_ENTRANCE);
    addConnectedLocation(ARCADE_ENTRANCE, WEST_MAIN_STREET);

    addConnectedLocation(ARCADE_ALLEY, ARCADE_ENTRANCE);
    addConnectedLocation(ARCADE_ENTRANCE, ARCADE_ALLEY);

    addConnectedLocation(ARCADE_ALLEY, TOWN_PARK);
    addConnectedLocation(TOWN_PARK, ARCADE_ALLEY);

    addConnectedLocation(TOWN_GARDEN, TOWN_PARK);
    addConnectedLocation(TOWN_PARK, TOWN_GARDEN);

    addConnectedLocation(NORTHERN_FOREST_EDGE, TOWN_PARK);
    addConnectedLocation(TOWN_PARK, NORTHERN_FOREST_EDGE);

    // NEW: Place objects in the world by calling placeObjects()
    
    placeObjects(chewtoy, { HOME_BACKDOOR }, 1, false);
    placeObjects(burger, { HOME_KITCHEN }, 1, false);
    placeObjects(dog, { EASTERN_FOREST_EDGE, WESTERN_FOREST_EDGE, NORTHERN_FOREST_EDGE, SOUTHERN_FOREST_EDGE, INNER_WOODS }, 1, false);
    placeObjects(firewood, { FOUR_LINCOLN_COURT_FRONT_DOOR, FIVE_HUESTON_AVE_FRONT_DOOR }, 2, false);
    placeObjects(coal, { TWELVE_HUESTON_AVE_FRONT_DOOR }, 1, false);
	placeObjects(fire_axe, { THREE_HUESTON_AVE_FRONT_DOOR }, 1, false);
	placeObjects(half_generator, { THREE_HUESTON_AVE_LIVING_ROOM }, 1, false);
	placeObjects(wooden_planks, { ONE_TWELVE_MAIN_STREET_SIDE_DOOR }, 1, false);
	placeObjects(dog_food_bag, { GROCERY_STORE_ENTRANCE }, 1, false);
	placeObjects(silver_key, { GROCERY_STORE_BACKLOT }, 1, false);
	placeObjects(wallet, { ARCADE_ALLEY }, 1, false);
	placeObjects(cabbage, { TOWN_GARDEN }, 1, false);
	placeObjects(bucket, { HOME_BATHROOM }, 1, false);
	placeObjects(tree_branch, { SOUTHERN_FOREST_EDGE, WESTERN_FOREST_EDGE, EASTERN_FOREST_EDGE, NORTHERN_FOREST_EDGE, INNER_WOODS }, 4, true);

    randomizeFood(foodLoot);
}

void World::createLocation(LOCATION_ENUMS location_enum, std::string name, std::string description, bool allowsSleep, bool isIndoors, float lootChance) {
    Location* newLocation = new Location(name, description, allowsSleep, isIndoors, lootChance);
    locationEnumToPointer.insert_or_assign(location_enum, newLocation);
}


bool World::isValidLocation(LOCATION_ENUMS loc_enum) {
    if (loc_enum == INVALID_LOCATION) {
        return false;
    }
    else {
        return true;
    }
}

World::LOCATION_ENUMS World::findLocation(std::string name) {
    
    name = InputHandler::normalizeInput(name);

    //search the possible inputs mapping for the location enum which matches the provided name after having been input corrected for spaces & capitalization
    for (const auto& mapping : locationInputMap) {
        if (mapping.first == name) {
            return mapping.second;
        }
    }
    return INVALID_LOCATION;

}

std::string World::locationString(LOCATION_ENUMS loc_enum) {
    if (findLocation(loc_enum) != nullptr) {
        return findLocation(loc_enum)->getName();
    }
    else {
        return "INVALID_LOCATION";
    }
}

Location* World::findLocation(LOCATION_ENUMS loc_enum) {
    for (const auto& mapping : locationEnumToPointer) {
        if (mapping.first == loc_enum) {
            return mapping.second;
        }
    }

    return nullptr;

}

bool World::isLocationConnected(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2) {

    if (isValidLocation(loc_enum1) && isValidLocation(loc_enum2)) {

        auto findResult = locationConnectionsMap.find(loc_enum1);
        if (findResult != locationConnectionsMap.end()) {
            auto& locationEntry = *findResult;
            for (auto& connections : locationEntry.second) {
                if (connections == loc_enum2) {
                    return true;
                }
            }
        }

    }
    return false;
}

void World::outputLocationConnections(LOCATION_ENUMS loc_enum) {
    //ToDo: 
    // convert these "cout" statments into UI class method calls
    if (isValidLocation(loc_enum)) {

        auto findResult = locationConnectionsMap.find(loc_enum);
        if (findResult != locationConnectionsMap.end()) {
            auto& locationEntry = *findResult;

            if (locationEntry.first == loc_enum) {
                for (auto& connectionedLoc : locationEntry.second) {
                    std::cout << "=== " << locationString(connectionedLoc) << std::endl;
                }
            }
            
        }

    }
    else
    {
        std::cout << "Error: outputLocationConnections() passed INVALID_LOCATION enum, which should never happen";
    }
}

void World::placeObjects(Object* object, std::vector<LOCATION_ENUMS> locations, int copies, bool duplicates) {
    for (int i = 0; i < copies; i++) {
		int randLocationIndex = rand() % locations.size();
		LOCATION_ENUMS randLocationEnum = locations[randLocationIndex];
        findLocation(randLocationEnum)->addLocationObject(object);
        if (!duplicates && (copies - i) <= locations.size()) {      // extra check just in case function is called with duplicates = false and more copies than locations in vector
            locations.erase(locations.begin() + randLocationIndex);
        }
    }
}

void World::addConnectedLocation(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2) {
    if (isLocationConnected(loc_enum1,loc_enum2) == false) {                  //IF loc_enum2 isn't already connected to loc_enum1...    (and isLocationConnected already returns false if one or both location enums are invalid)
        locationConnectionsMap[loc_enum1];                                    //    create mapping entry for loc_enum1 if it doesn't already exist. both the provided enum and the new vector are created by this, the vector being empty.
        auto& locationEntry = *locationConnectionsMap.find(loc_enum1);        //    gets the mapping entry we just created OR the already existing entry
        locationEntry.second.push_back(loc_enum2);                            //    adds the second location to the vector

    }
}

void World::randomizeFood(Object** lootArray) { // Iterates over all the locations
    srand(time(0)); //randomizes the chance
    for (int fooInt = HOME_BEDROOM; fooInt != INVALID_LOCATION; fooInt++) { //Invalid Location must be the last location for this to work
        LOCATION_ENUMS foo = static_cast<LOCATION_ENUMS>(fooInt); //turns the "index" into the enum
        if (rand()%101 < ((findLocation(foo)->getLootChance())*100)) { //if random chance is within the % chance of the location, put food there
            findLocation(foo)->addLocationObject(new Object(lootArray[rand() % 10]->getName(), lootArray[rand() % 10]->getDescription())); //assigns a random food to the location
        }
    }
}


