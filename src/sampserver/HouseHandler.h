#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "Handler.h"

class House;
class InteriorHandler;
class GameUtility;
class Interior;
class Player;

class HouseHandler : public Handler
{
public:
	HouseHandler(GameUtility *gameUtility);
	~HouseHandler(void);
	virtual void Load();
	std::map<int, House*> *houses;
	bool CreateHouse(int destinationId, float x, float y, float z, Interior *interior, InteriorHandler *interiorHandler);
};

