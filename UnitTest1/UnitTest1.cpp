#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../Jobardic-Project/Location.h"
#include "../Jobardic-Project/Object.h"

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
		TEST_METHOD(LOCATION_OBJECT_MANIPULATION) //implementation may change significantly in the future
		{
			Location room("room name", "room description", false);
			Object object_A("A name","A description");
			Object object_B("B name", "B description");
			Object object_C("C name", "C description");

			std::vector<Object*> expectedThreeObjects = {&object_A,&object_B,&object_C};
			room.addLocationObject(&object_A);
			room.addLocationObject(&object_B);
			room.addLocationObject(&object_C);
			
			Assert::IsTrue(room.getLocationObjects() == expectedThreeObjects, L"addLocationObject() not behaving as expected: unexpected object vector contents");

			std::vector<Object*> expectedTwoObjects = { &object_A,&object_C };
			room.removeLocationObject("B name"); //removes object of second position, object_B

			Assert::IsTrue(room.getLocationObjects() == expectedTwoObjects, L"removeLocationObject() not behaving as expected: unexpected remaining object vector contents");

		}
		TEST_METHOD(LOCATION_OBJECT_REMOVAL_WITH_EMPTY_INVENTORY) 
		{
			Object object("name", "description");
			Location room("room name", "room description", false);
			auto initialObjects = room.getLocationObjects();
	
			try {
				room.removeLocationObject("name");
				Assert::IsTrue(initialObjects == room.getLocationObjects(),L"Location's stored objects were changed when no change was expected");
			}
			catch (...) {
				Assert::Fail(L"removeLocationObject() throws an exception when attempting to remove an object when the inventory is empty");
			}
			
		}
	};
}
