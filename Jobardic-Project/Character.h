#pragma once
#include "Location.h"

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
	Character(Location* startingLocation);
	void setCurrentLocation(Location* location);
	Location* getCurrentLocation();
	int getEnergy();
	int getMaxEnergy();
	void decreaseEnergy();
	bool isCharacterExhausted();
private:
	Location* currentLocation;
	int characterEnergy;
	const int MAX_ENERGY = 20; ///< Maximum energy a character can have, can be changed later
	const int MIN_ENERGY = 0;  ///< Minimum energy a character can have
};

/*

<from high level design (exhaustion)>
character object:
	new class variable: energy (private)
	set health to 20 in constructor
	int getEnergy (0-20)
	void decreaseEnergy (by 1)

*/