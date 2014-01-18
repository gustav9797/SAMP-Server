#pragma once
#include <iostream>
#include <map>
#include "Inventory.h"
class House
{
public:
	House(void);
	~House(void);
	std::map<int, int> *pickups; //temp, not private D:
	std::map<int, int> *interiors;
	Inventory *inventory;
	std::string name;
};

