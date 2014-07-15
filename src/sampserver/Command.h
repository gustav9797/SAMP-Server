#pragma once
#include <string>
#include <vector>

class CommandExecutor;
class GameUtility;

class Command
{
private:
	GameUtility *gameUtility;
public:
	Command(GameUtility *gameUtility){ this->gameUtility = gameUtility; }
	virtual std::vector<std::string> getAliases() = 0;
	virtual void Execute(CommandExecutor *sender, std::vector<std::string> args) = 0;
};