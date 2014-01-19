#include "HouseHandler.h"
#include "Interior.h"
#include "MyPlayer.h"

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
			CreateHouse(destinationId, *x, *y, *z, gameUtility->interiorHandler->getInterior(GetPVarInt(player->GetId(), "currentinterior")), gameUtility->interiorHandler);
			delete x, y, z;			
		}
		return true;
	}
	return false;
}

void HouseHandler::CheckForHacks()
{
}

void HouseHandler::Load(GameUtility* gameUtility)
{
}

bool HouseHandler::CreateHouse(int destinationId, float x, float y, float z, Interior *interior, InteriorHandler* interiorHandler)
{
	int destinationId_ = interiorHandler->AddInterior(new Interior(*interiorHandler->getDefaultInterior(destinationId)));
	int pickup = interiorHandler->HandlerCreatePickup(1273, 1, x, y, z, "House", interior, destinationId_);
	House *house = new House();
	house->interiors->emplace(destinationId_, destinationId_);
	house->pickups->emplace(pickup, pickup);
	houses->emplace(destinationId_, house);
	return true; //temp
}
