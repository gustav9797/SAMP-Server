#pragma once
class WorldPositionObject
{
public:
	WorldPositionObject(float x, float y, float z, int interiorid, int sampinteriorid, int virtualworld);
	~WorldPositionObject(void);
	float x_; 
	float y_;
	float z_;
	int interiorid_;
	int sampinteriorid_;
	int virtualworld_;

	bool operator<(const WorldPositionObject& bla) const;
};

