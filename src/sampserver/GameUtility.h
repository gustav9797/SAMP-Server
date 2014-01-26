#pragma once
class PlayerHandler;
class InteriorHandler;
class HouseHandler;
class WeaponHandler;
class VehicleHandler;
class ObjectHandler;
class MyPlayer;
class WorldPositionObject;
class Interior;

class GameUtility
{
public:
	GameUtility(void);
	~GameUtility(void);
	void Load();
	static bool IsPlayerClose(MyPlayer *player, WorldPositionObject object, float range);
	static bool IsPlayerClose(MyPlayer *player, float x, float y, float z, Interior *interior, float range);
	PlayerHandler *playerHandler;
	InteriorHandler *interiorHandler;
	HouseHandler *houseHandler;
	WeaponHandler *weaponHandler;
	VehicleHandler *vehicleHandler;
	ObjectHandler *objectHandler;
};

