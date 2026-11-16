#include "EventManager.h"
std::vector<StoryEvent*> EventManager::storyEvents;


void EventManager::enactEvents() {
	for (const auto& event : storyEvents) {
		event->attemptEvent();
	}
}
void EventManager::addEvent(StoryEvent* event) {
	storyEvents.push_back(event);
}