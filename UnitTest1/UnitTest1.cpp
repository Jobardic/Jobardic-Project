#include "pch.h"
#include "CppUnitTest.h"
#include "../Jobardic-Project/Location.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(HELLO)
		{
			Logger::WriteMessage("Hello Jobard Test Automation");
		}
		TEST_METHOD(LOCATION_CONSTRUCTION) 
		{
			std::string bedroomName = "bedroom name";
			std::string bedroomDescription = "bedroom description";
			std::string roomName = "room name";
			std::string roomDescription = "room description";
			bool bedroomSleep = true;
			bool roomSleep = false;

			Location bedroom(bedroomName,bedroomDescription,bedroomSleep);
			Location room(roomName, roomDescription, roomSleep);

			Assert::AreEqual(bedroomName, bedroom.getName(),L"Name constructor argument and name returned by getName() do not match");
			Assert::AreEqual(bedroomDescription, bedroom.getDescription(), L"Description constructor argument and description returned by getDescription() do not match");

			Assert::AreEqual(bedroomSleep, bedroom.canPlayerSleepHere(), L"TRUE Sleep constructor argument and value returned by canPlayerSleepHere() do not match");
			Assert::AreEqual(roomSleep, room.canPlayerSleepHere(), L"FALSE Sleep constructor argument and value returned by canPlayerSleepHere() do not match");

		}
	};
}
