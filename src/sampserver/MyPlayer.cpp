#include "MyPlayer.h"
#include "Weapon.h"
#include "WeaponHandler.h"


MyPlayer::MyPlayer(int id) : Player(id)
{
	money_ = 0;
	weapons = new std::map<int, Weapon*>();
	vehicles = new std::map<int, MyVehicle*>();
}


MyPlayer::~MyPlayer()
{
	delete weapons;
}

void MyPlayer::GiveWeapon(Weapon *weapon)
{
	if(weapon != nullptr)
	{
		Weapon *currentWeapon = getWeapon(weapon->slot_);
		if(currentWeapon == nullptr || currentWeapon->id_ != weapon->id_)
			weapons->emplace(weapon->slot_, weapon);
		else
			currentWeapon->ammo_ += weapon->ammo_;
		GivePlayerWeapon(GetId(), weapon->id_, weapon->ammo_);
	}
}

Weapon *MyPlayer::getWeapon(int slot)
{
	if (weapons->find(slot) != weapons->end())
		return(weapons->at(slot));
	return nullptr;
}

void MyPlayer::RemoveWeapon(int weaponid, WeaponHandler* weaponHandler)
{
	Weapon *avaliableWeapon = weaponHandler->getWeapon(weaponid);
	if (weapons->find(avaliableWeapon->slot_) != weapons->end())
	{
		if(weapons->at(avaliableWeapon->slot_) != nullptr && weapons->at(avaliableWeapon->slot_)->id_ == weaponid)
		{
			delete weapons->at(avaliableWeapon->slot_);
			weapons->erase(avaliableWeapon->slot_);
			ResetPlayerWeapons(GetId());
			for(auto it = weapons->begin(); it != weapons->end(); it++)
			{
				GivePlayerWeapon(GetId(), it->second->id_, it->second->ammo_);
			}
		}
	}
}