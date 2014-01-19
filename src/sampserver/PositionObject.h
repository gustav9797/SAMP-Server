#pragma once
struct PositionObject
{
	PositionObject(float x, float y, float z) : x_(x), y_(y), z_(z) {}
	float x_;
	float y_;
	float z_;
};