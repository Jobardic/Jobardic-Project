#include "World.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>

/*
* 
* World class which manages all location class instances. 
* 
* Scope includes: initializing locations and objects in the world,
                  placing the objects into specific locations,
*                 establishing connections between locations which allow player travel between them
*                 processing and mapping player input to matching locations
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

*/

//World Constructor
//initializes all locations and objects with their intended data.
World::World() {

    createLocation(HOME_BEDROOM, "Home Bedroom", "You stand in your bedroom.\nYour bed is slightly disheveled, whay bother making your bed if the moon is really coming down.", true, true);
    createLocation(HOME_KITCHEN, "Home Kitchen", "You stand in your kitchen. The stovetop is cracked.", false, true);
    createLocation(HOME_LIVINGROOM, "Home Living Room", "You stand in your living room. A fine layer of dust is collecting on the coffee table.", false, true);
    createLocation(HOME_BATHROOM, "Home Bathroom", "You stand in your bathroom. The sink doesn't work.", false, true);
    createLocation(HOME_FRONTDOOR, "Home Front Door", "You stand at the front door. You can almost see the other housees through the peephole.", false, true);
    createLocation(HOME_FRONTPORCH, "Home Front Porch", "You step outside onto your front porch. The air is stale and chilly.", false, false);
    createLocation(HOME_BACKDOOR, "Home Back Door", "You stand by the back door. You can see trees through a window.", false, true);
    createLocation(HOME_BACKYARD, "Home Backyard", "You are now outside in your backyard. The trees lining you backyard sway in the wind.", false, false);
    createLocation(SOUTHERN_FOREST_EDGE, "Southern Forest Edge", "You trek through the south edge of the forest. \033[3mYou should be careful not to get lost in here.\003[0m", false, false);
    createLocation(INNER_WOODS, "Inner Woods", "You stand in the middle of the forest. \003[3mIt is eerie and quiet.\033[0m", false, false);
    createLocation(WESTERN_FOREST_EDGE, "Western Forest Edge", "You trek through the western edge of the forest. \033[3mThe shadows between the trees dance to the shuffle of the leaves.\003[0m", false, false);
    createLocation(EASTERN_FOREST_EDGE, "Eastern Forest Edge", "You trek through the eastern edge of the forest. \033[3mThe stones beneath your feet are rough and ragged.\003[0m", false, false);
    createLocation(NORTHERN_FOREST_EDGE, "Northern Forest Edge", "You trek through the northern edge of the forest. \033[3mThe trees seem to twist under the shade of their own foliage.\003[0m", false, false);
    createLocation(HOME_LAWN, "Home Lawn", "You look over your front lawn. \033[3mYou haven't mowed it in a few weeks.\033[0m", false, false);

    createLocation(LINCOLN_COURT, "Lincoln Court", "You walk out onto the street. There are a few abandoned houses on it. The street is empty.", false, false);
    createLocation(THREE_LINCOLN_COURT_FRONT_DOOR, "3 Lincoln Court Front Door", "You stand at one of the front doors of one of the abandoned houses on your street.\nYou don't remember who lived here.", false, false);
    createLocation(FOUR_LINCOLN_COURT_FRONT_DOOR, "4 Lincoln Court Front Door", "You stand at one of the front doors of one of the abandoned houses on your street.\nYou don't remember his name.", false, false);
    createLocation(NORTH_HUESTON_AVE, "North Hueston Ave", "You walk down the northern section of the distributary road connected to your street.\nThere are some abandonded houses here. Wind skims the void that kept neighbors apart.", false, false);
    createLocation(TWELVE_HUESTON_AVE_FRONT_DOOR, "12 Hueston Ave Front Door", "You stand at one of the front doors of one of the abandoned houses on Hueston Ave.\nYou think she used to have lilacs in her garden.", false, false);
    createLocation(FOURTEEN_HUESTON_AVE_FRONT_DOOR, "14 Hueston Ave Front Door", "You stand at one of the front doors of one of the abandoned houses on Hueston Ave.\nYou notice oil stains on the driveway, you remeber she liked cars.", false, false);
    createLocation(SOUTH_HUESTON_AVE, "South Hueston Ave", "You walk down the southern section of the distributary road connected to your street.\nThere are some more abandonded houses here. The wind produces a familiar note.", false, false);
    createLocation(FIVE_HUESTON_AVE_FRONT_DOOR, "5 Hueston Ave Front Door", "You stand at one of the front doors of one of the abandoned houses on Hueston Ave.\nYou think his name was Reginald.", false, false);
    createLocation(THREE_HUESTON_AVE_FRONT_DOOR, "3 Hueston Ave Front Door", "You stand at one of the front doors of one of the abandoned houses on Hueston Ave.\n\033[4mIt has a silver lock.\033[0m", false, false);
    createLocation(THREE_HUESTON_AVE_LIVING_ROOM, "3 Hueston Ave Living Room", "You stand inside 3 Hueston Ave. It is dusty and barren.", false, true);
    // ^ This location opens up after you find the silver key
    createLocation(SIX_HUESTON_AVE_FRONT_DOOR, "6 Hueston Ave Front Door", "You stand at one of the front doors of one of the abandoned houses on Hueston Ave.\nYou remember they used to have an immaculate lawn.\nThe yellow grass crinkles underfoot.", false, false);
    createLocation(ONE_HUESTON_AVE_FRONT_DOOR, "1 Hueston Ave Front Door", "You stand at one of the front doors of one of the abandoned houses on Hueston Ave.\nYou Wish you got to know her better.", false, false);
    createLocation(EAST_MAIN_STREET, "East Main Street", "You walk down the eastern part of Main Street. You used to know the kids that would loiter here.", false, false);
    createLocation(ONE_TWELVE_MAIN_STREET_FRONT_DOOR, "112 Main Street Front Door", "You stand at one of the front doors of one of the abandoned houses on Main Street.\nYou don't know who lived here.", false, false);
    createLocation(ONE_TWELVE_MAIN_STREET_SIDE_DOOR, "112 Main Street Side Door", "You stand at one of the front doors of one of the abandoned houses on Main Street.\nThe latch is broken.", false, false);

    createLocation(TOWN_DINER_ENTRANCE, "Town Diner Entrance", "You view the entrance of the most notable diner in town.\nYou remember the smell that would waft from this place around breakfast. \033[3mThat's gone now.\033[0m", false, false);
    createLocation(TOWN_DINER_BACKLOT, "Town Diner Backlot", "You've come to stand behind the town diner.\nIts parking spaces empty and the dumpster full of rodents scavenging for any leftover scraps.", false, false);
    createLocation(WEST_MAIN_STREET, "West Main Street", "You walk down the western part of the Main Street. You remember walking down Main Street every morning.", false, false);
    createLocation(GROCERY_STORE_ENTRANCE, "Grocery Store Entrance", "You stand to enter the grocery store. It has closed for repairs for a while now.", false, false);
    createLocation(GROCERY_STORE_BACKLOT, "Grocery Store Backlot", "You've come to stand behind the grocery store. Its parking spaces stained with oil and the dumpster leaking.", false, false);
    createLocation(CONSTRUCTION_DEPOT_ENTRANCE, "Construction Depot Entrance", "You stand at the entrance to the construction store. The smell of lumber and oil fills the air.\n\003[4mIt says it should open within the week.\033[0m", false, false);
    createLocation(CONSTRUCTION_DEPOT_INTERIOR, "Construction Depot Interior", "You walk inside the construction depot. Your shoes come down hard on the hard tile floors.\nIt keeps many useful tools and materials in stock.", false, true);
    // ^ This location opens after 10 days
    createLocation(ARCADE_ENTRANCE, "Arcade Entrance", "You stand and look askance at the entrance of the arcade.\nIts games, whose lights and sounds would fill the surrounding alleys, now lie dormant and dark.\n\033[3mYou have no desire to go in.\033[0m", false, false);
    createLocation(ARCADE_ALLEY, "Arcade Alley", "You duck into the alley on the side of the arcade.\nIts dark shadows lap the barrier between itself and the rest of the world.", false, false);
    createLocation(TOWN_PARK, "Town Park", "You walk through a park, it has a playground, garden, and a lot of grass to walk your dog on.\n\033[3mThough, many of the facilities have seen better days.\033[0m", false, false);
    createLocation(TOWN_GARDEN, "Town Garden", "You look upon the town garden. It usually has many freshly grown vegetables and fruits,\nbut it's verdancy has long since gone and many vegetables are not in season right now.\n\033[3mYou doubt they ever will be again.\033[0m", false, false);
	createLocation(WATER_WELL, "Water Well", "You peer into the well, its so deep light doesn't reach the bottom. \033[3mYou can fill a bucket with fresh water here.\033[0m", false, false);


    Object* chewtoy = new Object("\033[4mChewtoy\033[0m", "It is your dog's favorite cheeseburger chewtoy, which reminds you that you haven't seen your dog in a while.");
    Object* burger = new Object("\033[4mBurger\033[0m", "A delicious burger is waiting in the oven... \033[1mWait. What is a burger doing in the oven?\033[0m");
    Object* dog = new Object("\033[4mYour Dog\033[0m", "Your beloved pet you've had for years! He loves his chewtoy.");
    Object* firewood = new Object("\033[4mFirewood\033[0m", "Wood that can be burned for a long time to generate warmth.");
    Object* wooden_planks = new Object("\033[4mWooden Planks\033[0m", "Wood that can be burned or used to board up your house.");
    Object* coal = new Object("\033[4mCoal\033[0m", "Fuel that can be burned for a long time.");
    Object* fire_axe = new Object("\033[4mFire Axe\033[0m", "A tool you can use to chop wood or as a weapon.");
    Object* silver_key = new Object("\033[4mSilver key\033[0m", "A key that shines in the moonlight. \033[3mYou wonder what it unlocks.\033[0m");
    Object* half_generator = new Object("\033[4mGenerator\033[0m", "A half full generator that can burn fuel for warmth for multiple days. It smells like diesel.");
    Object* burger_bag = new Object("\033[4mBag of Burgers\033[0m", "A large bag of food that can last you multiple days... \033[1mWho put all these burgers in a bag?\033[0m");
    Object* cabbage = new Object("\033[4mCabbage\033[0m", "A delicious leafy vegetable you can eat, it's high in vitamin C!");
    Object* potato_sack = new Object("\033[4mBag of Potatoes\033[0m", "A bag of brown starchy plants you can eat for multiple days! They don't taste very good raw though.");
    Object* wallet = new Object("\033[4mWallet\033[0m", "A brown leather wallet with \033[1m$70\033[0m in it! You wonder whose it is but there's no identification inside.");
    Object* dog_food_bag = new Object("\033[4mDog Food Bag\033[0m", "A bag of food for your dog! ... \033[3mIt doesn't taste very good.\033[0m");
	Object* bucket = new Object("\033[4mBucket\033[0m", "An old metal bucket which can be used to collect water from the well.");


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


    findLocation(HOME_BACKDOOR)->addLocationObject(chewtoy);
    findLocation(HOME_KITCHEN)->addLocationObject(burger);
    findLocation(EASTERN_FOREST_EDGE)->addLocationObject(dog);
    findLocation(FOUR_LINCOLN_COURT_FRONT_DOOR)->addLocationObject(firewood);
    findLocation(TWELVE_HUESTON_AVE_FRONT_DOOR)->addLocationObject(coal);
    findLocation(FIVE_HUESTON_AVE_FRONT_DOOR)->addLocationObject(firewood);
    findLocation(THREE_HUESTON_AVE_FRONT_DOOR)->addLocationObject(fire_axe);
    findLocation(THREE_HUESTON_AVE_LIVING_ROOM)->addLocationObject(half_generator);
    findLocation(ONE_HUESTON_AVE_FRONT_DOOR)->addLocationObject(potato_sack);
    findLocation(ONE_TWELVE_MAIN_STREET_SIDE_DOOR)->addLocationObject(wooden_planks);
    findLocation(TOWN_DINER_BACKLOT)->addLocationObject(burger_bag);
    findLocation(GROCERY_STORE_ENTRANCE)->addLocationObject(dog_food_bag);
    findLocation(GROCERY_STORE_BACKLOT)->addLocationObject(silver_key);
    findLocation(ARCADE_ALLEY)->addLocationObject(wallet);
    findLocation(TOWN_GARDEN)->addLocationObject(cabbage);
    findLocation(HOME_BATHROOM)->addLocationObject(bucket);
}

void World::createLocation(LOCATION_ENUMS location_enum, std::string name, std::string description, bool allowsSleep, bool isIndoors) {
    Location* newLocation = new Location(name, description, allowsSleep, isIndoors);
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


void World::addConnectedLocation(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2) {
    if (isLocationConnected(loc_enum1,loc_enum2) == false) {                  //IF loc_enum2 isn't already connected to loc_enum1...    (and isLocationConnected already returns false if one or both location enums are invalid)
        locationConnectionsMap[loc_enum1];                                    //    create mapping entry for loc_enum1 if it doesn't already exist. both the provided enum and the new vector are created by this, the vector being empty.
        auto& locationEntry = *locationConnectionsMap.find(loc_enum1);        //    gets the mapping entry we just created OR the already existing entry
        locationEntry.second.push_back(loc_enum2);                            //    adds the second location to the vector

    }
}


