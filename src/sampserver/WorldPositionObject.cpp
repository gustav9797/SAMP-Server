#include "WorldPositionObject.h"


WorldPositionObject::WorldPositionObject(float x, float y, float z, int interiorid, int sampinteriorid, int virtualworld)
{
	x_ = x;
	y_ = y;
	z_ = z;
	interiorid_ = interiorid;
	sampinteriorid_ = sampinteriorid;
	virtualworld_ = virtualworld;
}


WorldPositionObject::~WorldPositionObject(void)
{
}

bool WorldPositionObject::operator<(const WorldPositionObject& bla) const
{
	return false;
}
