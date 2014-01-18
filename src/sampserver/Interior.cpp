#include "Interior.h"


Interior::Interior(std::string name, std::string description, float x, float y, float z, float facingangle, int interiorid, int sampinteriorid, int virtualworld)
	: WorldPositionObject(x, y, z, interiorid, sampinteriorid, virtualworld)
{
	name_ = name;
	description_ = description;
	facingangle_ = facingangle;
	//exitLocations = new std::map<WorldPositionObject, WorldPositionObject>();
}


Interior::~Interior()
{
}
