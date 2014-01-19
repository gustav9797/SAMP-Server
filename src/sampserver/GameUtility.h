#pragma once
class PlayerHandler;
class InteriorHandler;
class HouseHandler;
class WeaponHandler;
class VehicleHandler;
class ObjectHandler;
class GameUtility
{
public:
	GameUtility(void);
	~GameUtility(void);
	void Load();
	PlayerHandler *playerHandler;
	InteriorHandler *interiorHandler;
	HouseHandler *houseHandler;
	WeaponHandler *weaponHandler;
	VehicleHandler *vehicleHandler;
	ObjectHandler *objectHandler;
};

