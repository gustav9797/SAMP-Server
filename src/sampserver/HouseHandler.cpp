#include "HouseHandler.h"
#include "Interior.h"

HouseHandler::HouseHandler(void)
{
	houses = new std::map<int, House*>();
}


HouseHandler::~HouseHandler(void)
{
}

bool HouseHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	if (cmd == "createhouse")
	{
		if (args.size() >= 1)
		{
			int destinationId = atoi(args[0].c_str());
			float *x = new float(), *y = new float(), *z = new float();
			GetPlayerPos(player->GetId(), x, y, z);
			CreateHouse(destinationId, *x, *y, *z, GetPVarInt(player->GetId(), "currentinterior"), GetPlayerInterior(player->GetId()), GetPlayerVirtualWorld(player->GetId()), gameUtility->interiorHandler, gameUtility->pickupHandler);
			delete x, y, z;			
		}
		return true;
	}
	return false;
}

void HouseHandler::CheckForHacks()
{
}

void HouseHandler::Load()
{
}

bool HouseHandler::CreateHouse(int destinationId, float x, float y, float z, int interior, int sampinterior, int virtualworld, InteriorHandler* interiorHandler, PickupHandler *pickupHandler)
{
	int destinationId_ = interiorHandler->AddInterior(new Interior(*interiorHandler->getDefaultInterior(destinationId)));
	int pickup = pickupHandler->HandlerCreatePickup(1273, 1, x, y, z, "House", interior, sampinterior, virtualworld, destinationId_);
	House *house = new House();
	house->interiors->emplace(destinationId_, destinationId_);
	house->pickups->emplace(pickup, pickup);
	houses->emplace(destinationId_, house);
	return true; //temp
}
