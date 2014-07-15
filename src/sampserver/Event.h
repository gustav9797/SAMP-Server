#pragma once
#include <string>

#include "IEvent.h"

class Event : IEvent
{
private:
	std::string name;
	size_t id;
public:
	Event(std::string name);
	~Event();
	std::string getName(){ return name; };
	size_t getComparableId(){ return id; };
};

