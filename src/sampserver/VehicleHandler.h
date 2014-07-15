#pragma once
#include "Handler.h"
#include "Vehicle.h"
#include "Player.h"
#include <map>
#include <vector>
class VehicleHandler : public Handler
{
private:
	std::map<int, Vehicle*> *vehicles;
	std::map<std::string, std::map<int, Vehicle*>*> *playerVehicles;
public:
	VehicleHandler(GameUtility *gameUtility);
	~VehicleHandler(void);
	virtual void Load();
	void RemoveVehicle(int vehicleId);
	void RemoveCurrentVehicle(Player *player);
	Vehicle *CreateVehicle(int model, int interior, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, std::string licensePlate, Player *owner, GameUtility *gameUtility);
	Vehicle *CreateVehicleForPlayer(int model, int color1, int color2, int respawnDelay, Player *player, std::string licensePlate, Player *owner, GameUtility *gameUtility);
	bool VehicleOwnedByPlayer(int vehicleId, Player *player);
	std::string VehicleOwnedByAnyPlayer(int vehicleId);
	void SaveVehicleData(int vehicleId);
	int getFreeVehicleUniqueId();
	std::string randomizeLicensePlate(int length=8);
	bool isLicensePlateUsed(std::string);
	bool UpdateVehicleDamageStatus(int vehicleId, int playerId);
};

