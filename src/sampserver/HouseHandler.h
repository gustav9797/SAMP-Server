#pragma once
#include <iostream>
#include <map>
#include "House.h"
#include "InteriorHandler.h"
class HouseHandler : public Handler
{
public:
	HouseHandler(void);
	~HouseHandler(void);
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	std::map<int, House*> *houses;
	bool CreateHouse(int destinationId, float x, float y, float z, Interior *interior, InteriorHandler *interiorHandler);
};

