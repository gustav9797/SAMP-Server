#include "ObjectHandler.h"
#include <sstream>
#include "MyObject.h"
#include "Interior.h"
#include "MyPlayer.h"
#include "InteriorHandler.h"
#include "GameUtility.h"
#include "MyPlayer.h"
#include "PlayerHandler.h"

ObjectHandler::ObjectHandler(void)
{
	objects = new std::map<int, MyObject*>();
	//streamedObjects = new std::map<int, PlayerObject>();
	//sampObjectIdToId = new std::map<int, int>();
}


ObjectHandler::~ObjectHandler(void)
{
}

bool ObjectHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	if(cmd == "createobject")
	{
		if(args.size() >= 1)
		{
			float *x = new float(); float *y = new float(); float *z = new float();
			player->GetPos(x, y, z);
			int model = atoi(args[0].c_str());
			MyObject *object = CreateObject(model, player, gameUtility->interiorHandler->getInterior(GetPVarInt(player->GetId(), "currentinterior")), *x, *y, *z, 0, 0, 0, 10);
			std::stringstream s;
			s << "Created object with ID " << object->getId();// << " and sampID " << object->getSampId();
			SendClientMessage(player->GetId(), 0xFFFFFFFF, s.str().c_str());
			delete x, y, z;
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /createobject <model>");
		return true;
	}
	else if(cmd == "selectobject")
	{
		SelectObject(player->GetId());
	}
	else if(cmd == "editobject")
	{
		//if(args.size() >= 1)
		//{
		int selectedObject = GetPVarInt(player->GetId(), "selectedobject");
		if(selectedObject != -1)
			EditPlayerObject(player->GetId(), selectedObject);
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "You do not have any object selected.");
		//}
		//else
		//	SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /editobject <objectID>");
	}
	return false;
}

void ObjectHandler::CheckForHacks()
{
}

void ObjectHandler::Load(GameUtility* gameUtility)
{
}

MyObject *ObjectHandler::CreateObject(int model, MyPlayer* player, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance)
{
	int objectId = getFreeObjectId();
	//PlayerObject temp = PlayerObject::Create(player->GetId(), model, x, y, z, rx, ry, rz, drawDistance);
	MyObject *object = new MyObject(getFreeObjectId(), model, interior, x, y, z, rx, ry, rz, drawDistance);
	objects->emplace(object->getId(), object);
	//sampObjectIdToId->emplace(object->getSampId(), object->getId());
	return object;
	//MyObj
	/*sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO objects(licenseplate, owner, virtualworld, interior, model, x, y, z, rotation, color1, color2, respawndelay) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
	statement->setInt(1, virtualWorld);
	statement->setDouble(2, x);
	statement->setDouble(3, y);
	statement->setDouble(4, z);
	statement->setDouble(5, x);
	statement->setDouble(6, y);
	statement->setDouble(7, z);
	statement->setDouble(8, rotation);
	MySQLFunctions::ExecutePreparedQuery(statement);*/
	//return nullptr;
}

void ObjectHandler::RemoveObject(int id)
{
}

std::vector<MyObject*> *ObjectHandler::getCloseObjects(float x, float y, float z, float maxDistance)
{
	return nullptr;
}

int ObjectHandler::getFreeObjectId()
{
	int openSlot = -1;
	for(int i = 0; true; i++)
	{
		if(objects->find(i) == objects->end())
		{
			openSlot = i;
			break;
		}
	}
	return openSlot;
}

MyObject *ObjectHandler::getObject(int objectId)
{
	if(objects->find(objectId) != objects->end())
	{
		return objects->at(objectId);
	}
	return nullptr;
}

void ObjectHandler::Update(GameUtility *gameUtility)
{
	std::map<int, MyPlayer*> *players = gameUtility->playerHandler->players;
	for(auto it = players->begin(); it != players->end(); it++)
	{
		Player *player = it->second;
		for(auto i = objects->begin(); i != objects->end(); i++)
		{
			MyObject *object = i->second;
			if(!object->hasPlayerObject(player->GetId()) && player->GetVirtualWorld() == object->getInterior()->virtualWorld_)
			{
				if(GetPVarInt(player->GetId(), "currentinterior") == object->getInterior()->interiorId_)
				{
					if(IsPlayerInRangeOfPoint(player->GetId(), object->getDrawDistance(), object->getX(), object->getY(), object->getZ()))
					{
						PlayerObject temp = PlayerObject::Create(player->GetId(), object->getModel(), object->getX(), object->getY(), object->getZ(), object->getRotX(), object->getRotY(), object->getRotZ(), object->getDrawDistance());
						//streamedObjects->emplace(temp.GetObjectId(), temp);
						object->addPlayerObject(player->GetId(), temp.GetObjectId());
						std::stringstream s;
						s << "Object " << object->getId() << " was streamed in";
						SendClientMessage(player->GetId(), 0xFFFFFFFF, s.str().c_str());
					}
				}
			}
			else if(object->hasPlayerObject(player->GetId()) && !IsPlayerObjectMoving(player->GetId(), GetPVarInt(player->GetId(), "selectedobject")))
			{
				if(GetPVarInt(player->GetId(), "currentinterior") != object->getInterior()->interiorId_ || 
					!IsPlayerInRangeOfPoint(player->GetId(), object->getDrawDistance(), object->getX(), object->getY(), object->getZ())
					|| player->GetVirtualWorld() != object->getInterior()->virtualWorld_)
				{

					std::stringstream s;
					s << "Object " << object->getId() << " was streamed out";
					SendClientMessage(player->GetId(), 0xFFFFFFFF, s.str().c_str());
					object->removePlayerObject(player->GetId());
				}
			}
		}
	}
}

bool ObjectHandler::OnPlayerSelectObject(MyPlayer *player, int type, int objectSampId, int model, float x, float y, float z)
{
	if(type == SELECT_OBJECT_PLAYER_OBJECT)
	{
		SetPVarInt(player->GetId(), "selectedobject", objectSampId);
		std::stringstream s;
		s << "Selected object " << objectSampId;
		SendClientMessage(player->GetId(), 0xFFFFFFFF, s.str().c_str());
	}
	return true;
}

bool ObjectHandler::OnPlayerEditObject(MyPlayer *player, int playerobject, int objectSampId, int response, float xo, float yo, float zo, float xr, float yr, float zr)
{
	if(playerobject)
	{
		for(auto it = objects->begin(); it != objects->end(); it++)
		{
			if(it->second->hasObject(objectSampId))
			{
				if(response = EDIT_RESPONSE_FINAL)
				{
					it->second->UpdatePosition(false, xo, yo, zo, xr, yr, zr);
					//std::cout << "Updated after object moved" << std::endl;
				}
				else if(response == EDIT_RESPONSE_CANCEL ||response == EDIT_RESPONSE_UPDATE)
				{
					it->second->UpdatePosition(false, it->second->getX(), it->second->getY(), it->second->getZ(), it->second->getRotX(), it->second->getRotY(), it->second->getRotZ());
					//std::cout << "Updated after cancel/exit" << std::endl;
				}
				break;
			}
		}
	}
	return true;
}

bool ObjectHandler::OnPlayerObjectMoved(MyPlayer *player, int objectSampId)
{
	return true;
}
