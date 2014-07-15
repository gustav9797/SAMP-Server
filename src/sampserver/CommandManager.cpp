#include "CommandManager.h"

#include <sstream>
#include <sampgdk/core.h>

#include "Command.h"
#include "CommandExecutor.h"
#include "GameUtility.h"
#include "EventPlayerCommandText.h"
#include "Event.h"
#include "EventHandler.h"
#include "HouseHandler.h"

#include "CommandSpawnVehicle.h"

CommandManager::CommandManager(GameUtility *gameUtility)
: Handler(gameUtility)
{
	commands = new std::map<std::string, Command*>();
}


CommandManager::~CommandManager()
{
}

void CommandManager::Load()
{
	using namespace std::placeholders;
	std::function<void(Event*)> f(std::bind(&CommandManager::OnPlayerCommandText, this, _1));
	gameUtility->eventHandler->RegisterHandler<EventPlayerCommandText>(f);

	RegisterCommand(new CommandSpawnVehicle(gameUtility));
}

bool CommandManager::RegisterCommand(Command *cmd)
{
	if (cmd)
	{
		for (std::string alias : cmd->getAliases())
		{
			if (commands->find(alias) == commands->end())
				commands->emplace(alias, cmd);
		}
		return true;
	}
	return false;
}

void CommandManager::UnRegisterCommand(Command *cmd)
{
	if (cmd)
	{
		for (std::string alias : cmd->getAliases())
		{
			if (commands->find(alias) != commands->end())
				commands->erase(alias);
		}
	}
}

std::string CommandManager::getCommand(std::string input)
{
	std::vector<std::string> tokens;
	std::istringstream iss(input);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(tokens));
	return tokens.at(0);
}

std::vector<std::string> CommandManager::getParams(std::string input)
{
	std::vector<std::string> tokens;
	std::istringstream iss(input);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(tokens));
	if (tokens.size() >= 1)
		tokens.erase(tokens.begin());
	return tokens;
}

void CommandManager::OnPlayerCommandText(Event *ev)
{
	EventPlayerCommandText *eve = static_cast<EventPlayerCommandText*>(ev);
	std::string cmd = getCommand(eve->getCommandText());
	std::vector<std::string> args = getParams(eve->getCommandText());
	Player *player = eve->getPlayer();

	if (commands->find(cmd) != commands->end())
	{
		Command *command = commands->at(cmd);
		//TODO: Check if player has perms
		command->Execute((CommandExecutor*)player, args);
	}
}
