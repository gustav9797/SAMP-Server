#pragma once
#include <map>
#include <vector>
#include <sampgdk\a_objects.h>
#include "Handler.h"
class MyObject;
class ObjectHandler: public Handler
{
private:
	std::map<int, MyObject*> *objects;
public:
	ObjectHandler(void);
	~ObjectHandler(void);
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	MyObject *CreateObject(int model, float x, float y, float z, float rx, float ry, float rz, float drawDistance);
	void RemoveObject(int id);
	std::vector<MyObject*> *getCloseObjects(float x, float y, float z, float maxDistance);
};

