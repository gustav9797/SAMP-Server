#include "GameUtility.h"

#include "Handler.h"
#include "PlayerHandler.h"
#include "InteriorHandler.h"
#include "HouseHandler.h"
#include "WeaponHandler.h"
#include "VehicleHandler.h"
#include "ObjectHandler.h"

#include "WorldPositionObject.h"
#include "Interior.h"
#include "Player.h"

GameUtility::GameUtility(void)
{
	handlers = new std::vector<Handler*>();
}


GameUtility::~GameUtility(void)
{
}

bool GameUtility::OnCommand(Player *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	bool temp = false;
	for(auto i : *handlers)
	{
		if(i->OnCommand(player, cmd, args, gameUtility))
			temp = true;
	}
	return temp;
}

void GameUtility::CheckForHacks()
{
	for(auto i : *handlers)
	{
		i->CheckForHacks();
	}
}

void GameUtility::Load(GameUtility* gameUtility)
{
	for(auto i : *handlers)
	{
		i->Load(gameUtility);
	}
}

void GameUtility::AddHandler(Handler *handler)
{
	handlers->push_back(handler);
}

bool GameUtility::IsPlayerClose(Player *player, WorldPositionObject object, float range)
{
	int playerInterior = GetPVarInt(player->getId(), "currentinterior");
	if(playerInterior == object.interiorId_)
	{
		return IsPlayerInRangeOfPoint(player->getId(), range, object.x_, object.y_, object.z_);
	}
}

bool GameUtility::IsPlayerClose(Player *player, float x, float y, float z, Interior *interior, float range)
{
	int playerInterior = GetPVarInt(player->getId(), "currentinterior");
	if(playerInterior == interior->interiorId_)
	{
		return IsPlayerInRangeOfPoint(player->getId(), range, x, y, z);
	}
}
