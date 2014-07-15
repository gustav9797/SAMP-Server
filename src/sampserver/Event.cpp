#include "Event.h"


Event::Event(std::string name)
{
	std::hash<std::string> hasher;
	this->id = hasher(name);
}


Event::~Event()
{
}