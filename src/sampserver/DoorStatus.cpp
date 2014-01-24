#include "DoorStatus.h"


DoorStatus::DoorStatus(int doors)
{
	Decode(doors);
}


DoorStatus::~DoorStatus(void)
{
}

int DoorStatus::Encode()
{
	return hood_.to_ulong() | (trunk_.to_ulong() << 8) | (drivers_door_.to_ulong() << 16) | (co_drivers_door_.to_ulong() << 24); 
}

void DoorStatus::Decode(int doors)
{
	co_drivers_door_ = doors >> 24;
	drivers_door_ = doors >> 16;
	trunk_ = doors >> 8;
	hood_ = doors;
}

bool DoorStatus::getBit(int door, int bit)
{
	switch (door)
	{
	case Doors::Hood:
		return hood_.at(bit);
		break;
	case Doors::Trunk:
		return trunk_.at(bit);
		break;
	case Doors::DriversDoor:
		return drivers_door_.at(bit);
		break;
	case Doors::CoDriversDoor:
		return co_drivers_door_.at(bit);
		break;
	}
	return 0;
}

void DoorStatus::setBit(int door, int bit, bool value)
{
	switch (door)
	{
	case Doors::Hood:
		hood_.set(bit, value);
		break;
	case Doors::Trunk:
		trunk_.set(bit, value);
		break;
	case Doors::DriversDoor:
		drivers_door_.set(bit, value);
		break;
	case Doors::CoDriversDoor:
		co_drivers_door_.set(bit, value);
		break;
	}
}

bool DoorStatus::getDoorOpened(int door)
{
	return getBit(door, 0);
}

void DoorStatus::setDoorOpened(int door, bool value)
{
	setBit(door, 0, value);
}

bool DoorStatus::getDoorDamaged(int door)
{
	return getBit(door, 1);
}

void DoorStatus::setDoorDamaged(int door, bool value)
{
	setBit(door, 1, value);
}

bool DoorStatus::getDoorRemoved(int door)
{
	return getBit(door, 2);
}

void DoorStatus::setDoorRemoved(int door, bool value)
{
	setBit(door, 2, value);
}

