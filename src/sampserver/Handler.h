#pragma once
#include <iostream>
#include <vector>
#include "GameUtility.h"
class MyPlayer;
class Handler
{
public:
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)=0;
	virtual void CheckForHacks()=0;
	virtual void Load()=0;
};

