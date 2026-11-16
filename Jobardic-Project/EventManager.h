#pragma once
#include <string>
#include <unordered_map>
#include "StoryEvent.h"

/*

Scope: keeps track of all story events & enacts them when their condition for occurring is met (e.g enacting events at the time threshold they are configured for)

public methods:

 void enactEvents() - enacts all story events which meet their condition (e.g attemptEvent for all events in the vector storyEvents)



private data:

vector<StoryEvent*> storyEvents - list of all storyEvents

*/



static class EventManager
{
public:
	static void enactEvents();
	static void addEvent(StoryEvent* event);

private:
	static std::vector<StoryEvent*> storyEvents;
};

