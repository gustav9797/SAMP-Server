#pragma once
#include <iostream>
#include <map>
#include "House.h"
#include "InteriorHandler.h"
#include "PickupHandler.h"
class HouseHandler : public Handler
{
public:
	HouseHandler(void);
	~HouseHandler(void);
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load();
	std::map<int, House*> *houses;
	bool CreateHouse(int destinationId, float x, float y, float z, int interior, int sampinterior, int virtualworld, InteriorHandler *interiorHandler, PickupHandler *pickupHandler);
};

