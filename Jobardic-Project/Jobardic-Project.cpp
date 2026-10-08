// Jobardic-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Location.h"
#include "Character.h"


int main()
{
    //Initializing the game world
    //===============================================================================================
    Location homeBedroom("Home Bedroom", "You are now in your bedroom.");
    Location homeKitchen("Home Kitchen", "You are now in your kitchen.");
    Location homeLivingRoom("Home Living Room", "You are now in your living room.");
    Location homeBathroom("Home Bathroom", "You are now in your bathroom.");
    Location homeFrontDoor("Home Front Door", "You are now at the front door to your home from the inside");
    Location homeFrontPorch("Home Front Porch", "You are now outside on your front porch");
    Location homeBackDoor("Home Back Door", "You are now at the back door to your home from the inside");
    Location homeBackyard("Home Backyard", "You are now outside in your backyard"); //renaming name argument from "Home Back Porch" to "Home Backyard" to match the description argument and variable name

    homeBedroom.addConnectedLocation(&homeLivingRoom);
    homeBedroom.addConnectedLocation(&homeBathroom);
    homeLivingRoom.addConnectedLocation(&homeKitchen);
    homeLivingRoom.addConnectedLocation(&homeBathroom);
    homeLivingRoom.addConnectedLocation(&homeBackDoor);
    homeBackDoor.addConnectedLocation(&homeBackyard);
    homeKitchen.addConnectedLocation(&homeFrontDoor);
    homeFrontDoor.addConnectedLocation(&homeFrontPorch);

    Character player(&homeBedroom);

    

    //===================================================================================================


























    //Location Exploration Functionality
    //=============================================================================================
    
    do {

        std::string playerInput;
        bool validInput = false;

        system("cls");
        std::cout << std::endl;
		std::cout << "Health: " << player.getEnergy() << std::endl;
        std::cout << player.getCurrentLocation()->getDescription() << std::endl << std::endl;
        std::cout << "What would you like to do now?" << std::endl;
        std::cout << "==== Nothing" << std::endl;
        std::cout << "==== Move" << std::endl << std::endl;

        

        while (validInput == false) {
            std::getline(std::cin, playerInput);
            if (playerInput != "Nothing" && playerInput != "Move") {
                std::cout << "I don't know what you mean! Try again" << std::endl;
            }
            else {
                validInput = true;
            }
        }

        if (playerInput == "Nothing") {
            return false;
        }
        else {

            std::cout << std::endl;
            std::cout << "Where would you like to move to?" << std::endl;
            for (Location* possibleLocation : player.getCurrentLocation()->getConnectedLocations()) {
                std::cout << "==== " << possibleLocation->getName() << std::endl;
            }
            std::cout << std::endl;
            
            validInput = false;
            while (validInput == false) {
                std::getline(std::cin, playerInput);

                for (Location* loc : player.getCurrentLocation()->getConnectedLocations()) {
                    if (playerInput == loc->getName()) {
                        validInput = true;
                        player.setCurrentLocation(loc);
                    }
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
    //=======================================================================================

    std::cout << "Hello World!\n";
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
