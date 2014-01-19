#pragma once
#include <sampgdk\a_objects.h>
#include <sampgdk\a_players.h>
#include <map>
class Interior;
class MyPlayer;
class MyObject
{
private:
	int id_;
	//int sampId_;
	int model_;
	//int player_;
	Interior *interior_;
	float x_;
	float y_;
	float z_;
	float rx_;
	float ry_;
	float rz_;
	float drawDistance_;
	//PlayerObject mainObject_;
	std::map<int, int> *playerObjectsOwned;
public:
	MyObject(int id, int model, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance);
	//MyObject(int id, PlayerObject object, int model, Interior *interior, float drawDistance);
	~MyObject(void);
	int getId() { return id_; };
	//int getSampId() { return mainObject_.GetObjectId(); };
	bool hasObject(int objectId);
	bool hasPlayerObject(int player);
	void addPlayerObject(int player, int objectId);
	void removePlayerObject(int player);
	void UpdatePosition(bool offset, float xo, float yo, float zo, float rx, float ry, float rz);
	void Save();
	int getModel() { return model_; };
	Interior *getInterior() { return  interior_; };
	float getX() { return x_; };
	float getY() { return y_; };
	float getZ() { return z_; };
	float getRotX() { return rx_; };
	float getRotY() { return ry_; };
	float getRotZ() { return rz_; };
	float getDrawDistance() { return drawDistance_; };
};

