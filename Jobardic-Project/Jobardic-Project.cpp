// Jobardic-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Location.h"
#include "Character.h"
#include "World.h"


int main()
{
    World* world = new World();
    Character player(World::INITIAL_LOCATION);



    while (true) {
        std::string playerInput;
        std::getline(std::cin, playerInput);
        if (playerInput == "e") {
            break;
        }
        auto foundLocation = world->findLocation(playerInput);

        std::cout << world->locationString(foundLocation) << std::endl;
        if (world->isValidLocation(foundLocation)) {
            std::cout << world->findLocation(foundLocation)->getDescription() << std::endl;
        }
    }



    
    do {

        std::string playerInput;
        bool validInput = false;

        system("cls");
        std::cout << std::endl;

        std::cout << "Energy: " << player.getEnergy() << " / " << player.getMaxEnergy(); //substitute for energy bar
        std::cout << "\n\n-------------------------------------\n\n";

        std::cout << world->findLocation(player.getCurrentLocation())->getDescription() << std::endl << std::endl;
        std::cout << "What would you like to do now?" << std::endl;
        std::cout << "==== Look" << std::endl;
        std::cout << "==== Move" << std::endl << std::endl;

        while (validInput == false) {
            std::getline(std::cin, playerInput);
            if (playerInput != "Look" && playerInput != "Move") {
                std::cout << "I don't know what you mean! Try again" << std::endl;
            }
            else {
                validInput = true;
            }
        }

        if (playerInput == "Look"){
            validInput = false;
            std::cout << std::endl << "You look around and find..." << std::endl;
            if (world->findLocation(player.getCurrentLocation())->getLocationObjects().size() == 0) {
                std::cout << "...Nothing!" << std::endl << "Press enter to return to menu";
                std::getline(std::cin, playerInput);
            } else {
                for (Object* ob : world->findLocation(player.getCurrentLocation())->getLocationObjects()) { // gets all the objects in the location to loop through
                    std::cout << ob->getName() << ": " << ob->getDescription() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "What would you like to take?" << std::endl;
                while (validInput == false) {
                    std::getline(std::cin, playerInput);
                    for (int i = 0; i < world->findLocation(player.getCurrentLocation())->getLocationObjects().size(); i++) {
                        if (playerInput == world->findLocation(player.getCurrentLocation())->getLocationObjects()[i]->getName()) {
                            validInput = true;
                            player.pickUpObject(world->findLocation(player.getCurrentLocation())->getLocationObjects()[i]);
                            world->findLocation(player.getCurrentLocation())->removeLocationObject(i);
                        }
                        else if (playerInput == "") {
                            validInput = true;
                        }
                    }
                    if (validInput == false)
                    {
                        std::cout << "This object doesn't exist here! Try again" << std::endl;
                    }
                }
            }
        }
        else { //shows player the locations they can go

            std::cout << std::endl;
            std::cout << "Where would you like to move to?" << std::endl;
            

            //world->findLocation(player.getCurrentLocation())->outputConnectedLocations();
            world->outputLocationConnections(player.getCurrentLocation());
            
            std::cout << std::endl;
            
            validInput = false;
            while (validInput == false) { //asks user where they want to go and if they input a valid location their location is set to it
                std::getline(std::cin, playerInput);
                World::LOCATION_ENUMS inputLocation = world->findLocation(playerInput);

                if (world->isLocationConnected(player.getCurrentLocation(), inputLocation)) {
                    validInput = true;
                    player.setCurrentLocation(inputLocation);
                }

                if (validInput == false)
                {
                    std::cout << "That location doesn't exist here! Try again" << std::endl;
                }
                else
                {
                    player.decreaseEnergy();
                }
            }
            
        }
		if (player.isCharacterExhausted()) {
			std::cout << "You have run out of energy and can no longer continue your journey." << std::endl;
			break;
		}
    } while (true);

}

// DO: output possible move locations done by world class directly
// DO: proper commments like talked about
//        e.g how to properly add a location
// DO: removing need for locationOutputMap
// DO?: changing it such that world has connected locations data instead
// DO: other github comment recommendations

//Outside of scope of story: refactoring OBJECT stuff
