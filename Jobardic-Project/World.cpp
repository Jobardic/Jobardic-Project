#include "World.h"
#include <iostream>
#include <unordered_map>
#include <string>

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
    createLocation(HOME_BEDROOM, "Home Bedroom", "You are now in your bedroom.");
    createLocation(HOME_KITCHEN, "Home Kitchen", "You are now in your kitchen.");
    createLocation(HOME_LIVINGROOM, "Home Living Room", "You are now in your living room.");
    createLocation(HOME_BATHROOM, "Home Bathroom", "You are now in your bathroom.");
    createLocation(HOME_FRONTDOOR, "Home Front Door", "You are now at the front door to your home from the inside");
    createLocation(HOME_FRONTPORCH, "Home Front Porch", "You are now outside on your front porch");
    createLocation(HOME_BACKDOOR, "Home Back Door", "You are now at the back door to your home from the inside");
    createLocation(HOME_BACKYARD, "Home Backyard", "You are now outside in your backyard");
    createLocation(SOUTHERN_FOREST_EDGE, "Southern Forest Edge", "You are now standing at the edge of the forest behind your backyard, which is the southern-most area of the forest.");

    Object* chewtoy = new Object("Chewtoy", "It is your dog's favorite chewtoy, which reminds you that you haven't seen your dog all morning");


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


    findLocation(HOME_BACKDOOR)->addLocationObject(chewtoy);
}

void World::createLocation(LOCATION_ENUMS location_enum, std::string name, std::string description) {
    Location* newLocation = new Location(name, description);
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
    
    
    //Erase white spaces in the beginning 
    for (int i = 0; i < name.length(); i++) {
        if (name[i] == ' ') {
            name.erase(i,1);
            i--;
        }
        else {
            break;
        }
    }
    //Erase white spaces in the end
    for (int i = name.length() - 1; i >= 0; i--) {
        if (name[i] == ' ') {
            name.erase(i, 1);
        }
        else {
            break;
        }
    }
    //remove capitalization
    for (int i = 0; i < name.length(); i++) {
        name[i] = std::tolower(name[i]);
    }


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


