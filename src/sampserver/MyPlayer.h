#pragma once
#include <iostream>
#include <map>
class WeaponHandler;
class Weapon;
class MyVehicle;
#include <sampgdk/a_players.h>
class MyPlayer : public Player
{
private:
	int money_;
	std::map<int, Weapon*> *weapons;
	std::map<int, MyVehicle*> *vehicles;
	//int GetFreeWeaponSlot();
	int getFreeVehicleSlot();
public:
	MyPlayer(int id);
	~MyPlayer();

	void GiveMoney(int money) { money_ += money; };
	void SetMoney(int money) { money_ = money; };
	void RemoveMoney(int money) { money_ -= money; };
	int getMoney() { return money_; };

	void GiveWeapon(Weapon *weapon);
	Weapon *getWeapon(int slot);
	void RemoveWeapon(int weaponid, WeaponHandler* weaponHandler);
};

