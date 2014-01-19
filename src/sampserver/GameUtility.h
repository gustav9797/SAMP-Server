#pragma once
class PlayerHandler;
class InteriorHandler;
class PickupHandler;
class HouseHandler;
class WeaponHandler;
class VehicleHandler;
class ObjectHandler;
class GameUtility
{
public:
	GameUtility(void);
	~GameUtility(void);
	PlayerHandler *playerHandler;
	InteriorHandler *interiorHandler;
	PickupHandler *pickupHandler;
	HouseHandler *houseHandler;
	WeaponHandler *weaponHandler;
	VehicleHandler *vehicleHandler;
	ObjectHandler *objectHandler;
};

