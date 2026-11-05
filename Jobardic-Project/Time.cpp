#include "Time.h"
#include "Character.h"

int Time::day = START_DAY;
float Time::hour = START_HOUR;

int Time::getDay() {
	return day;
}

float Time::getHour() {
	return hour;
}

void Time::passTime(int hours) {
	hour += hours;
	while (hour >= 24) {
		hour -= 24;
		day++;
	}
	/*if (sleeping) {
		character.changeEnergy(SLEEP_ENERGY_RATE * hours);
	}
	else {
		character.changeEnergy(WAKE_ENERGY_RATE * hours);
	}*/
}

std::string Time::timeDisplay() {
	return "Day " + std::to_string(day) + "     " + std::to_string(static_cast<int>(hour)) + ":00"; //currently doesn't work for non integer values for hour
}

/*
time object :
new class variables(private)
[int] day(starts at 1, increments after 24 hours)
[float] hour(starts at 0 and goes up to 23, at the 24th hour instead go to 0 and increment day)
set day to 1 and hour to 22 in constructor
int getDay()
int getTime()
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