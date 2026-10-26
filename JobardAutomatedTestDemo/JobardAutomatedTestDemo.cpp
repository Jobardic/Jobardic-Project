#include "pch.h"
#include "CppUnitTest.h"
#include "../Jobardic-Project/Character.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JobardAutomatedTestDemo
{
	TEST_CLASS(JobardAutomatedTestDemo)
	{
	public:
		
		TEST_METHOD(HelloTestAutomation)
		{
			Logger::WriteMessage("Hello Jobard Test Automation");
		}

		TEST_METHOD(CharacterHealth)	{
			Logger::WriteMessage("Character Health Test");
			// Create a character with a null starting location for testing purposes
			// don't want to drag in the location class for this test
			Character testCharacter(nullptr);
			Assert::AreEqual(testCharacter.getEnergy(), testCharacter.getMaxEnergy());
			testCharacter.decreaseEnergy();
			Assert::AreNotEqual(testCharacter.getEnergy(), testCharacter.getMaxEnergy());
		}
	};
}
