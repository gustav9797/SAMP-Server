#pragma once
#include <string>
#include <vector>

class CommandExecutor;
class GameUtility;

class Command
{
public:
	virtual std::vector<std::string> getAliases()=0;
	virtual void Execute(CommandExecutor *sender, std::vector<std::string> args, GameUtility *gameUtility)=0;
};