#include "WeaponHandler.h"
#include "Weapon.h"
#include "MyPlayer.h"
#include <iostream>
#include <sstream>

WeaponHandler::WeaponHandler(void)
{

}

WeaponHandler::~WeaponHandler(void)
{
}


void WeaponHandler::Load(GameUtility* gameUtility)
{
	avaliableWeapons = new std::map<int, Weapon*>();
	//slot 0, fist weapons
	avaliableWeapons->emplace(0, new Weapon(0, 0, -1, -1, 25, "Fist"));
	avaliableWeapons->emplace(1, new Weapon(1, 0, -1, 331, 25, "Brass Knuckles"));
	//slot 1, hand weapons
	avaliableWeapons->emplace(2, new Weapon(2, 1, -1, 333, 25, "Golf Club"));
	avaliableWeapons->emplace(3, new Weapon(3, 1, -1, 334, 25, "Nightstick"));
	avaliableWeapons->emplace(4, new Weapon(4, 1, -1, 335, 25, "Knife"));
	avaliableWeapons->emplace(5, new Weapon(5, 1, -1, 336, 25, "Baseball Bat"));
	avaliableWeapons->emplace(6, new Weapon(6, 1, -1, 337, 25, "Shovel"));
	avaliableWeapons->emplace(7, new Weapon(7, 1, -1, 338, 25, "Pool Cue"));
	avaliableWeapons->emplace(8, new Weapon(8, 1, -1, 339, 25, "Katana"));
	avaliableWeapons->emplace(9, new Weapon(9, 1, -1, 341, 50, "Chainsaw"));
	//slot 2, pistols
	avaliableWeapons->emplace(22, new Weapon(22, 2, 50, 346, 50, "9mm"));
	avaliableWeapons->emplace(23, new Weapon(23, 2, 50, 347, 45, "Silenced 9mm"));
	avaliableWeapons->emplace(24, new Weapon(24, 2, 50, 348, 75, "Desert Eagle"));
	//slot 3, shotguns
	avaliableWeapons->emplace(25, new Weapon(25, 3, 50, 349, 150, "Shotgun"));
	avaliableWeapons->emplace(26, new Weapon(26, 3, 50, 350, 150, "Sawnoff Shotgun"));
	avaliableWeapons->emplace(27, new Weapon(27, 3, 50, 351, 150, "Combat Shotgun"));
	//slot 4, smgs
	avaliableWeapons->emplace(28, new Weapon(28, 4, 200, 352, 50, "Micro SMG"));
	avaliableWeapons->emplace(29, new Weapon(29, 4, 200, 353, 50, "MP5"));
	avaliableWeapons->emplace(32, new Weapon(32, 4, 200, 372, 50, "Tec-9"));
	//slot 5, automatic rifles
	avaliableWeapons->emplace(30, new Weapon(30, 5, 200, 355, 100, "AK-47"));
	avaliableWeapons->emplace(31, new Weapon(31, 5, 200, 356, 100, "M4"));
	//slot 6, rifles
	avaliableWeapons->emplace(33, new Weapon(33, 6, 50, 357, 150, "Country Rifle"));
	avaliableWeapons->emplace(34, new Weapon(34, 6, 50, 358, 1000, "Sniper Rifle"));
	//slot 7, big guns
	avaliableWeapons->emplace(35, new Weapon(35, 7, 50, 359, 1000, "RPG"));
	avaliableWeapons->emplace(36, new Weapon(36, 7, 50, 360, 1000, "HS Rocket"));
	avaliableWeapons->emplace(37, new Weapon(37, 7, 50, 361, 250, "Flamethrower"));
	avaliableWeapons->emplace(38, new Weapon(38, 7, 50, 362, 200, "Minigun"));
	//slot 8, grenades + Satchel Charge
	avaliableWeapons->emplace(16, new Weapon(16, 8, 1, 342, 300, "Grenade"));
	avaliableWeapons->emplace(17, new Weapon(17, 8, 1, 343, 250, "Tear Gas"));
	avaliableWeapons->emplace(18, new Weapon(18, 8, 1, 344, 250, "Molotov Cocktail"));
	avaliableWeapons->emplace(39, new Weapon(39, 8, 1, 363, 700, "Satchel Charge"));
	//slot 9, spraycan, fire extinguishere, camera
	avaliableWeapons->emplace(41, new Weapon(41, 9, 40, 365, 50, "Spraycan"));
	avaliableWeapons->emplace(42, new Weapon(42, 9, 40, 366, 50, "Fire extinguisher"));
	avaliableWeapons->emplace(43, new Weapon(43, 9, 100, 367, -1, "Camera"));
	//slot 10, dildos, flowers, cane
	avaliableWeapons->emplace(10, new Weapon(10, 10, -1, 321, 25, "Double-ended Dildo"));
	avaliableWeapons->emplace(11, new Weapon(11, 10, -1, 322, 25, "Dildo"));
	avaliableWeapons->emplace(12, new Weapon(12, 10, -1, 323, 25, "Vibrator"));
	avaliableWeapons->emplace(13, new Weapon(13, 10, -1, 324, 25, "Silver Vibrator"));
	avaliableWeapons->emplace(14, new Weapon(14, 10, -1, 325, 25, "Flowers"));
	avaliableWeapons->emplace(15, new Weapon(15, 10, -1, 326, 25, "Cane"));
	//slot 11, goggles and parachute
	avaliableWeapons->emplace(44, new Weapon(44, 11, -1, 368, -1, "Night Vision Goggles"));
	avaliableWeapons->emplace(45, new Weapon(45, 11, -1, 369, -1, "Thermal Goggles"));
	avaliableWeapons->emplace(46, new Weapon(46, 11, 1, 371, -1, "Thermal Goggles"));
	//slot 12, detonator only
	avaliableWeapons->emplace(40, new Weapon(40, 12, -1, 364, -1, "Detonator"));
}

bool WeaponHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
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
		}
		else
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /wgive <weaponID>");
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
			SendClientMessage(player->GetId(), 0xFFFFFFFF, "Usage: /wremove <weaponID>");
		return true;
	}
	else if(cmd == "winfo")
	{
		int id = GetPlayerWeapon(player->GetId());
		Weapon *avaliable = WeaponHandler::avaliableWeapons->at(id);
		if(avaliable != nullptr)
		{
			Weapon *currentWeapon = player->getWeapon(avaliable->slot_);
			if(currentWeapon != nullptr)
			{
				std::stringstream info;
				info << "ID: " << currentWeapon->id_ << "\nName: " << currentWeapon->name_ << "\nAmmo: " << currentWeapon->ammo_ << std::endl;
				SendClientMessage(player->GetId(), 0xFFFFFFFF, info.str().c_str());
			}
			else
				SendClientMessage(player->GetId(), 0xFFFFFFFF, "You don't have any weapon selected.");
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
