#include "World.h"
#include <iostream>
#include <unordered_map>
#include <string>

//Helper function encompassing the creation of location instances & updating of locationNumToPointer with new location entry.
void World::createLocation(LOCATION_ENUMS location_enum, std::string name, std::string description) {
    Location* newLocation = new Location(name, description);
    //take the enum & location pointer and add them to the unordered map
    locationEnumToPointer.insert_or_assign(location_enum,newLocation);
}

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
    findLocation(HOME_BEDROOM)->addConnectedLocation(findLocation(HOME_LIVINGROOM));
    findLocation(HOME_BEDROOM)->addConnectedLocation(findLocation(HOME_BATHROOM));
    findLocation(HOME_LIVINGROOM)->addConnectedLocation(findLocation(HOME_KITCHEN));

    findLocation(HOME_LIVINGROOM)->addConnectedLocation(findLocation(HOME_BATHROOM));
    findLocation(HOME_LIVINGROOM)->addConnectedLocation(findLocation(HOME_BACKDOOR));
    findLocation(HOME_BACKDOOR)->addConnectedLocation(findLocation(HOME_BACKYARD));
    findLocation(HOME_KITCHEN)->addConnectedLocation(findLocation(HOME_FRONTDOOR));
    findLocation(HOME_FRONTDOOR)->addConnectedLocation(findLocation(HOME_FRONTPORCH));
    findLocation(HOME_BACKYARD)->addConnectedLocation(findLocation(SOUTHERN_FOREST_EDGE));

    findLocation(HOME_BACKDOOR)->addLocationObject(chewtoy);
}


//returns True if the provided location enum is anything other than INVALID_LOCATION
bool World::isValidLocation(LOCATION_ENUMS loc_enum) {
    if (loc_enum == INVALID_LOCATION) {
        return false;
    }
    else {
        return true;
    }
}
//finds the location enum based on the provided location name, ignoring preceding/exceding white spaces or capitalization. if it cannot find one it returns the INVALID_LOCATION enum
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
//search the outputs mapping for the location name which matches the provided location enum. if it cannot find one it returns the string "INVALID_LOCATION"
std::string World::locationString(LOCATION_ENUMS loc_enum) {
    for (const auto& mapping : locationOutputMap) {
        if (mapping.first == loc_enum) {
            return mapping.second;
        }
    }
    return "INVALID_LOCATION";
}

//search unordered map of locationEnumToPointer and return location pointer and if not found return a nullptr
Location* World::findLocation(LOCATION_ENUMS loc_enum) {
    for (const auto& mapping : locationEnumToPointer) {
        if (mapping.first == loc_enum) {
            return mapping.second;
        }
    }

    return nullptr;

}

//returns True if the second location is connected to the first location (aka if a player currently at first location can move to second location)
bool World::isLocationConnected(LOCATION_ENUMS loc_enum1, LOCATION_ENUMS loc_enum2) {
    if (isValidLocation(loc_enum1) && isValidLocation(loc_enum2)) {
        for (Location* loc : findLocation(loc_enum1)->getConnectedLocations()) {
            if (findLocation(loc_enum2)->getName() == loc->getName()) {
                return true;
            }
        }
        return false;
    }
    else {
        return false;
    }
}


