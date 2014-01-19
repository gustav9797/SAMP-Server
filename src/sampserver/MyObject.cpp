#include "MyObject.h"
#include <map>
#include "MySQLFunctions.h"
#include "Interior.h"

MyObject::MyObject(int id, int model, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance)
	: id_(id), 
	model_(model), 
	interior_(interior), 
	x_(x), 
	y_(y), 
	z_(z), 
	rx_(rx), 
	ry_(ry), 
	rz_(rz), 
	drawDistance_(drawDistance)
{
	playerObjectsOwned = new std::map<int, int>();
	Save();
}

MyObject::~MyObject(void)
{
}

void MyObject::UpdatePosition(bool offset, float xo, float yo, float zo, float rx, float ry, float rz)
{
	x_ = xo; y_ = yo; z_ = zo;
	rx_ = rx; ry_ = ry; rz_ = rz;
	float *objectX = new float(); float *objectY = new float(); float *objectZ = new float(); 
	for(auto it = playerObjectsOwned->begin(); it != playerObjectsOwned->end(); it++)
	{
		GetPlayerObjectPos(it->first, it->second, objectX, objectY, objectZ);
		MovePlayerObject(it->first, it->second, xo, yo, zo, 1000, rx, ry, rz);
	}
	delete objectX, objectY, objectZ;
	Save();
}

bool MyObject::hasObject(int objectId)
{
	for(auto it = playerObjectsOwned->begin(); it != playerObjectsOwned->end(); it++)
	{
		if(it->second == objectId)
			return true;
	}
	return false;
}

bool MyObject::hasPlayerObject(int player)
{
	return playerObjectsOwned->find(player) != playerObjectsOwned->end();
}

void MyObject::addPlayerObject(int player, int objectId)
{
	if(playerObjectsOwned->find(player) == playerObjectsOwned->end())
	{
		playerObjectsOwned->emplace(player, objectId);
	}
}

void MyObject::removePlayerObject(int player)
{
	if(playerObjectsOwned->find(player) != playerObjectsOwned->end())
	{
		DestroyPlayerObject(player, playerObjectsOwned->find(player)->second);
		playerObjectsOwned->erase(player);
	}
}

void MyObject::Save()
{
	/*sql::PreparedStatement *s = MySQLFunctions::con->prepareStatement("UPDATE `samp`.`objects` SET `x`=?, `y`=?, `z`=?, `rotation`=?, `color1`=?, `color2`=? WHERE `licenseplate`=?");
	s->setDouble(1, *x);
	s->setDouble(2, *y);
	s->setDouble(3, *z);
	s->setDouble(4, *rotation);
	s->setInt(5, vehicle->color1_);
	s->setInt(6, vehicle->color2_);
	s->setString(7, vehicle->licensePlate_);
	MySQLFunctions::ExecutePreparedQuery(s);*/
}

