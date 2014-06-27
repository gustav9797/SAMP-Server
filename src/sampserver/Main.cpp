#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

#include "HouseHandler.h"
#include "PlayerHandler.h"
#include "WeaponHandler.h"
#include "InteriorHandler.h"
#include "VehicleHandler.h"
#include "ObjectHandler.h"
#include "RegisterLoginHandler.h"

#include "WorldPositionObject.h"
#include "MySQLFunctions.h"
#include "Weapon.h"
#include "GameUtility.h"
#include "Pickup.h"
#include "House.h"
#include "CommandManager.h"
#include "EventHandler.h"

using sampgdk::logprintf;

namespace main
{
	using namespace std;
	PlayerHandler *playerHandler = new PlayerHandler();
	InteriorHandler *interiorHandler = new InteriorHandler();
	HouseHandler *houseHandler = new HouseHandler();
	WeaponHandler *weaponHandler = new WeaponHandler();
	VehicleHandler *vehicleHandler = new VehicleHandler();
	ObjectHandler *objectHandler =  new ObjectHandler();
	RegisterLoginHandler *registerLoginHandler = new RegisterLoginHandler();
	GameUtility *gameUtility = new GameUtility();

	CommandManager *commandManager = new CommandManager();
	EventHandler *eventHandler = new EventHandler();

	static string ToString(int number)
	{
		int Number = number; // number to convert
		char Result[16]; // string which will contain the number
		sprintf_s(Result, "%d", Number);
		return Result;
	}

	static void SAMPGDK_CALL CheckForHacks(int, void *) 
	{
		gameUtility->CheckForHacks();
	}

	static void SAMPGDK_CALL Update(int, void *) 
	{
		objectHandler->Update(gameUtility);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() 
	{
		std::cout << "Game is initializing..";
		srand(time(0));
		MySQLFunctions::Initialize();
		gameUtility->AddHandler(playerHandler);
		gameUtility->AddHandler(interiorHandler);
		gameUtility->AddHandler(houseHandler);
		gameUtility->AddHandler(vehicleHandler);
		gameUtility->AddHandler(weaponHandler);
		gameUtility->AddHandler(objectHandler);
		gameUtility->AddHandler(registerLoginHandler);
		gameUtility->houseHandler = houseHandler;
		gameUtility->interiorHandler = interiorHandler;
		gameUtility->playerHandler = playerHandler;
		gameUtility->vehicleHandler = vehicleHandler;
		gameUtility->weaponHandler = weaponHandler;
		gameUtility->objectHandler = objectHandler;
		gameUtility->registerLoginHandler = registerLoginHandler;
		gameUtility->eventHandler = eventHandler;
		std::cout << "  Initialized" << std::endl;

		std::cout << "MySQL data is loading...";
		gameUtility->Load(gameUtility);
		std::cout << "  Loaded" << std::endl;

		SetGameModeText("sampserver v1.0");
		DisableInteriorEnterExits();
		EnableStuntBonusForAll(false);
		SetTimer(2000, true, CheckForHacks, 0);
		SetTimer(500, true, Update, 0);
		//SetWorldTime(24);
		//ServerLog::Printf("--------------------------------------------------\n");
		//ServerLog::Printf("   The most softcoded gamemode ever was loaded!    \n");
		//ServerLog::Printf("--------------------------------------------------\n");
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
		SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the samptest server!");
		SetSpawnInfo(playerid, NO_TEAM, 0, -72.4094f, -1123.83f, 1.07812f, 269.1425f, 0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "currentinterior", -1);
		SetPVarInt(playerid, "selectedobject", -1);
		playerHandler->players->emplace(playerid, new Player(playerid));
		return registerLoginHandler->OnPlayerConnect(playerid);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
	{
		delete playerHandler->players->at(playerid);
		playerHandler->players->erase(playerid);
		return true;
	}

	static void SAMPGDK_CALL SetCameraTemp(int, void *fish)
	{
		SetCameraBehindPlayer((int)fish);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
		SpawnPlayer(playerid);
		SetTimer(1, false, SetCameraTemp, (void*)playerid);
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

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) 
	{
		/*Player *player = playerHandler->players->at(playerid);
		if (player)
		{
			commandManager->OnTextInput()
			std::string cmd = GetCommand(cmdtext);
			cmd.erase(0, 1);
			vector<string> args = GetParams(cmdtext);
			gameUtility->OnCommand(player, cmd, args, gameUtility);
		}
		else
			SendClientMessage(playerid, 0xFFFFFF, "Sorry, you do not exist.");
		return true;*/
		//eventHandler->PlayerCommandTextCallback(gameUtility, playerid, std::string(cmdtext));
		return true;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
	{
		int old = GetPVarInt(playerid, "currentPickup");
		Pickup *oldPickup = interiorHandler->getPickup(old);
		if(oldPickup != nullptr && old != pickupid)
			oldPickup->OnExit();
		SetPVarInt(playerid, "currentPickup", pickupid);
		std::stringstream s;
		s << "CurrentPickup: " << pickupid;
		SendClientMessage(playerid, 0xFFFFFFFF, s.str().c_str());
		Pickup *pickup = interiorHandler->getPickup(pickupid);
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
			return registerLoginHandler->OnDialogResponse(playerid, dialogid, response, listitem, inputtext, gameUtility);
		return false;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
	{
		if(issuerid != INVALID_PLAYER_ID) // If not self-inflicted
		{
			Player *victim = playerHandler->players->at(playerid);
			Player *issuer = playerHandler->players->at(issuerid);
			if(issuer != nullptr)
			{
				if(victim != nullptr)
				{
					Weapon *weapon = weaponHandler->getWeapon(weaponid);
					if(weapon !=  nullptr)
					{
						victim->SetHealth(victim->GetHealth() - weapon->damage_);
					}
				}
			}
		}
		return 1;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(oldkeys == KEY_FIRE || oldkeys == KEY_HANDBRAKE || newkeys == KEY_FIRE || newkeys == KEY_HANDBRAKE)
			{
				Player *shooter = playerHandler->players->at(playerid);
				if(shooter != nullptr)
				{
					int weaponId = GetPlayerWeapon(shooter->getId());
					Weapon *avaliable = weaponHandler->getWeapon(weaponId);
					if(avaliable != nullptr && avaliable->ammo_ != -1)
					{
						Weapon *currentWeapon = shooter->getWeapon(avaliable->slot_);
						if(currentWeapon != nullptr)
						{
							int *unused = new int();
							int *ammo = new int();
							GetPlayerWeaponData(shooter->getId(), avaliable->slot_, unused, ammo);
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

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectSampId, int model, float x, float y, float z)
	{
		return objectHandler->OnPlayerSelectObject(playerHandler->players->at(playerid), type, objectSampId, model, x, y, z);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, int type, int objectSampId, int response, float xo, float yo, float zo, float xr, float yr, float zr)
	{
		return objectHandler->OnPlayerEditObject(playerHandler->players->at(playerid), type, objectSampId, response, xo, yo, zo, xr, yr, zr);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerObjectMoved(int playerid, int objectSampId)
	{
		return objectHandler->OnPlayerObjectMoved(playerHandler->players->at(playerid), objectSampId);
	}

	PLUGIN_EXPORT bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
	{
		return vehicleHandler->UpdateVehicleDamageStatus(vehicleid, playerid);
	}

	PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
	{
		return sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
	}

	PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
	{
		return sampgdk::Load(ppData);
	}

	PLUGIN_EXPORT void PLUGIN_CALL Unload() 
	{
		sampgdk::Unload();
	}

	PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() 
	{
		sampgdk::ProcessTick();
	}
}


