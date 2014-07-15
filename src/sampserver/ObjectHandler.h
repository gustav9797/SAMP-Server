#pragma once
#include <map>
#include <vector>
#include <sampgdk\a_objects.h>
#include "Handler.h"
class Object;
class Interior;
class ObjectHandler: public Handler
{
private:
	std::map<int, Object*> *objects;
public:
	ObjectHandler(void);
	~ObjectHandler(void);
	virtual bool OnCommand(Player *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	Object *CreateObject(int model, Player* player, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance);
	void RemoveObject(int id);
	std::vector<Object*> *getCloseObjects(float x, float y, float z, float maxDistance);
	int getFreeObjectId();
	Object *getObject(int objectId);
	void Update(GameUtility *gameUtility);
	bool OnPlayerSelectObject(Player *player, int type, int objectSampId, int model, float x, float y, float z);
	bool OnPlayerEditObject(Player *player, int type, int objectSampId, int response, float xo, float yo, float zo, float xr, float yr, float zr);
	bool OnPlayerObjectMoved(Player *player, int objectSampId);
};

