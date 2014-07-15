#pragma once
#include <string>

#include "Event.h"
#include "PlayerState.h"

class Player;
class Vehicle;

class EventPlayerStateChange : public Event
{
private:
	Player *player;
	PlayerState newState;
	PlayerState oldState;
public:
	EventPlayerStateChange(Player *player, PlayerState newState, PlayerState oldState)
		: Event("PlayerStateChange")
	{
		this->player = player;
		this->newState = newState;
		this->oldState = oldState;
	}
	EventPlayerStateChange() {};

	Player *getPlayer() { return player; }
	PlayerState getNewState() { return newState; }
	PlayerState getOldState() { return oldState; }
};