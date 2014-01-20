#pragma once
#include <sampgdk\a_vehicles.h>
#include "DoorStatus.h"
#include "PanelStatus.h"
class VehicleDamageStatus
{
private:
	float health_;
	PanelStatus *panels_;
	DoorStatus *doors_;
	int lights_;
	int tires_;
public:
	VehicleDamageStatus(float health, int panels, int doors, int lights, int tires);
	~VehicleDamageStatus(void);
	void UpdateStatus(float health, int panels, int doors, int lights, int tires);
	float getHealth() { return health_; }
	int getPanelsRaw() { return panels_->getRaw(); }
	PanelStatus *getPanels() { return panels_; }
	int getDoorsRaw() { return doors_->getRaw(); }
	DoorStatus *getDoors() { return doors_; }
	int getLightsRaw() { return lights_; }
	int getTiresRaw() { return tires_; }

	int EncodeTires(int tire1, int tire2, int tire3, int tire4) 
	{
		return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
	}
	int EncodeLights(int light1, int light2, int light3, int light4)
	{
		return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
	} 
};

