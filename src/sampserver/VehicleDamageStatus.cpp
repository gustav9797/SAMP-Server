#include "VehicleDamageStatus.h"

VehicleDamageStatus::VehicleDamageStatus(float health, int panels, int doors, int lights, int tires)
{
	UpdateStatus(health, panels, doors, lights, tires);
}


VehicleDamageStatus::~VehicleDamageStatus(void)
{
}

void VehicleDamageStatus::UpdateStatus(float health, int panels, int doors, int lights, int tires)
{
	health_ = health;
	if(doors_ != nullptr)
		delete doors_;
	doors_ = new DoorStatus(doors);
	if(panels_ != nullptr)
		delete panels_;

	//////////////////////////////////////////////////////////////////LIGHTS AND TIRES NOT HANDLED YET
	panels_ = new PanelStatus(panels);
}
