#include "Player.h"
#include "Weapon.h"
#include "WeaponHandler.h"

Player::Player(int id)
{
	id_ = id;
	money_ = 0;
	weapons = new std::map<int, Weapon*>();
	vehicles = new std::map<int, Vehicle*>();
}


Player::~Player()
{
	delete weapons;
}

void Player::GiveWeapon(Weapon *weapon)
{
	if (weapon != nullptr)
	{
		Weapon *currentWeapon = getWeapon(weapon->slot_);
		if (currentWeapon == nullptr)
			weapons->emplace(weapon->slot_, weapon);
		else if (currentWeapon->id_ != weapon->id_)
			(*weapons)[weapon->slot_] = weapon;
		else
			currentWeapon->ammo_ += weapon->ammo_;
		GivePlayerWeapon(getId(), weapon->id_, weapon->ammo_);
	}
}

Weapon *Player::getWeapon(int slot)
{
	if (weapons->find(slot) != weapons->end())
		return(weapons->at(slot));
	return nullptr;
}

void Player::RemoveWeapon(int weaponid, WeaponHandler* weaponHandler)
{
	Weapon *avaliableWeapon = weaponHandler->getWeapon(weaponid);
	if (weapons->find(avaliableWeapon->slot_) != weapons->end())
	{
		if (weapons->at(avaliableWeapon->slot_) != nullptr && weapons->at(avaliableWeapon->slot_)->id_ == weaponid)
		{
			delete weapons->at(avaliableWeapon->slot_);
			weapons->erase(avaliableWeapon->slot_);
			ResetPlayerWeapons(getId());
			for (auto it = weapons->begin(); it != weapons->end(); it++)
			{
				GivePlayerWeapon(getId(), it->second->id_, it->second->ammo_);
			}
		}
	}
}