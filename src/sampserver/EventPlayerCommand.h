#pragma once
#include <string>
#include <vector>

#include "Event.h"
#include "PlayerState.h"

class Player;

class EventPlayerCommand : public Event
{
private:
	Player *player;
	std::string cmd;
	std::vector<std::string> args;
public:
	EventPlayerCommand(Player *player, std::string cmd, std::vector<std::string> args)
		: Event("PlayerCommand")
	{
		this->player = player;
		this->cmd = cmd;
		this->args = args;
	}
	EventPlayerCommand() {};

	Player *getPlayer() { return player; }
	std::string getCmd() { return cmd; }
	std::vector<std::string> getArgs() { return args; }
};