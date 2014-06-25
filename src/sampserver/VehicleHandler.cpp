#include <sstream>
#include "VehicleHandler.h"
#include "MySQLFunctions.h"
#include "PlayerHandler.h"
#include "VehicleDamageStatus.h"
#include "InteriorHandler.h"
#include "Interior.h"

VehicleHandler::VehicleHandler(void)
{
	vehicles = new std::map<int, Vehicle*>();
	playerVehicles = new std::map<std::string, std::map<int, Vehicle*>*>();
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
			Vehicle *vehicle = CreateVehicleForPlayer(model, 0, 0, 60, player, "", nullptr, gameUtility);
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
	else if(cmd == "mv")
	{
		if(args.size() == 3)
		{
			Vehicle *currentVehicle = vehicles->at(GetPlayerVehicleID(player->GetId()));
			if(currentVehicle != nullptr)
			{
				VehicleDamageStatus *dmg = currentVehicle->damageStatus_;
#pragma region door functions
				if(args[0] == "door")
				{
					if(args[1] == "damage")
					{
						if(args[2] == "frontleft")
							dmg->getDoors()->setDoorDamaged(Doors::DriversDoor, !dmg->getDoors()->getDoorDamaged(Doors::DriversDoor));
						else if(args[2] == "frontright")
							dmg->getDoors()->setDoorDamaged(Doors::CoDriversDoor, !dmg->getDoors()->getDoorDamaged(Doors::CoDriversDoor));
						else if(args[2] == "hood")
							dmg->getDoors()->setDoorDamaged(Doors::Hood, !dmg->getDoors()->getDoorDamaged(Doors::Hood));
						else if(args[2] == "trunk")
							dmg->getDoors()->setDoorDamaged(Doors::Trunk, !dmg->getDoors()->getDoorDamaged(Doors::Trunk));
					}
					if(args[1] == "remove")
					{
						if(args[2] == "frontleft")
							dmg->getDoors()->setDoorRemoved(Doors::DriversDoor, !dmg->getDoors()->getDoorRemoved(Doors::DriversDoor));
						else if(args[2] == "frontright")
							dmg->getDoors()->setDoorRemoved(Doors::CoDriversDoor, !dmg->getDoors()->getDoorRemoved(Doors::CoDriversDoor));
						else if(args[2] == "hood")
							dmg->getDoors()->setDoorRemoved(Doors::Hood, !dmg->getDoors()->getDoorRemoved(Doors::Hood));
						else if(args[2] == "trunk")
							dmg->getDoors()->setDoorRemoved(Doors::Trunk, !dmg->getDoors()->getDoorRemoved(Doors::Trunk));
					}
					else if(args[1] == "open")
					{
						if(args[2] == "frontleft")
							dmg->getDoors()->setDoorOpened(Doors::DriversDoor, !dmg->getDoors()->getDoorOpened(Doors::DriversDoor));
						else if(args[2] == "frontright")
							dmg->getDoors()->setDoorOpened(Doors::CoDriversDoor, !dmg->getDoors()->getDoorOpened(Doors::CoDriversDoor));
						else if(args[2] == "hood")
							dmg->getDoors()->setDoorOpened(Doors::Hood, !dmg->getDoors()->getDoorOpened(Doors::Hood));
						else if(args[2] == "trunk")
							dmg->getDoors()->setDoorOpened(Doors::Trunk, !dmg->getDoors()->getDoorOpened(Doors::Trunk));
					}
				}
#pragma endregion
#pragma region panel functions
				else if(args[0] == "panel")
				{
					if(args[1] == "damage")
					{
						if(args[2] == "frontleft")
							dmg->getPanels()->setPanelDamaged(Panels::FrontLeft, !dmg->getPanels()->getPanelDamaged(Panels::FrontLeft));
						else if(args[2] == "frontright")
							dmg->getPanels()->setPanelDamaged(Panels::FrontRight, !dmg->getPanels()->getPanelDamaged(Panels::FrontRight));
						else if(args[2] == "rearleft")
							dmg->getPanels()->setPanelDamaged(Panels::RearLeft, !dmg->getPanels()->getPanelDamaged(Panels::RearLeft));
						else if(args[2] == "rearright")
							dmg->getPanels()->setPanelDamaged(Panels::RearRight, !dmg->getPanels()->getPanelDamaged(Panels::RearRight));
						else if(args[2] == "windshield")
							dmg->getPanels()->setPanelDamaged(Panels::WindShield, !dmg->getPanels()->getPanelDamaged(Panels::WindShield));
						else if(args[2] == "frontbumper")
							dmg->getPanels()->setPanelDamaged(Panels::FrontBumper, !dmg->getPanels()->getPanelDamaged(Panels::FrontBumper));
						else if(args[2] == "rearbumper")
							dmg->getPanels()->setPanelDamaged(Panels::RearBumper, !dmg->getPanels()->getPanelDamaged(Panels::RearBumper));
					}
					else if(args[1] == "remove")
					{
						if(args[2] == "frontleft")
							dmg->getPanels()->setPanelRemoved(Panels::FrontLeft, !dmg->getPanels()->getPanelRemoved(Panels::FrontLeft));
						else if(args[2] == "frontright")
							dmg->getPanels()->setPanelRemoved(Panels::FrontRight, !dmg->getPanels()->getPanelRemoved(Panels::FrontRight));
						else if(args[2] == "rearleft")
							dmg->getPanels()->setPanelRemoved(Panels::RearLeft, !dmg->getPanels()->getPanelRemoved(Panels::RearLeft));
						else if(args[2] == "rearright")
							dmg->getPanels()->setPanelRemoved(Panels::RearRight, !dmg->getPanels()->getPanelRemoved(Panels::RearRight));
						else if(args[2] == "windshield")
							dmg->getPanels()->setPanelRemoved(Panels::WindShield, !dmg->getPanels()->getPanelRemoved(Panels::WindShield));
						else if(args[2] == "frontbumper")
							dmg->getPanels()->setPanelRemoved(Panels::FrontBumper, !dmg->getPanels()->getPanelRemoved(Panels::FrontBumper));
						else if(args[2] == "rearbumper")
							dmg->getPanels()->setPanelRemoved(Panels::RearBumper, !dmg->getPanels()->getPanelRemoved(Panels::RearBumper));
					}
				}
#pragma endregion
#pragma region light functions
				else if(args[0] == "light")
				{
					if(args[1] == "damage")
					{
						if(args[2] == "frontleft")
							dmg->getLights()->setLightDamaged(Lights::FrontLeftLight, !dmg->getLights()->getLightDamaged(Lights::FrontLeftLight));
						else if(args[2] == "frontright")
							dmg->getLights()->setLightDamaged(Lights::FrontRightLight, !dmg->getLights()->getLightDamaged(Lights::FrontRightLight));
						else if(args[2] == "rearleft")
							dmg->getLights()->setLightDamaged(Lights::RearLeftLight, !dmg->getLights()->getLightDamaged(Lights::RearLeftLight));
						else if(args[2] == "rearright")
							dmg->getLights()->setLightDamaged(Lights::RearRightLight, !dmg->getLights()->getLightDamaged(Lights::RearRightLight));
					}
				}
#pragma endregion
#pragma region tire functions
				else if(args[0] == "tire")
				{
					if(args[1] == "damage")
					{
						if(args[2] == "frontleft")
							dmg->getTires()->setTireDamaged(Tires::FrontLeftTire, !dmg->getTires()->getTireDamaged(Tires::FrontLeftTire));
						else if(args[2] == "frontright")
							dmg->getTires()->setTireDamaged(Tires::FrontRightTire, !dmg->getTires()->getTireDamaged(Tires::FrontRightTire));
						else if(args[2] == "rearleft")
							dmg->getTires()->setTireDamaged(Tires::RearLeftTire, !dmg->getTires()->getTireDamaged(Tires::RearLeftTire));
						else if(args[2] == "rearright")
							dmg->getTires()->setTireDamaged(Tires::RearRightTire, !dmg->getTires()->getTireDamaged(Tires::RearRightTire));
					}
				}
#pragma endregion
				currentVehicle->setDamage(dmg->getHealth(), dmg->getPanelsRaw(), dmg->getDoorsRaw(), dmg->getLightsRaw(), dmg->getTiresRaw());
			}
		}
		return true;
	}
	else if (cmd == "repair")
	{
		Vehicle *currentVehicle = vehicles->at(GetPlayerVehicleID(player->GetId()));
		if (currentVehicle != nullptr)
		{
			currentVehicle->Repair();
		}
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
		std::string licensePlate = res->getString("licenseplate");

		Vehicle *vehicle = new Vehicle(
			res->getInt("model"), 
			res->getDouble("x"),
			res->getDouble("y"),
			res->getDouble("z"),
			res->getDouble("rotation"), 
			res->getInt("color1"), 
			res->getInt("color2"), 
			res->getInt("respawndelay"), 
			licensePlate);

		vehicle->setDamage(res->getInt("health"), res->getInt("healthpanels"), res->getInt("healthdoors"), res->getInt("healthlights"), res->getInt("healthtires"));

		Interior *interior = gameUtility->interiorHandler->getInterior(res->getInt("interior"));
		if(interior != nullptr)
		{
			vehicle->setVirtualWorld(interior->virtualWorld_);
			vehicle->LinkToInterior(interior->sampInteriorId_);
		}

		vehicles->emplace(vehicle->getId(), vehicle);
		std::string owner = res->getString("owner");
		if(owner != "server")
		{
			if(playerVehicles->find(owner) == playerVehicles->end())
				playerVehicles->emplace(owner, new std::map<int, Vehicle*>);
			std::map<int, Vehicle*>* playerVehicles_ = playerVehicles->at(owner);
			if(playerVehicles_ != nullptr)
			{
				playerVehicles_->emplace(vehicle->getId(), vehicle);
			}
		}
	}
	delete res;
}

void VehicleHandler::RemoveVehicle(int vehicleId)
{
	if(vehicles->find(vehicleId) != vehicles->end())
	{
		Vehicle *vehicle = vehicles->at(vehicleId);
		vehicle->Destroy();
		std::string licensePlate = vehicle->licensePlate_;
		delete vehicles->at(vehicleId);
		vehicles->erase(vehicleId);
		for(auto it = playerVehicles->begin(); it != playerVehicles->end(); it++)
		{
			std::map<int, Vehicle*> *playerVehicles_ = it->second;
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
Vehicle *VehicleHandler::CreateVehicle(int model, int interior, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, std::string licensePlate, MyPlayer *owner, GameUtility *gameUtility)
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

	Vehicle *vehicle = new Vehicle(model, x, y, z, rotation, color1, color2, respawnDelay, licensePlate);
	Interior *interior_ = gameUtility->interiorHandler->getInterior(interior);

	if(interior_ != nullptr)
	{
		vehicle->setVirtualWorld(interior_->virtualWorld_);
		vehicle->LinkToInterior(interior_->sampInteriorId_);
		SetVehicleParamsEx(vehicle->getId(), true, true, false, false, false, false, false);
		vehicles->emplace(vehicle->getId(), vehicle);

		if(owner != nullptr)
		{
			if(playerVehicles->find(owner->GetName()) == playerVehicles->end())
				playerVehicles->emplace(owner->GetName(), new std::map<int, Vehicle*>());
			std::map<int, Vehicle*> *playerOwnedVehicles = playerVehicles->at(owner->GetName());
			if(playerOwnedVehicles == nullptr)
				playerOwnedVehicles = new std::map<int, Vehicle*>();
			playerOwnedVehicles->emplace(vehicle->getId(), vehicle);
		}

		sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO vehicles(licenseplate, owner, interior, model, x, y, z, rotation, color1, color2, respawndelay) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
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
Vehicle *VehicleHandler::CreateVehicleForPlayer(int model, int color1, int color2, int respawnDelay, MyPlayer *player, std::string licensePlate, MyPlayer *owner, GameUtility *gameUtility)
{
	float *x = new float(), *y = new float(), *z = new float(), *rotation = new float();
	player->GetPos(x, y, z);
	player->GetFacingAngle(rotation);
	Vehicle *vehicle = CreateVehicle(model, GetPVarInt(player->GetId(), "currentinterior"), *x, *y, *z, *rotation, color1, color2, respawnDelay, licensePlate, owner, gameUtility);//Vehicle::Create(model, *x, *y, *z, *rotation, color1, color2, respawnDelay);
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
		std::map<int, Vehicle*>* temp = playerVehicles->at(player->GetName());
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
		Vehicle *vehicle = vehicles->at(vehicleId);
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
		Vehicle *vehicle = vehicles->at(vehicleId);
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
