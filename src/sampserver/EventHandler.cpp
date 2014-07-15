#include "EventHandler.h"
#include "IEvent.h"

EventHandler::EventHandler()
{
	eventHandlers = new std::map<size_t, std::vector<std::function<void(IEvent*)>>*>();
}


EventHandler::~EventHandler()
{
}

void EventHandler::RegisterHandler(size_t eventId, std::function<void(IEvent*)> function)
{
	if (eventHandlers->find(eventId) == eventHandlers->end())
		eventHandlers->emplace(eventId, new std::vector<std::function<void(IEvent*)>>());
	eventHandlers->at(eventId)->push_back(function);
}

void EventHandler::CallEvent(IEvent *ev)
{
	if (eventHandlers->find(ev->getComparableId()) != eventHandlers->end())
	{
		std::vector<std::function<void(IEvent*)>>* functions = eventHandlers->at(ev->getComparableId());
		for (auto it = functions->begin(); it != functions->end(); ++it)
			(*it)(ev);
	}
}