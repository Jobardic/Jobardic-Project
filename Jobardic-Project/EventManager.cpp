#include "EventManager.h"
std::vector<StoryEvent*> EventManager::storyEvents;


void EventManager::enactEvents() {
	for (const auto& event : storyEvents) {
		event->attemptEvent();
	}
}
void EventManager::addEvent(StoryEvent* event) {

	if (!hasEvent(event)) {
		storyEvents.push_back(event);
	}
}

bool EventManager::hasEvent(StoryEvent* event) {
	auto indexOfEvent = std::find_if(
		storyEvents.begin(),
		storyEvents.end(),
		[event](StoryEvent* ev) {
			return ev == event;
		}
	);
	return (indexOfEvent != storyEvents.end());
}