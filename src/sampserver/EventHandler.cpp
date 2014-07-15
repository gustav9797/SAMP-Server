#include "EventHandler.h"
#include "Event.h"

#include <iostream>

EventHandler::EventHandler()
{
	eventHandlers = new std::map<size_t, std::vector<std::function<void(Event*)>>*>();
}


EventHandler::~EventHandler()
{
	delete eventHandlers;
}

void EventHandler::CallEvent(Event *ev)
{
	if (eventHandlers->find(ev->getComparableId()) != eventHandlers->end())
	{
		std::vector<std::function<void(Event*)>>* functions = eventHandlers->at(ev->getComparableId());
		for (auto it = functions->begin(); it != functions->end(); ++it)
			(*it)(ev);
	}
}