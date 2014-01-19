#pragma once
class Interior;
class WorldPositionObject
{
public:
	WorldPositionObject(float x, float y, float z, int interiorId, int sampInteriorId, int virtualWorld, float facingAngle);
	WorldPositionObject(float x, float y, float z, Interior *interior);
	~WorldPositionObject(void);
	float x_; 
	float y_;
	float z_;
	int interiorId_;
	int sampInteriorId_;
	int virtualWorld_;
	float facingAngle_;

	bool operator<(const WorldPositionObject& bla) const;
};

