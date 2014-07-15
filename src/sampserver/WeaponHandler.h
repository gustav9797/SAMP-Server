#pragma once
#include "Handler.h"
#include <map>
class Weapon;
class WeaponHandler : public Handler
{
private:
	std::map<int, Weapon*> *avaliableWeapons;
public:
	WeaponHandler(void);
	~WeaponHandler(void);
	virtual bool OnCommand(Player *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	Weapon* getWeapon(int weaponId);
};

