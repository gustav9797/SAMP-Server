#pragma once
#include "Handler.h"
#include <map>
class Interior;
class WorldPositionObject;

class InteriorHandler : public Handler
{
private:
	std::map<int, Interior*> *interiors;
	std::map<int, Interior*> *defaultInteriors;
public:
	InteriorHandler();
	~InteriorHandler();
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load();
	Interior* getInterior(int interiorId);
	Interior* getDefaultInterior(int interiorId);
	bool AddInterior(int interiorId, Interior *interior);
	int AddInterior(Interior *interior);
	bool RemoveInterior(int interiorId);
	int SampinterioridToInterior(int sampinteriorid, float x, float y, float z, int virtualworld);
	bool addInteriorExitLocation(int interiorid, WorldPositionObject location, WorldPositionObject destination);
	bool removeInteriorExitLocation(int interiorid, WorldPositionObject location);
};

