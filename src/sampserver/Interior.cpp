#include "Interior.h"
#include "WorldPositionObject.h"

Interior::Interior(int interiorId, std::string name, std::string description, float x, float y, float z, float facingAngle, int sampInteriorId, int virtualWorld)
	: name_(name), description_(description), WorldPositionObject(x, y, z, interiorId, sampInteriorId, virtualWorld, facingAngle)
{
}


Interior::~Interior()
{
}
