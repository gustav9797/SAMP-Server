#pragma once
#include <map>
#include "Handler.h"
class Interior;
class WorldPositionObject;
class Pickup;

class InteriorHandler : public Handler
{
private:
	std::map<int, Interior*> *interiors;
	std::map<int, Interior*> *defaultInteriors;

	std::map<int, Pickup*> *pickups;
	std::map<int, int> *sampPickupIdToPickupId;
public:
	InteriorHandler(GameUtility *gameUtility);
	~InteriorHandler();
	virtual void Load();
	Interior* getInterior(int interiorId);
	Interior* getDefaultInterior(int interiorId);
	bool AddInterior(int interiorId, Interior *interior);
	int AddInterior(Interior *interior);
	bool RemoveInterior(int interiorId);
	int SampinterioridToInterior(int sampinteriorid, float x, float y, float z, int virtualworld);
	bool addInteriorExitLocation(int interiorid, WorldPositionObject location, WorldPositionObject destination);
	bool removeInteriorExitLocation(int interiorid, WorldPositionObject location);

	Pickup* getPickup(int pickupId);
	int HandlerCreatePickup(int model, int type, float x, float y, float z, std::string text, Interior *interior, int destinationInterior = -1, int destinationPickup = -1);
	bool HandlerDestroyPickup(int pickupId);
	int getFreePickupId();
};

