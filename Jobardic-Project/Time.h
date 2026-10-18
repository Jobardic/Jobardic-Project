#pragma once
//#include "Character.h"    
#include <string>

/// @file Time.h
/// @brief Time class, with day and hour implemented
/// @author Paul Ribardo
/// @date 2026-10-14
/// 
/// @internal public methods
///		Time(int startDay, float startHour) - constructor that sets the starting day and hour
///		getDay() - returns the current day
///		getHour() - returns the current hour
///		PassTime(int hours, bool sleeping, Character& character) - adds to hour/day and updates energy based on sleeping or not

class Character;

class Time
{
public:
	Time(int startDay, float startHour);
	int getDay();
	float getHour();
	void passTime(int hours, bool sleeping, Character character);
	std::string timeDisplay();
private:
	int day;
	float hour;
	const int SLEEP_ENERGY_RATE = 10;
	const int WAKE_ENERGY_RATE = -3;
};

/*
* 
<from high level design>
time object :
	new class variables(private)
		[int] day(starts at 1, increments after 24 hours)
		[float] hour(starts at 0 and goes up to 23, at the 24th hour instead go to 0 and increment day)
	set day to 1 and hour to 22 in constructor
	int getDay()
	float getHour()
	constants:
		const int SLEEP_ENERGY_RATE = 10
		const int WAKE_ENERGY_RATE = -3 (would be -5 if energy was ONLY a function of time, but as of now walking deducts some energy so has to be smaller impact)
	void passTime(int hours, bool sleeping)
		first, hours from argument is added to value of hour
		loop until hour < 24
			if hour >= 24, subtract 24 and add 1 to day
			otherwise, do nothing
		add / subtract energy depending on if sleeping is true or false
			if true, call changeEnergy(SLEEP_ENERGY_RATE * hours)
			if false, call changeEnergy(WAKE_ENERGY_RATE * hours)
*/