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
	int model_;
	Interior *interior_;
	float x_;
	float y_;
	float z_;
	float rx_;
	float ry_;
	float rz_;
	float drawDistance_;
	std::map<int, int> *playerObjectsOwned;
public:
	MyObject(int id, int model, Interior *interior, float x, float y, float z, float rx, float ry, float rz, float drawDistance);
	~MyObject(void);
	int getModel() { return model_; };
	Interior *getInterior() { return  interior_; };
	int getId() { return id_; };
	float getX() { return x_; };
	float getY() { return y_; };
	float getZ() { return z_; };
	float getRotX() { return rx_; };
	float getRotY() { return ry_; };
	float getRotZ() { return rz_; };
	float getDrawDistance() { return drawDistance_; };
	bool HasObject(int objectId);
	bool HasPlayerObject(int player);
	void AddPlayerObject(int player, int objectId);
	void RemovePlayerObject(int player);
	void RemoveAll();
	void UpdatePosition(bool offset, float xo, float yo, float zo, float rx, float ry, float rz);
	void Save();
};

