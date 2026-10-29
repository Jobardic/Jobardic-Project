
#pragma once
#include <vector>
#include <string>
#include "Location.h"
#include "Object.h"
#include "World.h"

/// @file Character.h
/// @brief Character class, with location, energy, inventory, and food
/// @authors Matthew, Paul
/// @date 2026-10-07
/// 
/// @internal public methods
///		Character(Location*)					
///		setCurrentLocation(Location*)
/// 	getCurrentLocation()
/// 	getEnergy() - returns current energy
///		getMaxEnergy () - returns max energy, a constant
///		decreaseEnergy() - decreases energy by 1 (hard code, can be changed later)
///		isCharacterExhausted() - returns true if energy is 0 or less, currently leads to game over

class Character
{
public:
    Character(World::LOCATION_ENUMS startingLocation);
    Character(World::LOCATION_ENUMS startingLocation, int startingEnergy); // I changed starting energy to a constant defined in this class, so this may not be necessary anymore

    void setCurrentLocation(World::LOCATION_ENUMS);
	World::LOCATION_ENUMS getCurrentLocation();

    std::vector<Object*> getInventory();
    void pickUpObject(Object* item);

    int getEnergy();
    int getMaxEnergy();
    void changeEnergy(int amount);
    bool isCharacterExhausted();

    // NEW: Burger / food functionality
    int getFood();
    int getMaxFood();
    void increaseFood(int amount);
    void removeInventoryObject(int index);

	std::string Sleep(bool canSleep);
	std::string Wait();
private:
	World::LOCATION_ENUMS currentLocation;
    std::vector<Object*> inventory;

    // NEW: Food resource
    int characterFood;
    const int MAX_FOOD = 100;
    const int START_FOOD = 50;
	
	int characterEnergy;
	const int MAX_ENERGY = 100;			///< Maximum energy a character can have
	const int MIN_ENERGY = 0;			///< Minimum energy a character can have
	const int START_ENERGY = 20;		///< Arbitrary starting energy for a character
	const int SLEEP_HOURS = 8;			///< Number of hours a character sleeps at a time
	const int WAIT_HOURS = 2;			///< Number of hours a character waits at a time
	const int SLEEP_ENERGY_RATE = 10;	///< Energy gained per hour of sleep
	const int WAKE_ENERGY_RATE = -3;	///< Energy lost per hour of being awake
};


/*

<from high level design (exhaustion)>
character object:
	new class variable: energy (private)
	set health to 20 in constructor
	int getEnergy (0-20)
	void decreaseEnergy (by 1)

<from high level design (time/sleep)>
character object:
	void changeEnergy(int amnt) replaces decreaseEnergy()
	add functionality to not exceed MAX_ENERGY or go below MIN_ENERGY, in those cases just set to max or min
	change MAX_ENERGY to 100, player still starts with 20 though
	string Sleep(bool canSleep)
		If canSleep parameter is false, return “you can’t sleep here” message
		Otherwise:
			call passTime(8, true) //simplest possible implementation that probably will suffice for sprint 1
			return message indicating player has slept
*/

