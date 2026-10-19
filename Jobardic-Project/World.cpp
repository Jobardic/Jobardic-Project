#include "World.h"
#include <iostream>
#include <unordered_map>
#include <string>

World::World() {
    Location* homeBedroom = new Location("Home Bedroom", "You are now in your bedroom.");
    Location* homeKitchen = new Location("Home Kitchen", "You are now in your kitchen.");
    Location* homeLivingRoom = new Location("Home Living Room", "You are now in your living room.");
    Location* homeBathroom = new Location("Home Bathroom", "You are now in your bathroom.");
    Location* homeFrontDoor = new Location("Home Front Door", "You are now at the front door to your home from the inside");
    Location* homeFrontPorch = new Location("Home Front Porch", "You are now outside on your front porch");
    Location* homeBackDoor = new Location("Home Back Door", "You are now at the back door to your home from the inside");
    Location* homeBackyard = new Location("Home Backyard", "You are now outside in your backyard");

    Object* chewtoy = new Object("Chewtoy", "It is your dog's favorite chewtoy, which reminds you that you haven't seen your dog all morning");

    homeBedroom->addConnectedLocation(homeLivingRoom);
    homeBedroom->addConnectedLocation(homeBathroom);
    homeLivingRoom->addConnectedLocation(homeKitchen);
    homeLivingRoom->addConnectedLocation(homeBathroom);
    homeLivingRoom->addConnectedLocation(homeBackDoor);
    homeBackDoor->addConnectedLocation(homeBackyard);
    homeKitchen->addConnectedLocation(homeFrontDoor);
    homeFrontDoor->addConnectedLocation(homeFrontPorch);

    homeBackDoor->addLocationObject(chewtoy);

    allLocations.push_back(homeBedroom);
    allLocations.push_back(homeKitchen);
    allLocations.push_back(homeLivingRoom);
    allLocations.push_back(homeBathroom);
    allLocations.push_back(homeFrontDoor);
    allLocations.push_back(homeFrontPorch);
    allLocations.push_back(homeBackDoor);
    allLocations.push_back(homeBackyard);
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
            i++;
        }
        else {
            break;
        }
    }
    //remove capitalization
    for (int i = 0; i < name.length(); i++) {
        name[i] = std::tolower(name[i]);
    }



    for (const auto& mapping : locationInputMap) {
        if (mapping.first == name) {
            return mapping.second;
        }
    }
    return INVALID_LOCATION;

}

std::string World::locationString(LOCATION_ENUMS loc_enum) {
    for (const auto& mapping : locationOutputMap) {
        if (mapping.first == loc_enum) {
            return mapping.second;
        }
    }
    return "INVALID_LOCATION";
}

/*

Location* World::findLocation(LOCATION_ENUMS loc_enum) {


}

*/

