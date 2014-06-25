#include "InteriorHandler.h"
#include <sampgdk\core.h>
#include <sampgdk\a_objects.h>
#include <sampgdk\a_samp.h>
#include <sstream>
#include "PlayerHandler.h"
#include "MyPlayer.h"
#include "Interior.h"
#include "MySQLFunctions.h"
#include "Pickup.h"
#include "GameUtility.h"

InteriorHandler::InteriorHandler()
{
	interiors = new std::map<int, Interior*>();
	defaultInteriors = new std::map<int, Interior*>();
	pickups = new std::map<int, Pickup*>();
	sampPickupIdToPickupId = new std::map<int, int>();
}


InteriorHandler::~InteriorHandler()
{
	delete interiors;
	delete defaultInteriors;
	delete pickups;
}

bool InteriorHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	if (cmd == "gotoint")
	{
		if (args.size() >= 1 && args[0] != "")
		{
			int interiorId = 0;
			Interior *interior = nullptr;
			if(args[0] != "default" && args.size() != 2)
			{
				interiorId = atoi(args[0].c_str());
				interior = getInterior(interiorId);
			}
			else
			{
				interiorId = atoi(args[1].c_str());
				interior = getDefaultInterior(interiorId);
			}
			if (interior != nullptr)
				gameUtility->playerHandler->TeleportPlayer(player->GetId(), *interior);
			else
				SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: Interior does not exist.");
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /setint <interiorID>");
		return true;
	}
	else if (cmd == "setworld")
	{
		if (args.size() == 1 && args[0] != "")
		{
			int worldId = atoi(args[0].c_str());
			SetPlayerVirtualWorld(player->GetId(), worldId);
		}
		return true;
	}
	else if (cmd == "addpickuppickup")
	{
		if (args.size() >= 3)
		{
			float *x = new float(), *y = new float(), *z = new float();
			GetPlayerPos(player->GetId(), x, y, z);
			int model = atoi(args[0].c_str());
			int destinationId = atoi(args[1].c_str());

			std::string text = std::string();
			for (int i = 2; i < args.size(); i++)
				text += args[i] + " ";

			HandlerCreatePickup(model, 1, *x, *y, *z, text, getInterior(GetPVarInt(player->GetId(), "currentinterior")), -1, destinationId);
			delete x, y, z;
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /addpickuppickup <model> <dest.pickupID> <text>");
		return true;
	}
	else if (cmd == "addpickupinterior")
	{
		if (args.size() >= 4)
		{
			float *x = new float(), *y = new float(), *z = new float();
			GetPlayerPos(player->GetId(), x, y, z);
			int model = atoi(args[0].c_str());
			int destinationId = atoi(args[1].c_str());
			bool newInterior = (args[2] == "new" ? true : false);

			std::string text = std::string();
			for (int i = 3; i < args.size(); i++)
				text += args[i] + " ";
			if (newInterior)
				destinationId = AddInterior(new Interior(*getDefaultInterior(destinationId)));
			Interior *destinationInterior = getInterior(destinationId);
			if(destinationInterior != nullptr)
			{
				Interior *currentInterior = getInterior(GetPVarInt(player->GetId(), "currentinterior"));
				HandlerCreatePickup(model, 1, *x, *y, *z, text, currentInterior, destinationId);
			}
			else
				SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: Destination interior does not exist");
			delete x, y, z;
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /addpickupinterior <model> <dest.interiorID> <create new interior?(new/existing)> <text>");
		return true;
	}
	else if (cmd == "removepickup")
	{
		int currentPickup = GetPVarInt(player->GetId(), "currentpickup");
		Pickup *pickup = getPickup(currentPickup);
		if(pickup != nullptr && GameUtility::IsPlayerClose(player, *pickup, 1))
		{
			DestroyPickup(currentPickup);
			HandlerDestroyPickup(currentPickup);
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Pickup removed.");
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: You are not close to any pickup.");
		return true;
	}
	else if (cmd == "addexit")
	{
		int currentInteriorID = GetPVarInt(player->GetId(), "currentinterior");
		Interior *currentInterior = getInterior(currentInteriorID);
		if (GetPlayerInterior(player->GetId()) != -1 && currentInterior != nullptr)
		{
			float *x = new float(), *y = new float(), *z = new float();
			GetPlayerPos(player->GetId(), x, y, z);
			HandlerCreatePickup(1318, 1, *x, *y, *z, "[Exit]", currentInterior, -1, GetPVarInt(player->GetId(), "currentpickup"));
			delete x, y, z;
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Exit added.");
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: not inside interior");
		return true;
	}
	else if (cmd == "setentrance")
	{
		int currentInteriorID = GetPVarInt(player->GetId(), "currentinterior");
		Interior *currentInterior = getInterior(currentInteriorID);
		if (GetPlayerInterior(player->GetId()) != -1 && currentInterior != nullptr)
		{
			float *x = new float(), *y = new float(), *z = new float();
			GetPlayerPos(player->GetId(), x, y, z);
			currentInterior->x_ = *x;
			currentInterior->y_ = *y;
			currentInterior->z_ = *z;
			delete x, y, z;
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Entrance set.");
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: not inside interior");
		return true;
	}
	else if (cmd == "enter" || cmd == "ent" || cmd == "exit")
	{
		int currentPickup = GetPVarInt(player->GetId(), "currentpickup");
		Pickup *temp = getPickup(currentPickup);
		int state = GetPlayerState(player->GetId());
		if (temp != nullptr && currentPickup != -1 && (state != 2 && GameUtility::IsPlayerClose(player, *temp, 1)) || (state == 2 && GameUtility::IsPlayerClose(player, *temp, 7)))
		{
			int destinationInterior = temp->destinationInterior;
			int destinationPickup = temp->destinationPickup;
			SetPVarFloat(player->GetId(), "oldx", temp->x_);
			SetPVarFloat(player->GetId(), "oldy", temp->y_);
			SetPVarFloat(player->GetId(), "oldz", temp->z_);
			SetPVarInt(player->GetId(), "oldworld", GetPlayerVirtualWorld(player->GetId()));
			if (destinationPickup != -1)
			{
				Pickup *pickup = getPickup(destinationPickup);
				if(pickup != nullptr)
					gameUtility->playerHandler->TeleportPlayer(player->GetId(), WorldPositionObject(pickup->x_, pickup->y_, pickup->z_, getInterior(pickup->interiorId_)));
				else
					SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: Destination pickup does not exist");
			}
			else if (destinationInterior != -1)
			{
				Interior *interior = getInterior(destinationInterior);
				if(interior !=  nullptr)
					gameUtility->playerHandler->TeleportPlayer(player->GetId(), WorldPositionObject(interior->x_, interior->y_, interior->z_, interior));
				else
					SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: Destination interior does not exist");
			}
		}
		return true;
	}
	else if (cmd == "info")
	{
		std::stringstream s;
		s << "Interior: " << GetPVarInt(player->GetId(), "currentinterior") << "\nSampInterior: " << GetPlayerInterior(player->GetId()) << "\nVirtualWorld: " << GetPlayerVirtualWorld(player->GetId());
		SendClientMessage(player->GetId(), 0xFFFFFFFF, s.str().c_str());
		return true;                 
	}
	else if(cmd == "pinfo")
	{
		int currentPickup = GetPVarInt(player->GetId(), "currentpickup");
		Pickup *pickup = getPickup(currentPickup);
		if(pickup != nullptr)
		{
			std::stringstream s;
			s << "SampPickupID: " << currentPickup << std::endl << "PickupID: " << sampPickupIdToPickupId->at(currentPickup) << "\nPickupModel: " << pickup->model_ << "\nDestinationInterior: " << pickup->destinationInterior << "\nDestinationPickup: " << pickup->destinationPickup;
			SendClientMessage(player->GetId(), 0xFFFFFFFF, s.str().c_str());
		}
		return true;
	}
	return false;
}

void InteriorHandler::CheckForHacks()
{
}

Interior* InteriorHandler::getInterior(int interiorId)
{
	if (interiors->find(interiorId) != interiors->end())
		return interiors->at(interiorId);
	else
		sampgdk::logprintf("Tried to get interior which did not exist.");
	return nullptr;
}

Pickup* InteriorHandler::getPickup(int pickupId)
{
	if(pickups->find(pickupId) != pickups->end())
		return pickups->at(pickupId);
	else
		sampgdk::logprintf("Tried to get pickup which did not exist.");
	return nullptr;
}

Interior* InteriorHandler::getDefaultInterior(int interiorId)
{
	if (defaultInteriors->find(interiorId) != defaultInteriors->end())
		return defaultInteriors->at(interiorId);
	else
		sampgdk::logprintf("Tried to get default interior which did not exist.");
	return nullptr;
}

bool InteriorHandler::AddInterior(int interiorId, Interior *interior)
{
	if (interiors->find(interiorId) == interiors->end())
	{
		interiors->emplace(interiorId, interior);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO interiors(id, interiorid, virtualworld, x, y, z, facingangle, name, description) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)");
		statement->setInt(1, interior->interiorId_);
		statement->setInt(2, interior->sampInteriorId_);
		statement->setInt(3, interior->virtualWorld_);
		statement->setDouble(4, interior->x_);
		statement->setDouble(5, interior->y_);
		statement->setDouble(6, interior->z_);
		statement->setDouble(7, interior->facingAngle_);
		statement->setString(8, interior->name_);
		statement->setString(9, interior->description_);
		MySQLFunctions::ExecutePreparedQuery(statement);
		return true;
	}
	return false;
}

int InteriorHandler::AddInterior(Interior *interior)
{
	int openSlot = -1;
	for (int i = 0; true; i++)
	{
		if (interiors->find(i) == interiors->end())
		{
			openSlot = i;
			interior->interiorId_ = openSlot;
			interior->virtualWorld_ = openSlot;
			break;
		}
	}
	AddInterior(openSlot, interior);
	return openSlot;
}

bool InteriorHandler::RemoveInterior(int interiorId)
{
	if (interiorId >= 0 && interiorId <= 145)
		return false;
	if (interiors->find(interiorId) != interiors->end())
	{
		delete interiors->at(interiorId);
		interiors->erase(interiorId);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("DELETE FROM interiors WHERE id=? LIMIT 1");
		statement->setInt(1, interiorId);
		MySQLFunctions::ExecutePreparedQuery(statement);
		return true;
	}
	return false;
}

int InteriorHandler::SampinterioridToInterior(int sampinteriorid, float x, float y, float z, int virtualworld)
{
	for (std::map<int, Interior*>::iterator it = interiors->begin(); it != interiors->end(); it++)
	{
		Interior* temp = it->second;
		if (temp->sampInteriorId_ == sampinteriorid)
		{
			if (temp->x_ == x && temp->y_ == y && temp->z_ == z && temp->virtualWorld_ == virtualworld)
				return it->first;
		}
	}
	return -1;
}

void InteriorHandler::Load(GameUtility* gameUtility)
{
	sql::ResultSet *res = MySQLFunctions::ExecuteQuery("SELECT * FROM interiors");
	interiors->emplace(-1, new Interior(-1, "Main world", "", 1958.3783f, 1343.1572f, 15.3746f, 0, 0, 0));
	while (res->next())
	{
		interiors->emplace(res->getInt("id"), new Interior(
			res->getInt("id"), 
			res->getString("name"), 
			res->getString("description"), 
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getDouble("facingangle"), 
			res->getInt("interiorid"), 
			res->getInt("virtualworld")));
	}
	delete res;

	res = MySQLFunctions::ExecuteQuery("SELECT * FROM defaultinteriors");
	defaultInteriors->emplace(-1, new Interior(-1, "Main world", "", 1958.3783f, 1343.1572f, 15.3746f, 0, 0, 0));
	while (res->next())
	{
		defaultInteriors->emplace(res->getInt("id"), new Interior(
			res->getInt("id"), 
			res->getString("name"), 
			res->getString("description"), 
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getDouble("facingangle"), 
			res->getInt("interiorid"), 
			res->getInt("virtualworld")));
	}
	delete res;

	res = MySQLFunctions::ExecuteQuery("SELECT * FROM pickups");
	while (res->next())
	{
		int sampId = CreatePickup(res->getInt("model"), res->getInt("type"), res->getDouble("x"), res->getDouble("y"), res->getDouble("z"), res->getInt("virtualworld"));
		int id = res->getInt("id");
		sampPickupIdToPickupId->emplace(sampId, id);
		pickups->emplace(sampId, new Pickup(
			res->getInt("model"),
			res->getInt("type"),
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getString("text"), 
			getInterior(res->getInt("interiorid"))));
		pickups->at(sampId)->destinationInterior = res->getInt("destinationinteriorid");
		pickups->at(sampId)->destinationPickup = res->getInt("destinationpickupid");
	}
	delete res;
}

int InteriorHandler::getFreePickupId()
{
	std::vector<int> temp = std::vector<int>();
	for(auto it = sampPickupIdToPickupId->begin(); it != sampPickupIdToPickupId->end(); it++)
	{
		temp.push_back(it->second);
	}
	int openSlot = -1;
	for (int i = 0; true; i++)
	{
		if (std::find(temp.begin(), temp.end(), i) == temp.end())
		{
			openSlot = i;
			break;
		}
	}
	return openSlot;
}

int InteriorHandler::HandlerCreatePickup(int model, int type, float x, float y, float z, std::string text, Interior *interior, int destinationInterior, int destinationPickup)
{
	int pickupId = CreatePickup(model, type, x, y, z, interior->virtualWorld_);
	Pickup *pickup = new Pickup(model, type, x, y, z, text, interior);
	pickup->destinationInterior = destinationInterior;
	pickup->destinationPickup = destinationPickup;
	sampPickupIdToPickupId->emplace(pickupId, getFreePickupId());
	if (pickups->find(pickupId) == pickups->end())
	{
		pickups->emplace(pickupId, pickup);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO pickups(id, model, type, x, y, z, text, interiorid, sampinteriorid, virtualworld, destinationinteriorid, destinationpickupid) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
		statement->setInt(1, sampPickupIdToPickupId->at(pickupId));
		statement->setInt(2, pickup->model_);
		statement->setInt(3, pickup->type_);
		statement->setDouble(4, pickup->x_);
		statement->setDouble(5, pickup->y_);
		statement->setDouble(6, pickup->z_);
		statement->setString(7, pickup->text_);
		statement->setInt(8, pickup->interiorId_);
		statement->setInt(9, pickup->sampInteriorId_);
		statement->setInt(10, pickup->virtualWorld_);
		statement->setInt(11, pickup->destinationInterior);
		statement->setInt(12, pickup->destinationPickup);
		MySQLFunctions::ExecutePreparedQuery(statement);
	}
	return pickupId;
}

bool InteriorHandler::HandlerDestroyPickup(int pickupId)
{
	if (pickups->find(pickupId) != pickups->end())
	{
		delete pickups->at(pickupId);
		pickups->erase(pickupId);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("DELETE FROM pickups WHERE id=? LIMIT 1");
		statement->setInt(1, sampPickupIdToPickupId->at(pickupId));
		MySQLFunctions::ExecutePreparedQuery(statement);
		sampPickupIdToPickupId->erase(pickupId);
		return true;
	}
	return false;
}