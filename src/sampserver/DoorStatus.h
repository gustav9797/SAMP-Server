#pragma once
#include "DamageStatus.h"
#include <bitset>

class DoorStatus : public DamageStatus
{
private:
	std::bitset<8> hood_;
	std::bitset<8> trunk_;
	std::bitset<8> drivers_door_;
	std::bitset<8> co_drivers_door_;
	virtual bool getBit(int door, int bit);
	virtual void setBit(int door, int bit, bool value);
public:
	DoorStatus(int doors);
	~DoorStatus(void);
	bool getDoorOpened(int door);
	void setDoorOpened(int door, bool value);
	bool getDoorDamaged(int door);
	void setDoorDamaged(int door, bool value);
	bool getDoorRemoved(int door);
	void setDoorRemoved(int door, bool value);
	virtual int Encode();
	virtual void Decode(int doors);
};

enum Doors
{
	Hood=0,
	Trunk,
	DriversDoor,
	CoDriversDoor
};
