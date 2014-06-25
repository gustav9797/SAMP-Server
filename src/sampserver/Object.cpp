#include "Object.h"
#include <map>
#include "MySQLFunctions.h"
#include "Interior.h"

Object::Object(int id, int model, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance)
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
}

Object::~Object(void)
{
	delete  playerObjectsOwned;
}

void Object::UpdatePosition(bool offset, float xo, float yo, float zo, float rx, float ry, float rz)
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

bool Object::HasObject(int objectId)
{
	for(auto it = playerObjectsOwned->begin(); it != playerObjectsOwned->end(); it++)
	{
		if(it->second == objectId)
			return true;
	}
	return false;
}

bool Object::HasPlayerObject(int player)
{
	return playerObjectsOwned->find(player) != playerObjectsOwned->end();
}

void Object::AddPlayerObject(int player, int objectId)
{
	if(playerObjectsOwned->find(player) == playerObjectsOwned->end())
	{
		playerObjectsOwned->emplace(player, objectId);
	}
}

void Object::RemovePlayerObject(int player)
{
	if(playerObjectsOwned->find(player) != playerObjectsOwned->end())
	{
		DestroyPlayerObject(player, playerObjectsOwned->find(player)->second);
		playerObjectsOwned->erase(player);
	}
}

void Object::RemoveAll()
{
	for(auto it = playerObjectsOwned->begin(); it != playerObjectsOwned->end(); it++)
	{
		DestroyPlayerObject(it->first, it->second);
		playerObjectsOwned->erase(it->first);
	}
}

void Object::Save()
{
	sql::PreparedStatement *s = MySQLFunctions::con->prepareStatement("UPDATE `samp`.`objects` SET `interior`=?, `model`=?, `x`=?, `y`=?, `z`=?, `rx`=?, `ry`=?, `rz`=?, `drawdistance`=? WHERE `id`=?");
	s->setInt(1, interior_->interiorId_);
	s->setInt(2, model_);
	s->setDouble(3, x_);
	s->setDouble(4, y_);
	s->setDouble(5, z_);
	s->setDouble(6, rx_);
	s->setDouble(7, ry_);
	s->setDouble(8, rz_);
	s->setDouble(9, drawDistance_);
	s->setInt(10, id_);
	MySQLFunctions::ExecutePreparedQuery(s);
}

void Object::Destroy()
{
	for(auto it = playerObjectsOwned->begin(); it != playerObjectsOwned->end(); it++)
	{
		DestroyPlayerObject(it->first, it->second);
	}
}

