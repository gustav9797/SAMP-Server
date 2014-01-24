#include "LightStatus.h"

LightStatus::LightStatus(int lights)
{
	Decode(lights);
}


LightStatus::~LightStatus(void)
{
}

int LightStatus::Encode()
{
	return frontLeft_.to_ulong() | (rearLeft_.to_ulong() << 1) | (frontRight_.to_ulong() << 2) |  (rearRight_.to_ulong() << 3);
}

void LightStatus::Decode(int raw)
{
	rearRight_ = raw >> 3;
	frontRight_ = raw >> 2;
	rearLeft_ = raw >> 1;
	frontLeft_ = raw;
}

bool LightStatus::getBit(int light, int bit)
{
	switch (light)
	{
	case Lights::FrontLeftLight:
		return frontLeft_.at(bit);
		break;
	case Lights::RearLeftLight:
		return rearLeft_.at(bit);
		break;
	case Lights::FrontRightLight:
		return frontRight_.at(bit);
		break;
	case Lights::RearRightLight:
		return rearRight_.at(bit);
		break;
	}
	return 0;
}

void LightStatus::setBit(int light, int bit, bool value)
{
	switch (light)
	{
	case Lights::FrontLeftLight:
		frontLeft_.set(bit, value);
		break;
	case Lights::RearLeftLight:
		rearLeft_.set(bit, value);
		break;
	case Lights::FrontRightLight:
		frontRight_.set(bit, value);
		break;
	case Lights::RearRightLight:
		rearRight_.set(bit, value);
		break;
	}
}

bool LightStatus::getLightDamaged(int light)
{
	return getBit(light, 0);
}

void LightStatus::setLightDamaged(int light, bool value)
{
	setBit(light, 0, value);
}
