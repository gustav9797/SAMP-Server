#include "GameUtility.h"
#include "PlayerHandler.h"
#include "InteriorHandler.h"
#include "HouseHandler.h"
#include "WeaponHandler.h"
#include "VehicleHandler.h"
#include "ObjectHandler.h"

#include "WorldPositionObject.h"
#include "Interior.h"
#include "MyPlayer.h"

GameUtility::GameUtility(void)
{
}


GameUtility::~GameUtility(void)
{
}

void GameUtility::Load()
{
	interiorHandler->Load(this);
	houseHandler->Load(this);
	weaponHandler->Load(this);
	vehicleHandler->Load(this);
	playerHandler->Load(this);
	objectHandler->Load(this);
}

bool GameUtility::IsPlayerClose(MyPlayer *player, WorldPositionObject object, float range)
{
	int playerInterior = GetPVarInt(player->GetId(), "currentinterior");
	if(playerInterior == object.interiorId_)
	{
		return IsPlayerInRangeOfPoint(player->GetId(), range, object.x_, object.y_, object.z_);
	}
}

bool GameUtility::IsPlayerClose(MyPlayer *player, float x, float y, float z, Interior *interior, float range)
{
	int playerInterior = GetPVarInt(player->GetId(), "currentinterior");
	if(playerInterior == interior->interiorId_)
	{
		return IsPlayerInRangeOfPoint(player->GetId(), range, x, y, z);
	}
}
