#pragma once
#include <string>
#include <iostream>
#include <cctype>

/*

Scope: gets player input & processes it for other parts of the program to interpret.


Public Methods:

string getUserInput() - prompts the player for input and returns the input after processing it to remove capitalization & leading/trailing spaces
bool getAndCompareUserInput(string comparison) - prompts the player for input and returns true if the post-processed input matches the provided string, otherwise returns false.
void waitForUser() - prompts the player to “Press Enter to continue,” for the sake of pausing the game logic until any input provided.
string normalizeInput(string input) - returns the input string after removing capitalization & leading/trailing spaces

potentially deferrable:
void executeForInput(string input, bool (*helper_func)) - runs getAndCompareUserInput with input forcomparison parameter, then executes the provided helper function if true.

*/


static class InputHandler
{
public:
	static std::string getUserInput();
	static bool getAndCompareUserInput(std::string comparison);
	static void waitForUser();
	static std::string normalizeInput(std::string input);

	//potentially deferrable:
	static void executeForInput(std::string input, bool(*helper_func));
};

