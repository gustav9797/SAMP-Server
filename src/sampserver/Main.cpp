#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include<cstdlib>
#include<ctime>

#include <sampgdk\a_players.h>
#include <sampgdk\a_vehicles.h>
#include <sampgdk\a_samp.h>
#include <sampgdk\core.h>
#include <sampgdk\plugin.h>

#include "HouseHandler.h"
#include "PlayerHandler.h"
#include "WeaponHandler.h"
#include "InteriorHandler.h"
#include "PickupHandler.h"
#include "VehicleHandler.h"
#include "ObjectHandler.h"
#include "WorldPositionObject.h"
#include "MySQLFunctions.h"
#include "RegisterLogin.h"
#include "Weapon.h"
#include "GameUtility.h"

namespace main
{
	static ThisPlugin samptest;
	PlayerHandler *playerHandler = new PlayerHandler();
	InteriorHandler *interiorHandler = new InteriorHandler();
	PickupHandler *pickupHandler = new PickupHandler();
	HouseHandler *houseHandler = new HouseHandler();
	WeaponHandler *weaponHandler = new WeaponHandler();
	VehicleHandler *vehicleHandler = new VehicleHandler();
	ObjectHandler *objectHandler =  new ObjectHandler();
	GameUtility *gameUtility = new GameUtility();

	std::vector<Handler*> *handlers = new std::vector<Handler*>();
	using namespace std;

	static void Load()
	{
		for(auto i : *handlers)
		{
			i->Load();
		}
	}

	static string ToString(int number)
	{
		int Number = number; // number to convert
		char Result[16]; // string which will contain the number
		sprintf_s(Result, "%d", Number);
		return Result;
	}

	static vector<string> GetParams(std::string input)
	{
		std::vector<std::string> tokens;
		istringstream iss(input);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
		if(tokens.size() >= 1)
			tokens.erase(tokens.begin());
		return tokens;
	}

	static std::string GetCommand(std::string input)
	{
		std::vector<std::string> tokens;
		istringstream iss(input);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
		return tokens.at(0);
	}

	static void SAMPGDK_CALL KickPublic(int, void * playerid)
	{
		Kick((int)playerid);
	}

	static void SAMPGDK_CALL CheckForHacks(int, void *) {
		for(auto i : *handlers)
		{
			i->CheckForHacks();
		}
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
		srand(time(0));
		std::cout << "Game is initializing..";
		MySQLFunctions::Initialize();
		handlers->push_back(playerHandler);
		handlers->push_back(interiorHandler);
		handlers->push_back(pickupHandler);
		handlers->push_back(houseHandler);
		handlers->push_back(vehicleHandler);
		handlers->push_back(weaponHandler);
		handlers->push_back(objectHandler);
		gameUtility->houseHandler = houseHandler;
		gameUtility->interiorHandler = interiorHandler;
		gameUtility->pickupHandler = pickupHandler;
		gameUtility->playerHandler = playerHandler;
		gameUtility->vehicleHandler = vehicleHandler;
		gameUtility->weaponHandler = weaponHandler;
		gameUtility->objectHandler = objectHandler;
		std::cout << "  Initialized" << std::endl;
		std::cout << "MySQL data is loading...";
		Load();
		std::cout << "  Loaded" << std::endl;
		SetGameModeText("sampserver v1.0");
		DisableInteriorEnterExits();
		EnableStuntBonusForAll(false);
		SetTimer(2000, true, CheckForHacks, 0);
		ServerLog::Printf("--------------------------------------------------\n");
		ServerLog::Printf("   The most softcoded gamemode ever was loaded!    \n");
		ServerLog::Printf("--------------------------------------------------\n");
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
		SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the samptest server!");
		SetPVarInt(playerid, "currentinterior", -1);
		playerHandler->players->emplace(playerid, new MyPlayer(playerid));
		return registerlogin::OnPlayerConnect(playerid);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
	{
		delete playerHandler->players->at(playerid);
		playerHandler->players->erase(playerid);
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
		SetSpawnInfo(playerid, NO_TEAM, 0, -72.4094f, -1123.83f, 1.07812f, 269.1425f, 0, 0, 0, 0, 0, 0);
		//SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
		//SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
		//SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f, CAMERA_CUT);
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerInteriorChange(int playerid, int newinteriorid, int oldinteriorid)
	{
		float *x = new float(), *y = new float(), *z = new float(), *angle = new float();
		GetPlayerPos(playerid, x, y, z);
		SetPVarInt(playerid, "currentinterior", interiorHandler->SampinterioridToInterior(newinteriorid, *x, *y, *z, GetPlayerVirtualWorld(playerid)));
		SendClientMessage(playerid, 0xFFFFFFFF, std::string("changed interior to " + ToString(GetPVarInt(playerid, "currentinterior"))).c_str());
		delete x, y, z;
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) {
		MyPlayer *player = playerHandler->players->at(playerid);
		std::string cmd = GetCommand(cmdtext);
		cmd.erase(0, 1);
		vector<string> args = GetParams(cmdtext);
		for(auto i : *handlers)
		{
			if(i->OnCommand(player, cmd, args, gameUtility))
				return true;
		}
		return false;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
	{
		int old = GetPVarInt(playerid, "currentPickup");
		Pickup *oldPickup = pickupHandler->GetPickup(old);
		if(oldPickup != nullptr && old != pickupid)
			oldPickup->OnExit();
		SetPVarInt(playerid, "currentPickup", pickupid);
		Pickup *pickup = pickupHandler->GetPickup(pickupid);
		if(pickup != nullptr)
		{
			if(old != pickupid)
				pickup->OnEnter();
			if(houseHandler->houses->find(pickup->destinationInterior) != houseHandler->houses->end())
			{
				House *house = houseHandler->houses->at(pickup->destinationInterior);
				std::string message = "House: " + house->name + "                Owner: " + ">.<";
				GameTextForPlayer(playerid, message.c_str(), 5000, 4);
			}
		}
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, char* inputtext)
	{
		if (dialogid == DIALOG_LOGIN || dialogid == DIALOG_REGISTER)
			return registerlogin::OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
		return false;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float damage, int weaponid)
	{
		if(issuerid != INVALID_PLAYER_ID) // If not self-inflicted
		{
			MyPlayer *victim = playerHandler->players->at(playerid);
			MyPlayer *issuer = playerHandler->players->at(issuerid);
			if(issuer != nullptr)
			{
				if(victim != nullptr)
				{
					Weapon *weapon = weaponHandler->getWeapon(weaponid);
					if(weapon !=  nullptr)
					{
						victim->SetHealth(victim->GetHealth() - weapon->damage_);
					}
					else
						throw new exception("OnPlayerTakeDamage: weapon does not exist");
				}
				else
					throw new exception("OnPlayerTakeDamage: victim is null");
			}
			else
				throw new exception("OnPlayerTakeDamage: Issuer is null");
		}
		return 1;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(oldkeys == KEY_FIRE || oldkeys == KEY_HANDBRAKE || newkeys == KEY_FIRE || newkeys == KEY_HANDBRAKE)
			{
				MyPlayer *shooter = playerHandler->players->at(playerid);
				if(shooter != nullptr)
				{
					int weaponId = GetPlayerWeapon(shooter->GetId());
					Weapon *avaliable = weaponHandler->getWeapon(weaponId);
					if(avaliable != nullptr && avaliable->ammo_ != -1)
					{
						Weapon *currentWeapon = shooter->getWeapon(avaliable->slot_);
						if(currentWeapon != nullptr)
						{
							int *unused = new int();
							int *ammo = new int();
							GetPlayerWeaponData(shooter->GetId(), avaliable->slot_, unused, ammo);
							if(ammo != nullptr)
							{
								currentWeapon->ammo_ = *ammo;
							}
							delete unused;
							delete ammo;
						}
					}
				}
			}
		}
		return false;
	}

	PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
		return SUPPORTS_VERSION | SUPPORTS_PROCESS_TICK;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
		return samptest.Load(ppData) >= 0;
	}

	PLUGIN_EXPORT void PLUGIN_CALL Unload() {
		samptest.Unload();
	}

	PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
		samptest.ProcessTimers();
	}
}


