#include "Pickup.h"


Pickup::Pickup(int model, int type, float x, float y, float z, std::string text, Interior *interior)
	: WorldPositionObject(x, y, z, interior)
{
	destinationInterior = -1;
	destinationPickup = -1;

	model_ = model;
	type_ = type; 
	text_ = text; 

	if(!text.empty())
	{
		textlabelId = Create3DTextLabel(text.c_str(), 0x008080FF, x, y, z, 3, virtualWorld_, 1);
	}
}


Pickup::~Pickup()
{
	Delete3DTextLabel(textlabelId);
}

void Pickup::OnEnter()
{
}

void Pickup::OnExit()
{
}