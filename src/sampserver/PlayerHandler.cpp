#include "PlayerHandler.h"
#include <sampgdk\a_samp.h>
#include <sampgdk\a_vehicles.h>
#include "WorldPositionObject.h"
#include <sstream>

PlayerHandler::PlayerHandler()
{
	players = new std::map<int, MyPlayer*>();
}


PlayerHandler::~PlayerHandler()
{
}


bool PlayerHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	if (cmd == "hack")
	{
		GivePlayerMoney(player->GetId(), 500000);
		return true;
	}
	else if (cmd == "pos")
	{
		float *x = new float(), *y = new float(), *z = new float(), *angle = new float();
		GetPlayerPos(player->GetId(), x, y, z);
		std::stringstream pos;
		pos << "Pos: X" << *x << " Y" << *y << " Z" << *z;
		SendClientMessage(player->GetId(), 0xFFFFFFFF, pos.str().c_str());
		delete x, y, z;
		return true;
	}
	else if (cmd == "spawn")
	{
		SetPlayerVirtualWorld(player->GetId(), 0);
		SetPlayerInterior(player->GetId(), 0);
		SetPlayerPos(player->GetId(), 1958.3783f, 1343.1572f, 15.3746f);
		return true;
	}
	return false;
}

void PlayerHandler::CheckForHacks()
{
	for (std::map<int, MyPlayer*>::iterator it = players->begin(); it != players->end(); it++)
	{
		if (it->second->GetMoney() != GetPlayerMoney(it->first))
		{
			it->second->SendMessage(0xF81414, "Kicked from server: Moneyhacks");
			//SetTimer(1000, false, KickDelayed, (void*)(it->first));
			break;
		}
	}
}

void PlayerHandler::Load()
{
}

void SAMPGDK_CALL PlayerHandler::KickDelayed(int, void * playerId)
{
	Kick((int)playerId); //Fixa kick-fuKTION
}

void PlayerHandler::TeleportPlayer(int playerid, WorldPositionObject pos)
{
	SetPlayerVirtualWorld(playerid, pos.virtualworld_);
	SetPlayerInterior(playerid, pos.sampinteriorid_);
	SetPlayerPos(playerid, pos.x_, pos.y_, pos.z_);
	if (GetPlayerState(playerid) == 2)
	{
		int vehicleId = GetPlayerVehicleID(playerid);
		LinkVehicleToInterior(vehicleId, pos.sampinteriorid_);
		SetVehicleVirtualWorld(vehicleId, pos.virtualworld_);
		SetVehiclePos(vehicleId, pos.x_, pos.y_, pos.z_);
		PutPlayerInVehicle(playerid, vehicleId, 0);
	}
	SetPVarInt(playerid, "oldinterior", GetPVarInt(playerid, "currentinterior"));
	SetPVarInt(playerid, "currentinterior", pos.interiorid_);
}

