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
    Location innerWoods("Inner Woods", "You are now in the middle of the woods");
    Location northForestEdge("North Forest Edge", "You are now at the northern edge of the forest");
    Location eastForestEdge("East Forest Edge", "You are now at the eastern edge of the forest");
    Location westForestEdge("West Forest Edge", "You are now at the western edge of the forest");
    //South Forest Edge is a different story, will wait for Matthew to do the refactor

    Object chewtoy("Chewtoy", "It is your dog's favorite chewtoy, which reminds you that you haven't seen your dog all morning");
    Object burger("Burger", "A delicious burger is waiting in the oven.");
    Object dog("Your Dog", "Your loyal dog! His favorite toy is his chewtoy");

    homeBedroom.addConnectedLocation(&homeLivingRoom);
    homeBedroom.addConnectedLocation(&homeBathroom);
    homeLivingRoom.addConnectedLocation(&homeKitchen);
    homeLivingRoom.addConnectedLocation(&homeBathroom);
    homeLivingRoom.addConnectedLocation(&homeBackDoor);
    homeBackDoor.addConnectedLocation(&homeBackyard);
    homeKitchen.addConnectedLocation(&homeFrontDoor);
    homeFrontDoor.addConnectedLocation(&homeFrontPorch);
    innerWoods.addConnectedLocation(&northForestEdge);
    innerWoods.addConnectedLocation(&westForestEdge);
    innerWoods.addConnectedLocation(&eastForestEdge);

    homeBackDoor.addLocationObject(&chewtoy);
    homeKitchen.addLocationObject(&burger);
    eastForestEdge.addLocationObject(&dog);

    Character player(&homeBedroom);

    

    //===================================================================================================


























    //Location Exploration Functionality
    //=============================================================================================
    
    do {

        std::string playerInput;
        bool validInput = false;

        system("cls");
        std::cout << std::endl;

        std::cout << "Energy: " << player.getEnergy() << " / " << player.getMaxEnergy(); //substitute for energy bar
        std::cout << "\nFood: " << player.getFood() << " / " << player.getMaxFood(); // substitute for food bar
        std::cout << "\n\n-------------------------------------\n\n";


        if (player.getCurrentLocation() == &homeKitchen) {
            for (Object* item : homeKitchen.getLocationObjects()) {
                if (item->getName() == "Burger") {
                    std::cout << "There is a burger waiting in the oven!"
                        << std::endl << std::endl;
                    break;
                }
            }
        }


        std::cout << player.getCurrentLocation()->getDescription() << std::endl << std::endl;
        std::cout << "What would you like to do now?" << std::endl;
        std::cout << "==== Look" << std::endl;
        std::cout << "==== Move" << std::endl;
        std::cout << "==== Inventory" << std::endl;
        std::cout << std::endl;

        while (validInput == false) {
            std::getline(std::cin, playerInput);
            if (playerInput != "Look" && playerInput != "Move" && playerInput != "Inventory") {
                std::cout << "I don't know what you mean! Try again" << std::endl;
            }
            else {
                validInput = true;
            }
        }

        if (playerInput == "Look"){ //Player wants to look around the location
            validInput = false; //change validInput to false to recieve new input
            std::cout << std::endl << "You look around and find..." << std::endl;
            if (player.getCurrentLocation()->getLocationObjects().size() == 0) { //if there are no objects then print that
                std::cout << "...Nothing!" << std::endl << "Press enter to return to menu";
                std::getline(std::cin, playerInput);
            } else 
            {
                for (Object* ob : player.getCurrentLocation()->getLocationObjects()) { // gets all the objects in the location to loop through
                    std::cout << ob->getName() << ": " << ob->getDescription() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "What would you like to take?" << std::endl;
                while (validInput == false) {
                    std::getline(std::cin, playerInput); //takes in player input
                    for (int i = 0; i < player.getCurrentLocation()->getLocationObjects().size(); i++) { //loops through the objects again to check if any of them match
                        if (playerInput == player.getCurrentLocation()->getLocationObjects()[i]->getName()) { //what the player inputed
                            validInput = true;
                            player.pickUpObject(player.getCurrentLocation()->getLocationObjects()[i]); //if it does, place in player inv and remove from location inv
                            player.getCurrentLocation()->removeLocationObject(i);
                        }
                        else if (playerInput == "" || playerInput == "Nothing" || playerInput == "None") { //if they just hit enter or type nothing, take them out of the menu
                            validInput = true;
                        }
                    }
                    if (validInput == false) //if it's not a valid input, let them try again
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

                std::cout << "\nType 'Eat Burger' to eat the burger.";
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
