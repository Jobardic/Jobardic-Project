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
    Character player(World::INITIAL_LOCATION);

	bool wellDry = false;
	bool bucketFilled = false;
    
    do {

        //std::string playerInput;
        //bool validInput = false;

        system("cls");
        std::cout << std::endl;
        std::cout << Time::timeDisplay() << std::endl;
        std::cout << "Energy: " << player.getEnergy() << " / " << player.getMaxEnergy() << std::endl; //substitute for energy bar
        std::cout << "Thirst: " << player.getThirst() << " / " << player.getMaxThirst() << std::endl; // substitute for thirst bar
        std::cout << "Food: " << player.getFood() << " / " << player.getMaxFood() << std::endl; // substitute for food bar
        std::cout << "\n-------------------------------------\n\n";


        if (player.getCurrentLocation() == World::HOME_KITCHEN) {
            for (Object* item : world->findLocation(player.getCurrentLocation())->getLocationObjects()) {
                if (item->getName() == "Burger") {
                    std::cout << "There is a burger waiting in the oven!"
                        << std::endl << std::endl;
                    break;
                }
            }
        }

        // NEW: Water well description
        if (world->findLocation(player.getCurrentLocation()) == world->findLocation(World::WATER_WELL)) {

            if (wellDry) {
                std::cout << "The well has dried up. "
                    << "There is no water left.\n\n";
            }
            else {
                bool hasBucket = false;

                for (Object* item : player.getInventory()) {
                    if (item->getName() == "Bucket") {
                        hasBucket = true;
                        break;
                    }
                }

                if (hasBucket) {
                    std::cout << "You can fill your bucket "
                        << "with water here!\n\n";
                }
                else {
                    std::cout << "You see a well full of water. "
                        << "Bring a bucket to collect some!\n\n";
                }
            }
        }

        std::cout << world->findLocation(player.getCurrentLocation())->getDescription() << std::endl << std::endl;
        std::cout << "What would you like to do now?" << std::endl;
        std::cout << "==== Look" << std::endl;
        std::cout << "==== Move" << std::endl;
        std::cout << "==== Inventory" << std::endl;
		std::cout << "==== Wait" << std::endl;  // new player action: waiting
		if (world->findLocation(player.getCurrentLocation())->canPlayerSleepHere()) {
            std::cout << "==== Sleep" << std::endl;
		}
        if (world->findLocation(player.getCurrentLocation()) == world->findLocation(World::WATER_WELL)) {
            std::cout << "==== Fill Bucket" << std::endl;
        }
        std::cout << std::endl;
        /*
        while (validInput == false) {
            std::getline(std::cin, playerInput);
            if (playerInput != "Look" && playerInput != "Move" && playerInput != "Inventory" && playerInput != "Wait" && playerInput != "Sleep" && playerInput != "Fill Bucket") {
                std::cout << "I don't know what you mean! Try again" << std::endl;
            }
            else {
                validInput = true;
            }
        }*/

        std::string playerAction = InputHandler::getUserInput();

        if (playerAction == "look"){
            std::cout << std::endl << "You look around and find..." << std::endl;
            if (world->findLocation(player.getCurrentLocation())->getLocationObjects().size() == 0) { //checks to see if the location has objects
                std::cout << "...Nothing!" << std::endl;
                InputHandler::waitForUser();
            } else {
                for (Object* ob : world->findLocation(player.getCurrentLocation())->getLocationObjects()) { // loops through all the objects in the location to print
                    std::cout << ob->getName() << ": " << ob->getDescription() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "What would you like to take?" << std::endl;

                bool loop = true;
                while(loop){
                    std::string objectInput = InputHandler::getUserInput();
                    if (objectInput == "") {
                        loop = false;
                    }
                    else if (world->findLocation(player.getCurrentLocation())->hasObject(objectInput)) {
                        auto object = world->findLocation(player.getCurrentLocation())->findLocationObject(objectInput);
                        player.pickUpObject(object);
                        world->findLocation(player.getCurrentLocation())->removeLocationObject(object->getName());
                        loop = false;

                    }
                    else {
                        std::cout << "This object doesn't exist here! Try again" << std::endl;
                    }
                } 
                
            }
        }


        else if (playerAction == "fill bucket") {

            if (world->findLocation(player.getCurrentLocation()) != world->findLocation(World::WATER_WELL)) {
                std::cout << "There is no well here.\n";
            }
            else if (wellDry) {
                std::cout << "The well has dried up!\n";
            }
            else {
                bool hasBucket = false;

                for (Object* item : player.getInventory()) {
                    if (item->getName() == "Bucket") {
                        hasBucket = true;
                        break;
                    }
                }

                if (!hasBucket) {
                    std::cout << "You need to bring a bucket "
                        << "to collect water.\n";
                }
                else if (bucketFilled) {
                    std::cout << "Your bucket is already full!\n";
                }
                else {
                    bucketFilled = true;
                    wellDry = true;

                    std::cout << "You filled your bucket "
                        << "with fresh water!\n";

                    std::cout << "The well has now dried up!\n";
                }
            }

            InputHandler::waitForUser();
        }



        else if (playerAction == "inventory") {

            std::cout << "\nYour Inventory:\n";

            std::vector<Object*> items = player.getInventory();

            if (items.empty()) {
                std::cout << "Your inventory is empty.\n";
                InputHandler::waitForUser();
            }
            else {
                for (Object* item : items) {
                    std::cout << "==== " << item->getName() << "\n";
                }

                std::cout << "\nType 'Drink Water' to drink from your bucket.";
                std::cout << "\nType 'Eat [Food]' to eat food."; //Man cannot live off burger alone
                std::cout << "\nPress Enter to return.\n";

                std::string playerInventoryAction = InputHandler::getUserInput();

                if (playerInventoryAction == "eat burger") {
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

                    InputHandler::waitForUser();
                }

                else if (playerInventoryAction == "drink water") {

                    bool hasBucket = false;

                    for (Object* item : player.getInventory()) {
                        if (item->getName() == "Bucket") {
                            hasBucket = true;
                            break;
                        }
                    }

                    if (!hasBucket) {
                        std::cout << "\nYou do not have a bucket!\n";
                    }
                    else if (!bucketFilled) {
                        std::cout << "\nYour bucket is empty!\n";
                    }
                    else {
                        player.increaseThirst(40);
                        bucketFilled = false;

                        std::cout << "\nYou drank the water!\n";
                        std::cout << "Your thirst has been restored!\n";
                    }

                    InputHandler::waitForUser();
                }
            }
        }

        else if (playerAction == "wait") {
            std::cout << player.Wait();
            InputHandler::waitForUser();
        }

        else if (playerAction == "sleep") {
            std::cout << player.Sleep(world->findLocation(player.getCurrentLocation())->canPlayerSleepHere());
            InputHandler::waitForUser();
        }
        
        else if (playerAction == "move") {

            std::cout << std::endl;
            std::cout << "Where would you like to move to?" << std::endl;
            


            world->outputLocationConnections(player.getCurrentLocation());
            
            std::cout << std::endl;
            
            bool loop = true;
            while (loop) { //if they input a valid location their location is set to it
                World::LOCATION_ENUMS inputLocation = world->findLocation(InputHandler::getUserInput());

                if (world->isLocationConnected(player.getCurrentLocation(), inputLocation)) {
                    player.setCurrentLocation(inputLocation);
                    loop = false;
                    player.decreaseThirst();
                    player.changeEnergy(-1);
                }
                else {
                    std::cout << "That location doesn't exist here! Try again" << std::endl;
                }

            }

            
            
        }
        else if (playerAction != "") {
            std::cout << "I don't know what you mean! Try again" << std::endl;
            InputHandler::waitForUser();
        }
		if (player.isCharacterExhausted()) {
			std::cout << "You have run out of energy and can no longer continue your journey." << std::endl;
			break;
		}
    } while (true);


   /* void PrintDeathScreen(std::string reason) {
        system("cls");

        std::cout << "\n";
        std::cout << "====================================\n";
        std::cout << "             GAME OVER              \n";
        std::cout << "====================================\n\n";

        std::cout << "You have died!\n\n";
        std::cout << "Cause of death: " << reason << "\n\n";

        std::cout << "====================================\n";
        std::cout << "         Press R to Restart         \n";
        std::cout << "         Press Q to Quit            \n";
        std::cout << "====================================\n\n";
    }*/

}
