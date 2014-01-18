#include "PickupHandler.h"
#include <sampgdk\core.h>
#include "MySQLFunctions.h"

PickupHandler::PickupHandler()
{
	pickupList = new std::map<int, Pickup*>();
}


PickupHandler::~PickupHandler()
{
	delete pickupList;
}

bool PickupHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	return false;
}

void PickupHandler::CheckForHacks()
{
}

Pickup* PickupHandler::GetPickup(int pickupId)
{
	if(pickupList->find(pickupId) != pickupList->end())
		return pickupList->at(pickupId);
	else
		ServerLog::Printf("Tried to get pickup which did not exist.");
	return nullptr;
}

bool PickupHandler::AddPickup(int pickupId, Pickup *pickup)
{
	if (pickupList->find(pickupId) == pickupList->end())
	{
		pickupList->emplace(pickupId, pickup);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO pickups(id, model, type, x, y, z, text, interiorid, sampinteriorid, virtualworld, destinationinteriorid, destinationpickupid) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
		statement->setInt(1, pickupId);
		statement->setInt(2, pickup->model_);
		statement->setInt(3, pickup->type_);
		statement->setDouble(4, pickup->x_);
		statement->setDouble(5, pickup->y_);
		statement->setDouble(6, pickup->z_);
		statement->setString(7, pickup->text_);
		statement->setInt(8, pickup->interiorid_);
		statement->setInt(9, pickup->sampinteriorid_);
		statement->setInt(10, pickup->virtualworld_);
		statement->setInt(11, pickup->destinationInterior);
		statement->setInt(12, pickup->destinationPickup);
		MySQLFunctions::ExecutePreparedQuery(statement);
		return true;
	}
	return false;
}

int PickupHandler::HandlerCreatePickup(int model, int type, float x, float y, float z, std::string text, int interiorid, int sampinteriorid, int virtualworld, int destinationInterior, int destinationPickup)
{
	int pickupId = CreatePickup(model, type, x, y, z, virtualworld);
	Pickup *pickup = new Pickup(model, type, x, y, z, text, interiorid, sampinteriorid, virtualworld);
	pickup->destinationInterior = destinationInterior;
	pickup->destinationPickup = destinationPickup;
	AddPickup(pickupId, pickup);
	return pickupId;
}

bool PickupHandler::DestroyPickup(int pickupId)
{
	if (pickupList->find(pickupId) != pickupList->end())
	{
		delete pickupList->at(pickupId);
		pickupList->erase(pickupId);
		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("DELETE FROM pickups WHERE id=? LIMIT 1");
		statement->setInt(1, pickupId);
		MySQLFunctions::ExecutePreparedQuery(statement);
		return true;
	}
	return false;
}

void PickupHandler::Load()
{
	sql::ResultSet *res = MySQLFunctions::ExecuteQuery("SELECT * FROM pickups");
	while (res->next())
	{
		int id = res->getInt("id");
		pickupList->emplace(id, new Pickup(
			res->getInt("model"),
			res->getInt("type"),
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getString("text"), 
			res->getInt("interiorid"), 
			res->getInt("sampinteriorid"), 
			res->getInt("virtualworld")));
		pickupList->at(id)->destinationInterior = res->getInt("destinationinteriorid");
		pickupList->at(id)->destinationPickup = res->getInt("destinationpickupid");

		CreatePickup(res->getInt("model"), res->getInt("type"), res->getDouble("x"), res->getDouble("y"), res->getDouble("z"), res->getInt("virtualworld"));
	}
	delete res;
}