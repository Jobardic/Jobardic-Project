
#pragma once
#include <vector>
#include "Location.h"
#include "Object.h"

/// @file Character.h
/// @brief Character class, with location, energy, inventory, and food
/// @authors Matthew, Paul

class Character
{
public:
    Character(Location* startingLocation);

    void setCurrentLocation(Location* location);
    Location* getCurrentLocation();

    std::vector<Object*> getInventory();
    void pickUpObject(Object* item);

    int getEnergy();
    int getMaxEnergy();
    void decreaseEnergy();
    bool isCharacterExhausted();

    // NEW: Burger / food functionality
    int getFood();
    int getMaxFood();
    void increaseFood(int amount);
    void removeInventoryObject(int index);
	void decreaseFood(int amount);
	bool isCharacterStarving();
	bool isCharacterDehydrated();


    // NEW: Water well / thirst functionality
    int getThirst();
    int getMaxThirst();
    void decreaseThirst();
    void increaseThirst(int amount);

private:
    Location* currentLocation;
    std::vector<Object*> inventory;

    int characterEnergy;
    const int MAX_ENERGY = 20;
    const int MIN_ENERGY = 0;

    // NEW: Food resource
    int characterFood;
    const int MAX_FOOD = 100;


    // NEW: Thirst resource
    int characterThirst;
    const int MAX_THIRST = 100;
    const int MIN_THIRST = 0;

};


/*

<from high level design (exhaustion)>
character object:
	new class variable: energy (private)
	set health to 20 in constructor
	int getEnergy (0-20)
	void decreaseEnergy (by 1)

*/