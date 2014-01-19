#pragma once
#include <iostream>
#include <map>
#include <sampgdk/a_samp.h>
#include "WorldPositionObject.h"
class PositionObject;
class Interior : public WorldPositionObject
{
public:
	Interior(int interiorId, std::string name, std::string description, float x, float y, float z, float facingAngle, int sampInteriorId, int virtualWorld);
	~Interior();
	std::string name_;
	std::string description_;
};

