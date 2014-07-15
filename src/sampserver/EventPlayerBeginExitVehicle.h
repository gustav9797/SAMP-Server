#pragma once
#include <string>

#include "Event.h"

class Player;
class Vehicle;

class EventPlayerBeginExitVehicle : public Event
{
private:
	Player *player;
	Vehicle *vehicle;
public:
	EventPlayerBeginExitVehicle(Player *player, Vehicle *vehicle)
		: Event("PlayerBeginExitVehicle")
	{
		this->player = player;
		this->vehicle = vehicle;
	}
	EventPlayerBeginExitVehicle() {};

	Player *getPlayer() { return player; }
	Vehicle *getVehicle() { return vehicle; }
};