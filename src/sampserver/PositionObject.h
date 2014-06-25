#pragma once
class PositionObject
{
public:
	PositionObject(float x, float y, float z) : x_(x), y_(y), z_(z) {}
	float getX() { return x_; }
	float getY() { return y_; }
	float getZ() { return z_; }
private:
	float x_;
	float y_;
	float z_;
};