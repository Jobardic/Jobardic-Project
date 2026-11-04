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
    Location waterWell("Water Well", "You are standing beside an old water well.");

    Object chewtoy("Chewtoy", "It is your dog's favorite chewtoy, which reminds you that you haven't seen your dog all morning");
    Object burger("Burger", "A delicious burger is waiting in the oven.");
    Object bucket("Bucket", "An empty bucket that can hold water.");
    
    bool wellDry = false;
    bool bucketFilled = false;

    homeBedroom.addConnectedLocation(&homeLivingRoom);
    homeBedroom.addConnectedLocation(&homeBathroom);
    homeLivingRoom.addConnectedLocation(&homeKitchen);
    homeLivingRoom.addConnectedLocation(&homeBathroom);
    homeLivingRoom.addConnectedLocation(&homeBackDoor);
    homeBackDoor.addConnectedLocation(&homeBackyard);
    homeBackyard.addConnectedLocation(&waterWell);
    homeKitchen.addConnectedLocation(&homeFrontDoor);
    homeFrontDoor.addConnectedLocation(&homeFrontPorch);

    homeBackDoor.addLocationObject(&chewtoy);
    homeKitchen.addLocationObject(&burger);
    homeBathroom.addLocationObject(&bucket);

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
        std::cout << "Food: " << player.getFood() << " / " << player.getMaxFood(); // substitute for food bar
        std::cout << "Thirst: " << player.getThirst() << " / " << player.getMaxThirst(); // substitute for thirst bar
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

        // NEW: Water well description
        if (player.getCurrentLocation() == &waterWell) {

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

        std::cout << player.getCurrentLocation()->getDescription() << std::endl << std::endl;
        std::cout << "What would you like to do now?" << std::endl;
        std::cout << "==== Look" << std::endl;
        std::cout << "==== Move" << std::endl << std::endl;
		std::cout << "==== Inventory" << std::endl << std::endl;

        if (player.getCurrentLocation() == &waterWell) {
            std::cout << "==== Fill Bucket" << std::endl;
        }

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
            if (player.getCurrentLocation()->getLocationObjects().size() == 0) {
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
                    std::getline(std::cin, playerInput);
                    for (int i = 0; i < player.getCurrentLocation()->getLocationObjects().size(); i++) {
                        if (playerInput == player.getCurrentLocation()->getLocationObjects()[i]->getName()) {
                            validInput = true;
                            player.pickUpObject(player.getCurrentLocation()->getLocationObjects()[i]);
                            player.getCurrentLocation()->removeLocationObject(i);
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


        else if (playerInput == "Fill Bucket") {

            if (player.getCurrentLocation() != &waterWell) {
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
            }
            else {
                for (Object* item : items) {
                    std::cout << "==== " << item->getName() << "\n";
                }

                std::cout << "\nType 'Eat Burger' to eat the burger.";
                std::cout << "\nType 'Drink Water' to drink from your bucket.";
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


        else if (playerInput == "Drink Water") {

            bool hasBucket = false;

            for (Object* item : player.getInventory() ) {
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
                    player.decreaseThirst();
                }
            }
            
        }
		if (player.isCharacterExhausted()) {
			std::cout << "You have run out of energy and can no longer continue your journey." << std::endl;
			break;
		}
    } while (true);
    //=======================================================================================


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





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
