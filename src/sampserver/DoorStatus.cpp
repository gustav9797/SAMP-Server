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
	return hood_ | (trunk_ << 8) | (drivers_door_ << 16) | (co_drivers_door_ << 24); 
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
		return (hood_ & (1 << bit-1)) != 0;
		break;
	case Doors::Trunk:
		return (trunk_ & (1 << bit-1)) != 0;
		break;
	case Doors::DriversDoor:
		return (drivers_door_& (1 << bit-1)) != 0;
		break;
	case Doors::CoDriversDoor:
		return (co_drivers_door_ & (1 << bit-1)) != 0;
		break;
	}
	return 0;
}

void DoorStatus::setBit(int door, int bit, bool value)
{
	if(value)
	{
		switch (door)
		{
		case Doors::Hood:
			hood_ |= (1 << bit-1);
			break;
		case Doors::Trunk:
			trunk_ |= (1 << bit-1);
			break;
		case Doors::DriversDoor:
			drivers_door_ |= (1 << bit-1);
			break;
		case Doors::CoDriversDoor:
			co_drivers_door_ |= (1 << bit-1);
			break;
		}
	}
	else
	{
		switch (door)
		{
		case Doors::Hood:
			hood_ &= (value << bit-1);
			break;
		case Doors::Trunk:
			trunk_ &= (1 << bit-1);
			break;
		case Doors::DriversDoor:
			drivers_door_ &= (1 << bit-1);
			break;
		case Doors::CoDriversDoor:
			co_drivers_door_ &= (1 << bit-1);
			break;
		}
	}
}

bool DoorStatus::getDoorOpened(int door)
{
	return getBit(door, 1);
}

void DoorStatus::setDoorOpened(int door, bool value)
{
	setBit(door, 1, value);
}

bool DoorStatus::getDoorDamaged(int door)
{
	return getBit(door, 2);
}

void DoorStatus::setDoorDamaged(int door, bool value)
{
	setBit(door, 2, value);
}

bool DoorStatus::getDoorRemoved(int door)
{
	return getBit(door, 3);
}

void DoorStatus::setDoorRemoved(int door, bool value)
{
	setBit(door, 3, value);
}

