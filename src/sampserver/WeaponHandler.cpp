#include "WeaponHandler.h"
#include <iostream>
#include <sstream>
#include "Weapon.h"
#include "Player.h"
#include "MySQLFunctions.h"

WeaponHandler::WeaponHandler(void)
{
	avaliableWeapons = new std::map<int, Weapon*>();
}

WeaponHandler::~WeaponHandler(void)
{
}


void WeaponHandler::Load(GameUtility* gameUtility)
{
	sql::ResultSet *res = MySQLFunctions::ExecuteQuery("SELECT * FROM weapontypes");
	while (res->next())
	{
		avaliableWeapons->emplace(res->getInt("id"), new Weapon(res->getInt("id"), res->getInt("slot"), res->getInt("ammo"), res->getInt("model"), res->getInt("damage"), res->getString("name"), res->getInt("cost")));
	}
	delete res;
}

bool WeaponHandler::OnCommand(Player *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	if(cmd == "wgive")
	{
		if(args.size() > 0)
		{
			int id = atoi(args[0].c_str());
			Weapon *avaliable = getWeapon(id);
			if(avaliable != nullptr)
			{
				player->GiveWeapon(new Weapon(*avaliable));
			}
			else
				SendClientMessage(player->getId(), 0xFFFFFFFF, "Weapon does not exist.");
		}
		else
			SendClientMessage(player->getId(), 0xFFFFFFFF, "Usage: /wgive <weaponID>");
		return true;
	}
	else if(cmd == "wremove")
	{
		if(args.size() > 0)
		{
			int id = atoi(args[0].c_str());
			player->RemoveWeapon(id, this);
		}
		else
			SendClientMessage(player->getId(), 0xFFFFFFFF, "Usage: /wremove <weaponID>");
		return true;
	}
	else if(cmd == "winfo")
	{
		int id = GetPlayerWeapon(player->getId());
		Weapon *avaliable = WeaponHandler::avaliableWeapons->at(id);
		if(avaliable != nullptr)
		{
			Weapon *currentWeapon = player->getWeapon(avaliable->slot_);
			if(currentWeapon != nullptr)
			{
				std::stringstream info;
				info << "ID: " << currentWeapon->id_ << "\nName: " << currentWeapon->name_ << "\nAmmo: " << currentWeapon->ammo_ << std::endl;
				SendClientMessage(player->getId(), 0xFFFFFFFF, info.str().c_str());
			}
			else
				SendClientMessage(player->getId(), 0xFFFFFFFF, "You don't have any weapon selected.");
		}
		return true;
	}
	return false;
}

void WeaponHandler::CheckForHacks()
{
}

Weapon* WeaponHandler::getWeapon(int weaponId)
{
	if(avaliableWeapons->find(weaponId) != avaliableWeapons->end())
		return avaliableWeapons->at(weaponId);
	return nullptr;
}
