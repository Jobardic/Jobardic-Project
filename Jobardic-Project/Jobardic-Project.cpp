// Jobardic-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Location.h"
#include "Character.h"
#include "World.h"
#include "Time.h"

int main()
{
    World* world = new World();
    Character player(World::INITIAL_LOCATION,100);
    
    do {

        std::string playerInput;
        bool validInput = false;

        system("cls");
        std::cout << std::endl;

        std::cout << Time::timeDisplay() << std::endl;
        std::cout << "Energy: " << player.getEnergy() << " / " << player.getMaxEnergy(); //substitute for energy bar
        std::cout << "\nFood: " << player.getFood() << " / " << player.getMaxFood(); // substitute for food bar
        std::cout << "\n\n-------------------------------------\n\n";


        if (player.getCurrentLocation() == World::HOME_KITCHEN) {
            for (Object* item : world->findLocation(player.getCurrentLocation())->getLocationObjects()) {
                if (item->getName() == "Burger") {
                    std::cout << "There is a burger waiting in the oven!"
                        << std::endl << std::endl;
                    break;
                }
            }
        }


        std::cout << world->findLocation(player.getCurrentLocation())->getDescription() << std::endl << std::endl;
        std::cout << "What would you like to do now?" << std::endl;
        std::cout << "==== Look" << std::endl;
        std::cout << "==== Move" << std::endl;
        std::cout << "==== Inventory" << std::endl;
		if (world->findLocation(player.getCurrentLocation())->canPlayerSleepHere()) {
            std::cout << "==== Sleep" << std::endl;
		}
        std::cout << std::endl;

        while (validInput == false) {
            std::getline(std::cin, playerInput);
            if (playerInput != "Look" && playerInput != "Move" && playerInput != "Inventory" && playerInput != "Sleep") {
                std::cout << "I don't know what you mean! Try again" << std::endl;
            }
            else {
                validInput = true;
            }
        }

        if (playerInput == "Look"){
            validInput = false;
            std::cout << std::endl << "You look around and find..." << std::endl;
            if (world->findLocation(player.getCurrentLocation())->getLocationObjects().size() == 0) { //checks to see if the location has objects
                std::cout << "...Nothing!" << std::endl << "Press enter to return to menu"; //if not, present nothing
                std::getline(std::cin, playerInput);
            } else {
                for (Object* ob : world->findLocation(player.getCurrentLocation())->getLocationObjects()) { // loops through all the objects in the location to print
                    std::cout << ob->getName() << ": " << ob->getDescription() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "What would you like to take?" << std::endl;
                while (validInput == false) {
                    std::getline(std::cin, playerInput);
                    for (int i = 0; i < world->findLocation(player.getCurrentLocation())->getLocationObjects().size(); i++) { // searches for the typed object in the location inventory
                        if (playerInput == world->findLocation(player.getCurrentLocation())->getLocationObjects()[i]->getName()) { // if that object is there
                            validInput = true;
                            player.pickUpObject(world->findLocation(player.getCurrentLocation())->getLocationObjects()[i]); // put it in the player's inventory
                            world->findLocation(player.getCurrentLocation())->removeLocationObject(i); // and remove it from the location inventory
                        }
                        else if (playerInput == "") { // exit without taking anything
                            validInput = true;
                        }
                    }
                    if (validInput == false) // if object was not found they can try again
                    {
                        std::cout << "This object doesn't exist here! Try again" << std::endl;
                    }
                }
            }
        }


        else if (playerInput == "Inventory") {

            std::cout << "\nYour Inventory:\n";

            std::vector<Object*> items = player.getInventory();

            if (items.empty()) {
                std::cout << "Your inventory is empty.\n";
                std::cout << "\nPress Enter to continue:";
                std::getline(std::cin, playerInput);
            }
            else {
                for (Object* item : items) {
                    std::cout << "==== " << item->getName() << "\n";
                }

                std::cout << "\nType 'Eat [Food]' to eat food."; //Man cannot live off burger alone
                std::cout << "\nPress Enter to return.\n";

                std::getline(std::cin, playerInput);

                if (playerInput == "Eat Burger") {
                    bool burgerFound = false;

                    for (int i = 0; i < static_cast<int>(items.size()); i++) {
                        if (items[i]->getName() == "Burger") {

                            player.increaseFood(25);
                            player.removeInventoryObject(i);

                            std::cout << "\nYou ate the burger!\n";
                            burgerFound = true;
                            break;
                        }
                    }

                    if (!burgerFound) {
                        std::cout << "You don't have a burger.\n";
                    }

                    std::cout << "Press Enter to continue...";
                    std::getline(std::cin, playerInput);
                }
            }
        }

		else if (playerInput == "Sleep") {
            std::cout << player.Sleep(world->findLocation(player.getCurrentLocation())->canPlayerSleepHere());
            std::cout << "\nPress enter to continue";   // To-Do: figure out better way to handle clearing screen after inputs
            std::getline(std::cin, playerInput);
		}
        
        else {

            std::cout << std::endl;
            std::cout << "Where would you like to move to?" << std::endl;
            


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
                    player.changeEnergy(-1);
                }
            }
            
        }
		if (player.isCharacterExhausted()) {
			std::cout << "You have run out of energy and can no longer continue your journey." << std::endl;
			break;
		}
    } while (true);

}
