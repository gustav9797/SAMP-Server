#include "Weapon.h"

Weapon::Weapon(int id, int slot, int ammo, int model, int damage, std::string name, int cost)
	: NormalItem(name)
{
	id_ = id;
	slot_ = slot;
	ammo_ = ammo;
	model_ = model;
	damage_ = damage;
	name_ = name;
	cost_ = cost;
}


Weapon::~Weapon()
{
}
