#pragma once
#include <string>

#include "Event.h"
#include "PlayerState.h"

class Player;

class EventPlayerCommandText : public Event
{
private:
	Player *player;
	std::string text;
public:
	EventPlayerCommandText(Player *player, std::string text)
		: Event("PlayerCommandText")
	{
		this->player = player;
		this->text = text;
	}
	EventPlayerCommandText() {};

	Player *getPlayer() { return player; }
	std::string getCommandText() { return text; }
};