#pragma once
#include <map>
#include <vector>
#include <string>

#include "EventHandler.h"

class Command;
class CommandExecutor;
class GameUtility;

class CommandManager
{
private:
	std::map<std::string, Command*> *commands;
	static std::string getCommand(std::string input);
	static std::vector<std::string> getParams(std::string input);
public:
	CommandManager();
	~CommandManager();
	bool RegisterCommand(Command *cmd);
	void UnRegisterCommand(Command *cmd);
};

