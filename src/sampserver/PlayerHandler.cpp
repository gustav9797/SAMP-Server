#include "PlayerHandler.h"
#include <sstream>
#include <sampgdk\a_samp.h>
#include <sampgdk\a_vehicles.h>
#include "WorldPositionObject.h"
#include "InteriorHandler.h"

PlayerHandler::PlayerHandler(GameUtility *gameUtility)
: Handler(gameUtility)
{
	players = new std::map<int, Player*>();
}


PlayerHandler::~PlayerHandler()
{
}


/*bool PlayerHandler::OnCommand(Player *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
if (cmd == "hack")
{
GivePlayerMoney(player->getId(), 500000);
return true;
}
else if (cmd == "pos")
{
float *x = new float(), *y = new float(), *z = new float(), *angle = new float();
GetPlayerPos(player->getId(), x, y, z);
std::stringstream pos;
pos << "Pos: X" << *x << " Y" << *y << " Z" << *z << "\nInterior: " << player->GetInterior() << " VirtualWorld: " << player->GetVirtualWorld();
SendClientMessage(player->getId(), 0xFFFFFFFF, pos.str().c_str());
delete x, y, z;
return true;
}
else if (cmd == "spawn")
{
TeleportPlayer(player->getId(), WorldPositionObject(1958.3783f, 1343.1572f, 15.3746f, gameUtility->interiorHandler->getInterior(-1)));
return true;
}
return false;
}*/

//TODO: add event for checkhack and subscribe
/*void PlayerHandler::CheckForHacks()
{
for (std::map<int, Player*>::iterator it = players->begin(); it != players->end(); it++)
{
if (it->second->getMoney() != GetPlayerMoney(it->first))
{
it->second->SendMessage(0xF81414, "Kicked from server: Moneyhacks");
//SetTimer(1000, false, KickDelayed, (void*)(it->first));
break;
}
}
}*/

void PlayerHandler::Load()
{
}

bool PlayerHandler::KickPlayer(int playerid, std::string message, GameUtility* gameUtility)
{
	std::stringstream s;
	s << "Kicked from server: " << message;
	SendClientMessage(playerid, 0xFF0000, s.str().c_str());
	SetTimer(1, false, KickDelayed, (void*)playerid);
	return true;
}

void SAMPGDK_CALL PlayerHandler::KickDelayed(int, void * playerId)
{
	Kick((int)playerId);
}

void PlayerHandler::TeleportPlayer(int playerid, WorldPositionObject pos)
{
	SetPlayerVirtualWorld(playerid, pos.virtualWorld_);
	SetPlayerInterior(playerid, pos.sampInteriorId_);
	SetPlayerPos(playerid, pos.x_, pos.y_, pos.z_);
	if (GetPlayerState(playerid) == 2)
	{
		int vehicleId = GetPlayerVehicleID(playerid);
		LinkVehicleToInterior(vehicleId, pos.sampInteriorId_);
		SetVehicleVirtualWorld(vehicleId, pos.virtualWorld_);
		SetVehiclePos(vehicleId, pos.x_, pos.y_, pos.z_);
		PutPlayerInVehicle(playerid, vehicleId, 0);
	}
	SetPVarInt(playerid, "oldinterior", GetPVarInt(playerid, "currentinterior"));
	SetPVarInt(playerid, "currentinterior", pos.interiorId_);
}

