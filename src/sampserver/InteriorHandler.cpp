#include "InteriorHandler.h"
#include <sampgdk\core.h>
#include <sstream>
#include "PlayerHandler.h"
#include "PickupHandler.h"
#include "MyPlayer.h"
#include "Interior.h"
#include "MySQLFunctions.h"

InteriorHandler::InteriorHandler()
{
	interiors = new std::map<int, Interior*>();
	defaultInteriors = new std::map<int, Interior*>();
}


InteriorHandler::~InteriorHandler()
{
	delete interiors;
	delete defaultInteriors;
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
				interior = gameUtility->interiorHandler->getInterior(interiorId);
			}
			else
			{
				interiorId = atoi(args[1].c_str());
				interior = gameUtility->interiorHandler->getDefaultInterior(interiorId);
			}
			if (interior != nullptr)
			{
				SetPlayerInterior(player->GetId(), interior->sampinteriorid_);
				SetPlayerVirtualWorld(player->GetId(), interior->virtualworld_);
				SetPlayerPos(player->GetId(), interior->x_, interior->y_, interior->z_);
			}
			else
				SendClientMessage(player->GetId(), 0xFFFFFFFF, "Interior does not exist.");
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
			for (int i = 3; i < args.size(); i++)
				text += args[i] + " ";

			gameUtility->pickupHandler->HandlerCreatePickup(
				model, 
				1, 
				*x, 
				*y, 
				*z, 
				text, 
				GetPVarInt(player->GetId(), "currentinterior"), 
				GetPlayerInterior(player->GetId()), 
				GetPlayerVirtualWorld(player->GetId()), -1, destinationId);
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
			for (int i = 4; i < args.size(); i++)
				text += args[i] + " ";
			if (newInterior)
				destinationId = gameUtility->interiorHandler->AddInterior(new Interior(*getDefaultInterior(destinationId)));
			gameUtility->pickupHandler->HandlerCreatePickup(model, 1, *x, *y, *z, text, GetPVarInt(player->GetId(), "currentinterior"), GetPlayerInterior(player->GetId()), GetPlayerVirtualWorld(player->GetId()), destinationId);
			delete x, y, z;
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /addpickupinterior <model> <dest.interiorID> <create new interior?(new/existing)> <text>");
		return true;
	}
	else if (cmd == "removepickup")
	{
		int currentPickup = GetPVarInt(player->GetId(), "currentpickup");
		if (currentPickup != -1)
		{
			DestroyPickup(currentPickup);
			gameUtility->pickupHandler->DestroyPickup(currentPickup);
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Pickup removed.");
		}
		return true;
	}
	else if (cmd == "addexit")
	{
		int currentInteriorID = GetPVarInt(player->GetId(), "currentinterior");
		Interior *currentInterior = gameUtility->interiorHandler->getInterior(currentInteriorID);
		if (GetPlayerInterior(player->GetId()) != -1 && currentInterior != nullptr)
		{
			float *x = new float(), *y = new float(), *z = new float();
			GetPlayerPos(player->GetId(), x, y, z);
			gameUtility->pickupHandler->HandlerCreatePickup(1318, 1, *x, *y, *z, "[Exit]", currentInteriorID, currentInterior->sampinteriorid_, currentInterior->virtualworld_, -1, GetPVarInt(player->GetId(), "currentpickup"));
			delete x, y, z;
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Exit added.");
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Error: not inside interior");
		return true;
	}
	else if (cmd == "enter" || cmd == "ent" || cmd == "exit")
	{
		int currentPickup = GetPVarInt(player->GetId(), "currentpickup");
		Pickup *temp = gameUtility->pickupHandler->GetPickup(currentPickup);
		int state = GetPlayerState(player->GetId());
		if (temp != nullptr && currentPickup != -1 && (state != 2 && IsPlayerInRangeOfPoint(player->GetId(), 1, temp->x_, temp->y_, temp->z_)) || (state == 2 && IsPlayerInRangeOfPoint(player->GetId(), 7, temp->x_, temp->y_, temp->z_)))
		{
			int destinationInterior = temp->destinationInterior;
			int destinationPickup = temp->destinationPickup;
			SetPVarFloat(player->GetId(), "oldx", temp->x_);
			SetPVarFloat(player->GetId(), "oldy", temp->y_);
			SetPVarFloat(player->GetId(), "oldz", temp->z_);
			SetPVarInt(player->GetId(), "oldworld", GetPlayerVirtualWorld(player->GetId()));
			if (destinationPickup != -1)
			{
				Pickup *pickup = gameUtility->pickupHandler->GetPickup(destinationPickup);
				SetPlayerInterior(player->GetId(), pickup->sampinteriorid_);
				SetPlayerPos(player->GetId(), pickup->x_, pickup->y_, pickup->z_);
				SetPlayerVirtualWorld(player->GetId(), pickup->virtualworld_);
			}
			else if (destinationInterior != -1)
			{
				Interior *interior = getInterior(destinationInterior);
				gameUtility->playerHandler->TeleportPlayer(player->GetId(), *interior);
				SetPVarInt(player->GetId(), "currentinterior", destinationInterior);
			}
		}
		return true;
	}
	else if (cmd == "info")
	{
		//std::string temp1 = std::string("Interior: ") + ToString(GetPVarInt(player->GetId(), "currentinterior"))
		//+ std::string("\nSamp Interior: ") + ToString(GetPlayerInterior(player->GetId()))
		//+ std::string("\nVirtualworld: ") + ToString(GetPlayerVirtualWorld(player->GetId()));

		//SendClientMessage(player->GetId(), 0xFFFFFFFF, temp1.c_str());
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
		ServerLog::Printf("Tried to get interior which did not exist.");
	return nullptr;
}

Interior* InteriorHandler::getDefaultInterior(int interiorId)
{
	if (defaultInteriors->find(interiorId) != defaultInteriors->end())
		return defaultInteriors->at(interiorId);
	else
		ServerLog::Printf("Tried to get default interior which did not exist.");
	return nullptr;
}

bool InteriorHandler::AddInterior(int interiorId, Interior *interior)
{
	if (interiors->find(interiorId) == interiors->end())
	{
		interiors->emplace(interiorId, interior);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO interiors(id, interiorid, virtualworld, x, y, z, facingangle, name, description) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)");
		statement->setInt(1, interior->interiorid_);
		statement->setInt(2, interior->sampinteriorid_);
		statement->setInt(3, interior->virtualworld_);
		statement->setDouble(4, interior->x_);
		statement->setDouble(5, interior->y_);
		statement->setDouble(6, interior->z_);
		statement->setDouble(7, interior->facingangle_);
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
			interior->interiorid_ = openSlot;
			interior->virtualworld_ = openSlot;
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
		if (temp->sampinteriorid_ == sampinteriorid)
		{
			if (temp->x_ == x && temp->y_ == y && temp->z_ == z && temp->virtualworld_ == virtualworld)
				return it->first;
		}
	}
	return -1;
}


void InteriorHandler::Load()
{
	sql::ResultSet *res = MySQLFunctions::ExecuteQuery("SELECT * FROM interiors");
	interiors->emplace(-1, new Interior("Main world", "", 1958.3783f, 1343.1572f, 15.3746f, 0, -1, 0, 0));
	while (res->next())
	{
		interiors->emplace(res->getInt("id"), new Interior(
			res->getString("name"), 
			res->getString("description"), 
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getDouble("facingangle"), 
			res->getInt("id"), 
			res->getInt("interiorid"), 
			res->getInt("virtualworld")));
	}
	delete res;

	res = MySQLFunctions::ExecuteQuery("SELECT * FROM defaultinteriors");
	defaultInteriors->emplace(-1, new Interior("Main world", "", 1958.3783f, 1343.1572f, 15.3746f, 0, -1, 0, 0));
	while (res->next())
	{
		defaultInteriors->emplace(res->getInt("id"), new Interior(
			res->getString("name"), 
			res->getString("description"), 
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getDouble("facingangle"), 
			res->getInt("id"), 
			res->getInt("interiorid"), 
			res->getInt("virtualworld")));
	}
	delete res;
}
