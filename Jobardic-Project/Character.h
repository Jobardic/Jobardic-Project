#pragma once
#include <string>
#include "Location.h"
#include "Object.h"
#include "Time.h"

/// @file Character.h
/// @brief Character class, with location and energy/time implemented
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
	Character(Location* startingLocation, int startEnergy);
	void setCurrentLocation(Location* location);
	Location* getCurrentLocation();
	std::vector<Object*> getInventory();
	void pickUpObject(Object* item);
	int getEnergy();
	int getMaxEnergy();
	void changeEnergy(int amount);
	bool isCharacterExhausted();
	std::string Sleep(bool canSleep);
private:
	Location* currentLocation;
	std::vector<Object*> inventory;
	int characterEnergy;
	std::string sleepMessage;
	const int MAX_ENERGY = 100; ///< Maximum energy a character can have
	const int MIN_ENERGY = 0;  ///< Minimum energy a character can have
	const int SLEEP_HOURS = 8; ///< Number of hours a character sleeps at a time
	const int SLEEP_ENERGY_RATE = 10;
	const int WAKE_ENERGY_RATE = -3;
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

