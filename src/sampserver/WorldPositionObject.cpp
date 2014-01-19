#include "WorldPositionObject.h"
#include "Interior.h"

WorldPositionObject::WorldPositionObject(float x, float y, float z, int interiorId, int sampInteriorId, int virtualWorld, float facingAngle)
{
	x_ = x;
	y_ = y;
	z_ = z;
	interiorId_ = interiorId;
	sampInteriorId_ = sampInteriorId;
	virtualWorld_ = virtualWorld;
	facingAngle_ = facingAngle;
}

WorldPositionObject::WorldPositionObject(float x, float y, float z, Interior *interior)
{
	x_ = x;
	y_ = y;
	z_ = z;
	interiorId_ = interior->interiorId_;
	sampInteriorId_ = interior->sampInteriorId_;
	virtualWorld_ = interior->virtualWorld_;
	facingAngle_ = interior->facingAngle_;
}


WorldPositionObject::~WorldPositionObject(void)
{
}

bool WorldPositionObject::operator<(const WorldPositionObject& bla) const
{
	return false;
}
