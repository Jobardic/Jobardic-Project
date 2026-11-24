#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../Jobardic-Project/Location.h"
#include "../Jobardic-Project/Object.h"
#include "../Jobardic-Project/StoryEvent.h"
#include "../Jobardic-Project/World.h"
#include "../Jobardic-Project/EventManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{

	public:

		//Important tech debt:
		//Many test methods declare a new World specific to the test to guarentee everthing is reset to normal
		//however, this presents the issue of technically causing a memory leak
		//while we can easily delete the World class pointer itself, the object pointers and other dynamically allocated variables in the world class constructor will still linger around
		//though since these are just automated tests run once and closed out by Visual Studio naturally we woludn't face any issues with it
		//thus a proper destructor function is technically needed though the lack of it will mostly likely not impact us.

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

			Location bedroom(bedroomName,bedroomDescription,bedroomSleep,false,0.0f);
			Location room(roomName, roomDescription, roomSleep,false,0.0f);

			Assert::AreEqual(bedroomName, bedroom.getName(),L"Name constructor argument and name returned by getName() do not match");
			Assert::AreEqual(bedroomDescription, bedroom.getDescription(), L"Description constructor argument and description returned by getDescription() do not match");

			Assert::AreEqual(bedroomSleep, bedroom.canPlayerSleepHere(), L"TRUE Sleep constructor argument and value returned by canPlayerSleepHere() do not match");
			Assert::AreEqual(roomSleep, room.canPlayerSleepHere(), L"FALSE Sleep constructor argument and value returned by canPlayerSleepHere() do not match");

		}
		TEST_METHOD(LOCATION_OBJECT_MANIPULATION) //implementation may change significantly in the future
		{
			Location room("room name", "room description", false,false,0.0f);
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
			Location room("room name", "room description", false,false,0.0f);
			auto initialObjects = room.getLocationObjects();
	
			try {
				room.removeLocationObject("nonexistent_object");
				Assert::IsTrue(initialObjects == room.getLocationObjects(),L"Location's stored objects were changed when no change was expected");
			}
			catch (...) {
				Assert::Fail(L"removeLocationObject() throws an exception when attempting to remove an object when the inventory is empty");
			}
			
		}
		TEST_METHOD(LOCATION_HASOBJECT_METHOD) {
			Location room("room name", "room description", false, false, 0.0f);
			Object object("object", "object description");
			Object other_object("other object", "other object description");

			//Tests that hasObject reflects that neither object are in the location yet
			Assert::IsFalse(room.hasObject("object"));
			Assert::IsFalse(room.hasObject("other object"));

			//Tests thas hasObject reflects that the first object has been added and not the second
			room.addLocationObject(&object);
			Assert::IsTrue(room.hasObject("object"));
			Assert::IsFalse(room.hasObject("other object"));

			//Tests thas hasObject reflects that the second object has been added, now both are in the location
			room.addLocationObject(&other_object);
			Assert::IsTrue(room.hasObject("object"));
			Assert::IsTrue(room.hasObject("other object"));

			//Tests thas hasObject reflects that the first object has been removed, so only the second object is in the location
			room.removeLocationObject("object");
			Assert::IsFalse(room.hasObject("object"));
			Assert::IsTrue(room.hasObject("other object"));

			//Tests thas hasObject reflects that the second object has been removed, so neither object is in the location now
			room.removeLocationObject("other object");
			Assert::IsFalse(room.hasObject("object"));
			Assert::IsFalse(room.hasObject("other object"));
		}
		TEST_METHOD(STORY_EVENT_ADDSOBJECTSTOLOCATIONS_METHOD) {
			World* world = new World();

			Object* object = new Object("object name", "object description");
			int time[3] = { 1,3,10 };
			std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> objects = {{World::HOME_BEDROOM,{object}}};
			StoryEvent event(time,objects,world);
			StoryEvent event_two(time, {}, world);

			Assert::IsTrue(event.addsObjectsToLocations() == true,L"addObjectsToLocations() returned false when true was expected");
			Assert::IsFalse(event_two.addsObjectsToLocations() == true, L"addObjectsToLocations() returned true when false was expected");
		}
		
		TEST_METHOD(ITEM_STORY_EVENT_EXECUTION_AT_VARIOUS_TIMES) {
			World* world = new World();

			//Portion creating an event which is set to occur immediately, directly using Time::get... methods for the event's time threshold
			Object* instant_event_object = new Object("instant event object", "object description");
			int instant[3] = { Time::getDay(),Time::getHour(),Time::getMinute()};
			std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> objects = { {World::HOME_BEDROOM,{instant_event_object}} };
			StoryEvent event(instant, objects, world);

			event.attemptEvent();

			//checks that the event's execution boolean has been switched to true
			Assert::IsTrue(event.hasExecuted() == true);
			//checks that the locationhas the object its supposed to have using hasObject()
			Assert::IsTrue(world->findLocation(World::HOME_BEDROOM)->hasObject("instant event object") == true);
			//extra check confirming hasObject worked properly;
			Assert::IsTrue(world->findLocation(World::HOME_BEDROOM)->findLocationObject("instant event object") == instant_event_object);




            //creating events with time thresholds later than initial starting time time. Testing three events for a later Day, Hour, and Minute seperately to confirm all 3 threshold values work properly
			int day_one[3] = { Time::getDay() + 1,Time::getHour(),Time::getMinute() };
			int hour_one[3] = { Time::getDay(),Time::getHour() + 1,Time::getMinute() };
			int minute_one[3] = { Time::getDay(),Time::getHour(),Time::getMinute() + 1 };
			World* world_two = new World();
			World* world_three = new World();
			World* world_four = new World();

			StoryEvent event_two(day_one,objects,world_two);
			StoryEvent event_three(hour_one, objects, world_three);
			StoryEvent event_four(minute_one, objects, world_four);



			//similar checks as above but confirming that they haven't executed yet.
			event_two.attemptEvent();
			Assert::IsFalse(event_two.hasExecuted() == true);
			Assert::IsFalse(world_two->findLocation(World::HOME_BEDROOM)->hasObject("instant event object") == true);
			Assert::IsFalse(world_two->findLocation(World::HOME_BEDROOM)->findLocationObject("instant event object") == instant_event_object);

			event_three.attemptEvent();
			Assert::IsFalse(event_three.hasExecuted() == true);
			Assert::IsFalse(world_three->findLocation(World::HOME_BEDROOM)->hasObject("instant event object") == true);
			Assert::IsFalse(world_three->findLocation(World::HOME_BEDROOM)->findLocationObject("instant event object") == instant_event_object);

			event_four.attemptEvent();
			Assert::IsFalse(event_four.hasExecuted() == true);
			Assert::IsFalse(world_four->findLocation(World::HOME_BEDROOM)->hasObject("instant event object") == true);
			Assert::IsFalse(world_four->findLocation(World::HOME_BEDROOM)->findLocationObject("instant event object") == instant_event_object);
			
		}
		TEST_METHOD(ITEM_STORY_EVENT_GETTER_METHODS) {
			World* world = new World();

			int time[3] = {1,5,10};
			StoryEvent event(time, {}, world);

			
			Assert::AreEqual(1,event.getDayThreshold());
			Assert::AreEqual(5, event.getHourThreshold());
			Assert::AreEqual(10, event.getMinuteThreshold());
			Assert::AreEqual(false, event.hasExecuted());
		}
		//The following is more of a test of the EventManager as EventManager::enactEvents() executes after every Time::passTime() call.
		//EventManager::enactEvents() runs attemptEvent() for all events added to it.
	
		TEST_METHOD(EVENTMANAGER_EXECUTION_WHEN_TIME_PASSES) {
			World* world = new World();

			//creating an event which is set to execute 3 hours after current time
			Object* event_object = new Object("event object", "object description");
			int time[3] = { Time::getDay(),Time::getHour()+3,Time::getMinute() };
			std::unordered_map<World::LOCATION_ENUMS, std::vector<Object*>> objects = { {World::HOME_BEDROOM,{event_object}} };
			StoryEvent* event = new StoryEvent(time, objects, world);

			//Adding it to EventManager; Time::passTime()'s execution of EventManager:enactEvents() now includes the event created above
			EventManager::addEvent(event);
			
			//checking that it hasnt immediately executed
			Assert::IsFalse(event->hasExecuted() == true);
			Assert::IsFalse(world->findLocation(World::HOME_BEDROOM)->hasObject("event object") == true);
			Assert::IsFalse(world->findLocation(World::HOME_BEDROOM)->findLocationObject("event object") == event_object);

			//checking that passTime doesn't immediately execute the event in the EventManager when the events time threshold hasnt been met
			Time::passTime(1,0);
			Assert::IsFalse(event->hasExecuted() == true);
			Assert::IsFalse(world->findLocation(World::HOME_BEDROOM)->hasObject("event object") == true);
			Assert::IsFalse(world->findLocation(World::HOME_BEDROOM)->findLocationObject("event object") == event_object);

			//checking that the event now executes as the time threshold has been met
			Time::passTime(2,0);
			Assert::IsTrue(event->hasExecuted() == true);
			Assert::IsTrue(world->findLocation(World::HOME_BEDROOM)->hasObject("event object") == true);
			Assert::IsTrue(world->findLocation(World::HOME_BEDROOM)->findLocationObject("event object") == event_object);


		}




	};
}
