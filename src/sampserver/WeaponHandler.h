#pragma once
#include "Handler.h"
#include <map>
class Weapon;
class WeaponHandler : public Handler
{
private:
	std::map<int, Weapon*> *avaliableWeapons;
public:
	WeaponHandler(GameUtility *gameUtility);
	~WeaponHandler(void);
	virtual void Load();
	Weapon* getWeapon(int weaponId);
};

