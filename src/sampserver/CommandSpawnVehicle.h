#include "Command.h"

#include <iostream>

class CommandSpawnVehicle : public Command
{
public:
	CommandSpawnVehicle(GameUtility *gameUtility) : Command(gameUtility) {};

	virtual std::vector<std::string> getAliases()
	{
		std::vector<std::string> aliases = std::vector<std::string>();
		aliases.push_back("v");
		aliases.push_back("createvehicle");
		return aliases;
	}

	virtual void Execute(CommandExecutor *sender, std::vector<std::string> args)
	{
		std::cout << " BOOM baby!";
	}
};