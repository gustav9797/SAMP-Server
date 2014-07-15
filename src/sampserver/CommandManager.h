#pragma once
#include <map>
#include <vector>
#include <string>

#include "EventHandler.h"
#include "Handler.h"

class Command;
class CommandExecutor;
class GameUtility;
class EventPlayerCommandText;

class CommandManager : public Handler
{
private:
	std::map<std::string, Command*> *commands;
	static std::string getCommand(std::string input);
	static std::vector<std::string> getParams(std::string input);
public:
	CommandManager(GameUtility *gameUtility);
	~CommandManager();
	bool RegisterCommand(Command *cmd);
	void UnRegisterCommand(Command *cmd);
	void OnPlayerCommandText(Event *ev);

	virtual void Load();

};

