#pragma once
#include "NormalItem.h"
class Weapon : NormalItem
{
public:
	Weapon(int id, int slot, int ammo, int model, int damage, std::string name);
	~Weapon();
	int id_;
	int slot_;
	int ammo_;
	int model_;
	int damage_;
	std::string name_;
};

