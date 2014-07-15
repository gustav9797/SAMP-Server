#pragma once
#include <functional>
#include <map>
#include <vector>

class IEvent;

class EventHandler
{
private:
	std::map<size_t, std::vector<std::function<void(IEvent*)>>*> *eventHandlers;
public:
	EventHandler();
	~EventHandler();
	void RegisterHandler(size_t eventId, std::function<void(IEvent*)> function);
	void CallEvent(IEvent *ev);
};

