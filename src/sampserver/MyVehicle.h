#pragma once
#include <sampgdk/a_vehicles.h>
class MyVehicle : public Vehicle
{
public:
	MyVehicle(int id, int model, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, std::string licensePlate);
	MyVehicle(Vehicle vehicle, int color1, int color2, int respawnDelay, std::string licensePlate);
	~MyVehicle();
	int id_;
	int model_;
	float x_;
	float y_;
	float z_;
	float rotation_;
	int color1_;
	int color2_;
	int respawnDelay_;
	int getId() { return id_; };
	std::string licensePlate_;
};

