#pragma once
#include "Handler.h"
#include "Vehicle.h"
#include "MyPlayer.h"
#include <map>
#include <vector>
class VehicleHandler : public Handler
{
private:
	std::map<int, Vehicle*> *vehicles;
	std::map<std::string, std::map<int, Vehicle*>*> *playerVehicles;
public:
	VehicleHandler(void);
	~VehicleHandler(void);
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	void RemoveVehicle(int vehicleId);
	void RemoveCurrentVehicle(MyPlayer *player);
	Vehicle *CreateVehicle(int model, int interior, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, std::string licensePlate, MyPlayer *owner, GameUtility *gameUtility);
	Vehicle *CreateVehicleForPlayer(int model, int color1, int color2, int respawnDelay, MyPlayer *player, std::string licensePlate, MyPlayer *owner, GameUtility *gameUtility);
	bool VehicleOwnedByPlayer(int vehicleId, MyPlayer *player);
	std::string VehicleOwnedByAnyPlayer(int vehicleId);
	void SaveVehicleData(int vehicleId);
	int getFreeVehicleUniqueId();
	std::string randomizeLicensePlate(int length=8);
	bool isLicensePlateUsed(std::string);
	bool UpdateVehicleDamageStatus(int vehicleId, int playerId);
};

