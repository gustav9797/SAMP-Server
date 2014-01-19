#pragma once
#include <iostream>
#include <sampgdk/a_samp.h>
#include "WorldPositionObject.h"

class Pickup : public WorldPositionObject
{
private:
	int textlabelId;
public:
	//Pickup(int model, int type, float x, float y, float z, std::string text, int interiorid, int sampinteriorid, int virtualworld);
	Pickup(int model, int type, float x, float y, float z, std::string text, Interior *interior);
	~Pickup();
	int destinationInterior;
	int destinationPickup;
	int model_;
	int type_;
	std::string text_;
	virtual void OnEnter();
	virtual void OnExit();
};

