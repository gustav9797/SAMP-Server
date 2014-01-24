#include "VehicleDamageStatus.h"

VehicleDamageStatus::VehicleDamageStatus(float health, int panels, int doors, int lights, int tires)
{
	health_ = health;
	panels_ = new PanelStatus(panels);
	doors_ = new DoorStatus(doors);
	lights_ = new LightStatus(lights);
	tires_ = new TireStatus(tires);
}


VehicleDamageStatus::~VehicleDamageStatus(void)
{
}

void VehicleDamageStatus::UpdateStatus(float health, int panels, int doors, int lights, int tires)
{
	health_ = health;
	panels_->Update(panels);
	doors_->Update(doors);
	lights_->Update(lights);
	tires_->Update(tires);
}
