#include <sstream>
#include "VehicleHandler.h"
#include "MySQLFunctions.h"
#include "PlayerHandler.h"
#include "VehicleDamageStatus.h"
#include "InteriorHandler.h"
#include "Interior.h"

VehicleHandler::VehicleHandler(void)
{
	vehicles = new std::map<int, MyVehicle*>();
	playerVehicles = new std::map<std::string, std::map<int, MyVehicle*>*>();
}


VehicleHandler::~VehicleHandler(void)
{
}

bool VehicleHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	if (cmd == "v")
	{
		if (args.size() == 1 && args[0] != "")
		{
			int model = atoi(args[0].c_str());
			MyVehicle *vehicle = CreateVehicleForPlayer(model, 0, 0, 60, player, "", nullptr, gameUtility);
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Vehicle spawned!");
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /v <vehicleID>");
		return true;
	}
	else if(cmd == "rv")
	{
		RemoveCurrentVehicle(player);
		return true;
	}
	else if(cmd == "sv")
	{
		int vehicleId = player->GetVehicleID();
		if(vehicleId != 0)
			SaveVehicleData(vehicleId);
		return true;
	}
	return false;
}

void VehicleHandler::CheckForHacks()
{

}

void VehicleHandler::Load(GameUtility* gameUtility)
{
	sql::ResultSet *res = MySQLFunctions::ExecuteQuery("SELECT * FROM vehicles");
	while (res->next())
	{
		Vehicle temp = Vehicle::Create(
			res->getInt("model"), 
			res->getDouble("x"), 
			res->getDouble("y"), 
			res->getDouble("z"), 
			res->getDouble("rotation"),
			res->getInt("color1"),
			res->getInt("color2"),
			res->getInt("respawndelay"));
		std::string licensePlate = res->getString("licenseplate");
		MyVehicle *vehicle = new MyVehicle(temp, res->getInt("color1"), res->getInt("color2"), res->getInt("respawndelay"), licensePlate);
		vehicle->UpdateDamageStatus(res->getInt("healthpanels"), res->getInt("healthdoors"), res->getInt("healthlights"), res->getInt("healthtires"));

		Interior *interior = gameUtility->interiorHandler->getInterior(res->getInt("interior"));
		if(interior != nullptr)
		{
			vehicle->SetVirtualWorld(interior->virtualWorld_);
			vehicle->LinkToInterior(interior->sampInteriorId_);
		}

		vehicles->emplace(vehicle->GetId(), vehicle);
		std::string owner = res->getString("owner");
		if(owner != "server")
		{
			if(playerVehicles->find(owner) == playerVehicles->end())
				playerVehicles->emplace(owner, new std::map<int, MyVehicle*>);
			std::map<int, MyVehicle*>* playerVehicles_ = playerVehicles->at(owner);
			if(playerVehicles_ != nullptr)
			{
				playerVehicles_->emplace(vehicle->GetId(), vehicle);
			}
		}
	}
	delete res;
}

void VehicleHandler::RemoveVehicle(int vehicleId)
{
	if(vehicles->find(vehicleId) != vehicles->end())
	{
		MyVehicle *vehicle = vehicles->at(vehicleId);
		vehicle->Destroy();
		std::string licensePlate = vehicle->licensePlate_;
		delete vehicles->at(vehicleId);
		vehicles->erase(vehicleId);
		for(auto it = playerVehicles->begin(); it != playerVehicles->end(); it++)
		{
			std::map<int, MyVehicle*> *playerVehicles_ = it->second;
			if(playerVehicles_ != nullptr && playerVehicles_->find(vehicleId) != playerVehicles_->end())
			{
				playerVehicles_->erase(vehicleId);
				break;
			}
		}
		sql::PreparedStatement *s = MySQLFunctions::con->prepareStatement("DELETE FROM `samp`.`vehicles` WHERE `licenseplate`=?");
		s->setString(1, licensePlate);
		MySQLFunctions::ExecutePreparedQuery(s);
	}
}

void VehicleHandler::RemoveCurrentVehicle(MyPlayer *player)
{
	int vehicleId = player->GetVehicleID();
	if(vehicleId != 0)
		RemoveVehicle(vehicleId);
}

//Creates a vehicle at specified position (owner is null for server)
MyVehicle *VehicleHandler::CreateVehicle(int model, int interior, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, std::string licensePlate, MyPlayer *owner, GameUtility *gameUtility)
{
	while(isLicensePlateUsed(licensePlate))
		licensePlate = randomizeLicensePlate();
	if(licensePlate == "")
		licensePlate = randomizeLicensePlate();
	else if(licensePlate.length() > 8 || isLicensePlateUsed(licensePlate))
		return nullptr;

	std::string ownerName;
	if(owner == nullptr)
		ownerName = "server";
	else
		ownerName = owner->GetName();

	Vehicle temp = Vehicle::Create(model, x, y, z, rotation, color1, color2, respawnDelay);
	MyVehicle *vehicle = new MyVehicle(temp, color1, color2, respawnDelay, licensePlate);
	Interior *interior_ = gameUtility->interiorHandler->getInterior(interior);

	if(interior_ != nullptr)
	{
		vehicle->SetVirtualWorld(interior_->virtualWorld_);
		vehicle->LinkToInterior(interior_->sampInteriorId_);
		vehicle->SetNumberPlate(licensePlate.c_str());
		vehicles->emplace(vehicle->GetId(), vehicle);

		if(owner != nullptr)
		{
			if(playerVehicles->find(owner->GetName()) == playerVehicles->end())
				playerVehicles->emplace(owner->GetName(), new std::map<int, MyVehicle*>());
			std::map<int, MyVehicle*> *playerOwnedVehicles = playerVehicles->at(owner->GetName());
			if(playerOwnedVehicles == nullptr)
				playerOwnedVehicles = new std::map<int, MyVehicle*>();
			playerOwnedVehicles->emplace(vehicle->GetId(), vehicle);
		}

		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO vehicles(licenseplate, owner, interior, model, x, y, z, rotation, color1, color2, respawndelay) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
		statement->setString(1, licensePlate);
		statement->setString(2, ownerName);
		statement->setInt(3, interior);
		statement->setInt(4, model);
		statement->setDouble(5, x);
		statement->setDouble(6, y);
		statement->setDouble(7, z);
		statement->setDouble(8, rotation);
		statement->setInt(9, color1);
		statement->setInt(10, color2);
		statement->setInt(11, respawnDelay);
		MySQLFunctions::ExecutePreparedQuery(statement);
	}
	return vehicle;
}

//Creates a vehicle at players position, puts player inside it (owner is null for server)
MyVehicle *VehicleHandler::CreateVehicleForPlayer(int model, int color1, int color2, int respawnDelay, MyPlayer *player, std::string licensePlate, MyPlayer *owner, GameUtility *gameUtility)
{
	float *x = new float(), *y = new float(), *z = new float(), *rotation = new float();
	player->GetPos(x, y, z);
	player->GetFacingAngle(rotation);
	MyVehicle *vehicle = CreateVehicle(model, GetPVarInt(player->GetId(), "currentinterior"), *x, *y, *z, *rotation, color1, color2, respawnDelay, licensePlate, owner, gameUtility);//Vehicle::Create(model, *x, *y, *z, *rotation, color1, color2, respawnDelay);
	delete x, y, z, rotation;
	if(vehicle == nullptr)
		return nullptr;
	PutPlayerInVehicle(player->GetId(), vehicle->getId(), 0);
	return vehicle;
}

//Checks if vehicle is owned by the specified player
bool VehicleHandler::VehicleOwnedByPlayer(int vehicleId, MyPlayer *player)
{
	if(playerVehicles->find(player->GetName()) != playerVehicles->end())
	{
		std::map<int, MyVehicle*>* temp = playerVehicles->at(player->GetName());
		if(temp != nullptr && (temp->find(vehicleId) != temp->end()))
			return true;
	}
	return false;
}

//Checks if vehicle is owned by any player, returns name of player (name/nullptr)
std::string VehicleHandler::VehicleOwnedByAnyPlayer(int vehicleId)
{
	for(auto i : *playerVehicles)
	{
		if(i.second->find(vehicleId) != i.second->end())
			return i.first;
	}
	return nullptr;
}

//Updates vehicle data in MySQL
void VehicleHandler::SaveVehicleData(int vehicleId)
{
	if(vehicles->find(vehicleId) != vehicles->end())
	{
		MyVehicle *vehicle = vehicles->at(vehicleId);
		sql::PreparedStatement *s = MySQLFunctions::con->prepareStatement("UPDATE `samp`.`vehicles` SET `x`=?, `y`=?, `z`=?, `rotation`=?, `color1`=?, `color2`=? WHERE `licenseplate`=?");

		float *x = new float(), *y = new float(), *z = new float(), *rotation = new float();
		vehicle->GetPos(x, y, z);
		vehicle->GetZAngle(rotation);
		s->setDouble(1, *x);
		s->setDouble(2, *y);
		s->setDouble(3, *z);
		s->setDouble(4, *rotation);
		s->setInt(5, vehicle->color1_);
		s->setInt(6, vehicle->color2_);
		s->setString(7, vehicle->licensePlate_);
		MySQLFunctions::ExecutePreparedQuery(s);
		delete x, y, z, rotation;
	}
}

int VehicleHandler::getFreeVehicleUniqueId()
{
	int openSlot = -1;
	for (int i = 0; true; i++)
	{
		if (vehicles->find(i) == vehicles->end())
		{
			openSlot = i;
			break;
		}
	}
	return openSlot;
}

bool VehicleHandler::isLicensePlateUsed(std::string licensePlate)
{
	for(auto it = vehicles->begin(); it != vehicles->end(); it++)
	{
		if(it->second->licensePlate_ == licensePlate)
			return true;
	}
	return false;
}

std::string VehicleHandler::randomizeLicensePlate(int length)
{
	char licensePlateChars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::stringstream output;
	for(int i = 0; i < 8; i++)
	{
		int j = rand() % (sizeof(licensePlateChars) - 1);
		output << licensePlateChars[j];
	}
	return output.str();
}

bool VehicleHandler::UpdateVehicleDamageStatus(int vehicleId, int playerId)
{
	if(vehicles->find(vehicleId) != vehicles->end())
	{
		MyVehicle *vehicle = vehicles->at(vehicleId);
		int *panels = new int();
		int *doors = new int();
		int *lights = new int();
		int *tires = new int();
		float *health = new float();
		GetVehicleHealth(vehicleId, health);
		GetVehicleDamageStatus(vehicleId, panels, doors, lights, tires);
		vehicles->at(vehicleId)->setDamage(*health, *panels, *doors, *lights, *tires);

		std::stringstream s;
		s << "SAMP Panels:" << *panels << " Doors:" << *doors << " Lights:" << *lights << " Tires:" << *tires;// << " Health:" << *health;
		SendClientMessage(playerId, 0xFFFFFFFF, s.str().c_str());

		sql::PreparedStatement *st = MySQLFunctions::con->prepareStatement("UPDATE `samp`.`vehicles` SET `health`=?, `healthpanels`=?, `healthdoors`=?, `healthlights`=?, `healthtires`=? WHERE `licenseplate`=?");
		st->setDouble(1, *health);
		st->setInt(2, *panels);
		st->setInt(3, *doors);
		st->setInt(4, *lights);
		st->setInt(5, *tires);
		st->setString(6, vehicle->licensePlate_);
		MySQLFunctions::ExecutePreparedQuery(st);
		delete panels, doors, lights, tires, health;
	}
	return true;
}
