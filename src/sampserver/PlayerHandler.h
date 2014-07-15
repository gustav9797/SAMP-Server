#pragma once
#include <iostream>
#include <map>
#include "Player.h"
#include "Handler.h"
class WorldPositionObject;
class PlayerHandler : public Handler
{
public:
	PlayerHandler(GameUtility *gameUtility);
	~PlayerHandler();
	virtual void Load();
	bool KickPlayer(int playerid, std::string message, GameUtility* gameUtility);
	static void SAMPGDK_CALL KickDelayed(int, void * playerId);
	void TeleportPlayer(int playerid, WorldPositionObject pos);
	std::map<int, Player*> *players;
};

