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
	return frontLeft_ | (rearLeft_ << 1) | (frontRight_ << 2) |  (rearRight_ << 3);
}

void LightStatus::Decode(int raw)
{
	rearRight_ = raw >> 3;
	rearLeft_ = raw >> 2;
	frontRight_ = raw >> 1;
	frontLeft_ = raw;
}

bool LightStatus::getBit(int light, int bit)
{
	switch (light)
	{
	case Lights::FrontLeftLight:
		return (frontLeft_ & (1 << bit-1)) != 0;
		break;
	case Lights::RearLeftLight:
		return (rearLeft_ & (1 << bit-1)) != 0;
		break;
	case Lights::FrontRightLight:
		return (frontRight_ & (1 << bit-1)) != 0;
		break;
	case Lights::RearRightLight:
		return (rearRight_ & (1 << bit-1)) != 0;
		break;
	}
	return 0;
}

void LightStatus::setBit(int light, int bit, bool value)
{
	if(value)
	{
		switch (light)
		{
		case Lights::FrontLeftLight:
			frontLeft_ |= (1 << bit-1);
			break;
		case Lights::RearLeftLight:
			rearLeft_ |= (1 << bit-1);
			break;
		case Lights::FrontRightLight:
			frontRight_ |= (1 << bit-1);
			break;
		case Lights::RearRightLight:
			rearRight_ |= (1 << bit-1);
			break;
		}
	}
	else
	{
		switch (light)
		{
		case Lights::FrontLeftLight:
			frontLeft_ &= ~(1 << bit-1);
			break;
		case Lights::RearLeftLight:
			rearLeft_ &= ~(1 << bit-1);
			break;
		case Lights::FrontRightLight:
			frontRight_ &= ~(1 << bit-1);
			break;
		case Lights::RearRightLight:
			rearRight_ &= ~(1 << bit-1);
			break;
		}
	}
}

bool LightStatus::getLightDamaged(int light)
{
	return getBit(light, 1);
}

void LightStatus::setLightDamaged(int light, bool value)
{
	setBit(light, 1, value);
}
