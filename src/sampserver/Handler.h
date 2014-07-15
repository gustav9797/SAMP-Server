#pragma once
#include <iostream>
#include <vector>
#include "GameUtility.h"
class Player;
class Handler
{
protected:
	GameUtility *gameUtility;
public:
	Handler(GameUtility *gameUtility) { this->gameUtility = gameUtility; }
	virtual void Load()=0;
};

