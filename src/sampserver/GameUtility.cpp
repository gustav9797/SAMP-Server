#include "GameUtility.h"
#include "PlayerHandler.h"
#include "InteriorHandler.h"
#include "HouseHandler.h"
#include "WeaponHandler.h"
#include "VehicleHandler.h"
#include "ObjectHandler.h"

GameUtility::GameUtility(void)
{
}


GameUtility::~GameUtility(void)
{
}

void GameUtility::Load()
{
	interiorHandler->Load(this);
	objectHandler->Load(this);
	houseHandler->Load(this);
	weaponHandler->Load(this);
	vehicleHandler->Load(this);
	playerHandler->Load(this);
}
