#include "MyObject.h"
#include "MySQLFunctions.h"


MyObject::MyObject(int id, int model, int virtualWorld, int interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance)
	: Object(id), id_(id), model_(model), virtualWorld_(virtualWorld), interior_(interior), x_(x), y_(y), z_(z_), rx_(rx), ry_(ry), rz_(rz), drawDistance_(drawDistance)
{
}


MyObject::MyObject(Object object, int model, int virtualWorld, int interior, float drawDistance)
	: Object(object.GetId()), id_(object.GetId()), model_(model), virtualWorld_(virtualWorld), interior_(interior), drawDistance_(drawDistance)
{
	float *x = new float(), *y = new float(), *z = new float();
	float *rx = new float(), *ry = new float(), *rz = new float();
	object.GetPos(x, y, z);
	object.GetRot(rx, ry, rz);
	x_=*x; y_=*y; z_=*z; rx_=*rx; ry_=*ry; rz_=*rz;
	delete x, y, z, rx, ry, rz;
}


MyObject::~MyObject(void)
{
}
