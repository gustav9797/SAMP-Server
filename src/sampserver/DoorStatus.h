#pragma once
class DoorStatus
{
private:
	char hood_;
	char trunk_;
	char drivers_door_;
	char co_drivers_door_;
	bool getBit(int door, int bit);
public:
	DoorStatus(int doors);
	~DoorStatus(void);
	int getRaw() { return Encode(); };
	bool getDoorOpened(int door);
	bool getDoorDamaged(int door);
	bool getDoorRemoved(int door);
	int Encode();
	void Decode(int doors);
};

enum Doors
{
	Hood=0,
	Trunk,
	DriversDoor,
	CoDriversDoor
};
