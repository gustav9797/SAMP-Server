#pragma once
#include <sampgdk\a_objects.h>
class WorldPositionObject;
class MyObject : Object
{
private:
	int id_;
	int model_;
	int virtualWorld_;
	int interior_;
	float x_;
	float y_;
	float z_;
	float rx_;
	float ry_;
	float rz_;
	float drawDistance_;
public:
	MyObject(int id, int model, int virtualWorld, int interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance);
	MyObject(Object object, int model, int virtualWorld, int interior, float drawDistance);
	~MyObject(void);
	int getModel() { return model_; };
	//WorldPositionObject getPosition() { return WorldPositionObject(;
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	float getDrawDistance();
};

