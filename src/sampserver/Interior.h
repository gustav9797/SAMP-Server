#pragma once
#include <iostream>
#include <map>
#include <sampgdk/a_samp.h>
#include "WorldPositionObject.h"
class Interior : public WorldPositionObject
{
public:
	Interior(std::string name, std::string description, float x, float y, float z, float facingangle, int interiorid, int sampinteriorid, int virtualworld);
	~Interior();

	std::string name_;
	std::string description_;
	float facingangle_;

	std::map<WorldPositionObject, WorldPositionObject> *exitLocations;
};

