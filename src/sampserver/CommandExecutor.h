#pragma once
#include <string>

class CommandExecutor
{
public:
	virtual void SendMessage(std::string msg) = 0;
};