#pragma once
#include <map>
#include <vector>
#include <sampgdk\a_objects.h>
#include "Handler.h"
class MyObject;
class Interior;
class ObjectHandler: public Handler
{
private:
	//std::map<int, PlayerObject> *streamedObjects;
	std::map<int, MyObject*> *objects;
	//std::map<int, int> *sampObjectIdToId;
public:
	ObjectHandler(void);
	~ObjectHandler(void);
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	MyObject *CreateObject(int model, MyPlayer* player, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance);
	void RemoveObject(int id);
	std::vector<MyObject*> *getCloseObjects(float x, float y, float z, float maxDistance);
	int getFreeObjectId();
	MyObject *getObject(int objectId);

	void Update(GameUtility *gameUtility);
	bool OnPlayerSelectObject(MyPlayer *player, int type, int objectSampId, int model, float x, float y, float z);
	bool OnPlayerEditObject(MyPlayer *player, int type, int objectSampId, int response, float xo, float yo, float zo, float xr, float yr, float zr);
	bool OnPlayerObjectMoved(MyPlayer *player, int objectSampId);
};

