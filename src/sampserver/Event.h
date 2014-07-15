#pragma once
#include <string>

class Event
{
private:
	std::string name;
	size_t id;
	//bool cancelled = false;
public:
	Event(std::string name);
	Event() {};
	~Event();
	std::string getName(){ return name; };
	size_t getComparableId(){ return id; };
	//virtual void Cancel()=0;
	//bool isCancelled() { return cancelled; }
	//void setCancelled(bool value) { cancelled = value; }
};

