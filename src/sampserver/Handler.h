#pragma once
#include <iostream>
#include <vector>
#include "GameUtility.h"
class Player;
class Handler
{
public:
	virtual bool OnCommand(Player *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)=0;
	virtual void CheckForHacks()=0;
	virtual void Load(GameUtility* gameUtility)=0;
};

