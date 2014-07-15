#pragma once
#include <string>

class IEvent
{
public:
	virtual ~IEvent() {}
	virtual std::string getName() = 0;
	virtual size_t getComparableId() = 0;
};