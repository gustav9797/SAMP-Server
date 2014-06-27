#pragma once
#include <iostream>

#include "CommandExecutor.h"

class Console : CommandExecutor
{
public:
	inline void SendMessage(std::string msg) { std::cout << msg; };
};