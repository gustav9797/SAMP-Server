#include "CommandManager.h"

#include <sstream>
#include <sampgdk/core.h>

#include "Command.h"
#include "CommandExecutor.h"
#include "GameUtility.h"

CommandManager::CommandManager()
{
	commands = new std::map<std::string, Command*>();
}


CommandManager::~CommandManager()
{
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
