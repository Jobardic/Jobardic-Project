// Jobardic-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "Location.h"
#include "Character.h"
#include "InputPrompts.h"
#include "InputChoice.h"
#include "StoryEvent.h"
#include "Commands.h"
#include "UI.h"
#include "World.h"
#include "Time.h"



int main()
{
    World* world = new World();
    Character player(World::INITIAL_LOCATION);

    bool wellDry = false;
    bool bucketFilled = false;

    InputChoice progress("==>");
    std::vector<InputChoice*> choices = { &progress };
    InputPrompts opening(choices);
    std::string openingDesc = "You wake in your bedroom ready to start the day.\nYou turn on your radio to listen to the news while you get dressed.\n\"Breaking News : There has been an explosion on the moon.It is as of yet unknown how this event came to be but\nscientists warn that the resulting loss in velocity will cause the moon to descend to earth.Astrophysicists and \nastronauts   across the world are working hard to prevent what could be a modern day Chickulub.Now for the\nweather…\"\nYou turn off the radio and stand in disbelief.After the shock has washed over you you decide to get moving.If the moon is\nreally falling you should probably prepare.";
    Location* start = world->World::findLocation(World::LOCATION_ENUMS::HOME_BACKDOOR);

    StoryEvent* openingSequence = new StoryEvent(openingDesc, start, &opening);
    //StoryEvent openingSequence(cat, start, &opening);

    //===================================================================================================





    //Opening Secuence with basic game loop
    //===================================================================================================
    bool quit = false;
    do {
        system("cls");
        UI::displayOutput(openingSequence);
        std::string userInput;
        std::cin >> userInput;
        if (UI::parseUserInput(userInput) == Commands::Progress) {
            quit = true;
        }
        else {
            std::cout << "Unrecognized Command. Please try again." << "\n";
        }
    } while (quit == false);

    //===================================================================================================





    //===================================================================================================










    do {

        std::string playerInput;
        bool validInput = false;

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

        while (validInput == false) {
            std::getline(std::cin, playerInput);
            if (playerInput != "Look" && playerInput != "Move" && playerInput != "Inventory" && playerInput != "Wait" && playerInput != "Sleep" && playerInput != "Fill Bucket") {
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


        else if (playerInput == "Fill Bucket") {

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

            std::cout << "Press Enter to continue...";
            std::getline(std::cin, playerInput);
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

                std::cout << "\nType 'Drink Water' to drink from your bucket.";
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

                else if (playerInput == "Drink Water") {

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

                    std::cout << "Press Enter to continue...";
                    std::getline(std::cin, playerInput);
                }
            }
        }

        else if (playerInput == "Wait") {
            std::cout << player.Wait();
            std::cout << "\nPress enter to continue";
            std::getline(std::cin, playerInput);
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
                    player.decreaseThirst();
                    player.changeEnergy(-1);
                }
            }
            
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
