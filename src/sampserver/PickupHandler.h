#pragma once
#include <iostream>
#include <map>
#include "Pickup.h"
#include "InteriorHandler.h"
#include "MyPlayer.h";
class PickupHandler : public Handler
{
private:
	std::map<int, Pickup*> *pickupList;
	bool AddPickup(int pickupId, Pickup *pickup);
public:
	PickupHandler();
	~PickupHandler();
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load();
	Pickup* GetPickup(int pickupId);
	int HandlerCreatePickup(int model, int type, float x, float y, float z, std::string text, int interiorid, int sampinteriorid, int virtualworld, int destinationInterior = -1, int destinationPickup = -1);
	bool DestroyPickup(int pickupId);
};

