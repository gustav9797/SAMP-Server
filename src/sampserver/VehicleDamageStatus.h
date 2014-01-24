#pragma once
#include <sampgdk\a_vehicles.h>
#include "DoorStatus.h"
#include "PanelStatus.h"
#include "LightStatus.h"
#include "TireStatus.h"

class VehicleDamageStatus
{
private:
	float health_;
	PanelStatus *panels_;
	DoorStatus *doors_;
	LightStatus *lights_;
	TireStatus *tires_;
public:
	VehicleDamageStatus(float health, int panels, int doors, int lights, int tires);
	~VehicleDamageStatus(void);
	void UpdateStatus(float health, int panels, int doors, int lights, int tires);
	float getHealth() { return health_; }

	int getPanelsRaw() { return panels_->getRaw(); }
	PanelStatus *getPanels() { return panels_; }

	int getDoorsRaw() { return doors_->getRaw(); }
	DoorStatus *getDoors() { return doors_; }

	int getLightsRaw() { return lights_->getRaw(); }
	LightStatus *getLights() { return lights_; }

	int getTiresRaw() { return tires_->getRaw();; }
	TireStatus *getTires() { return tires_; }
};

