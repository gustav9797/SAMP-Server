#pragma once
#include <functional>
#include <map>
#include <vector>

#include "Event.h"

class EventHandler
{
private:
	std::map<size_t, std::vector<std::function<void(Event*)>>*> *eventHandlers;
public:
	EventHandler();
	~EventHandler();
	template<typename T> void RegisterHandler(std::function<void(Event*)> function);
	void CallEvent(Event *ev);
};

template<typename T>
void EventHandler::RegisterHandler(std::function<void(Event*)> function)
{
	size_t eventId = static_cast<Event*>(new T())->getComparableId();
	if (eventHandlers->find(eventId) == eventHandlers->end())
		eventHandlers->emplace(eventId, new std::vector<std::function<void(Event*)>>());
	eventHandlers->at(eventId)->push_back(function);
}

