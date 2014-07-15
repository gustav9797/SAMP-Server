#pragma once
#include <string>

#include "Event.h"

class Player;
class Vehicle;

class EventPlayerBeginEnterVehicle : public Event
{
private:
	Player *player;
	Vehicle *vehicle;
public:
	EventPlayerBeginEnterVehicle(Player *player, Vehicle *vehicle)
		: Event("PlayerBeginEnterVehicle")
	{
		this->player = player;
		this->vehicle = vehicle;
	}
	EventPlayerBeginEnterVehicle() {};

	Player *getPlayer() { return player; }
	Vehicle *getVehicle() { return vehicle; }
};