#include "TireStatus.h"

TireStatus::TireStatus(int tires)
{
	Decode(tires);
}


TireStatus::~TireStatus(void)
{
}

int TireStatus::Encode()
{
	return frontLeft_ | (rearLeft_ << 1) | (frontRight_ << 2) |  (rearRight_ << 3);
}

void TireStatus::Decode(int raw)
{
	rearRight_ = raw >> 3;
	rearLeft_ = raw >> 2;
	frontRight_ = raw >> 1;
	frontLeft_ = raw;
}

bool TireStatus::getBit(int tire, int bit)
{
	switch (tire)
	{
	case Tires::FrontLeftTire:
		return (frontLeft_ & (1 << bit-1)) != 0;
		break;
	case Tires::RearLeftTire:
		return (rearLeft_ & (1 << bit-1)) != 0;
		break;
	case Tires::FrontRightTire:
		return (frontRight_ & (1 << bit-1)) != 0;
		break;
	case Tires::RearRightTire:
		return (rearRight_ & (1 << bit-1)) != 0;
		break;
	}
	return 0;
}

void TireStatus::setBit(int tire, int bit, bool value)
{
	if(value)
	{
		switch (tire)
		{
		case Tires::FrontLeftTire:
			frontLeft_ |= (1 << bit-1);
			break;
		case Tires::RearLeftTire:
			rearLeft_ |= (1 << bit-1);
			break;
		case Tires::FrontRightTire:
			frontRight_ |= (1 << bit-1);
			break;
		case Tires::RearRightTire:
			rearRight_ |= (1 << bit-1);
			break;
		}
	}
	else
	{
		switch (tire)
		{
		case Tires::FrontLeftTire:
			frontLeft_ &= ~(1 << bit-1);
			break;
		case Tires::RearLeftTire:
			rearLeft_ &= ~(1 << bit-1);
			break;
		case Tires::FrontRightTire:
			frontRight_ &= ~(1 << bit-1);
			break;
		case Tires::RearRightTire:
			rearRight_ &= ~(1 << bit-1);
			break;
		}
	}
}

bool TireStatus::getTireDamaged(int tire)
{
	return getBit(tire, 1);
}

void TireStatus::setTireDamaged(int tire, bool value)
{
	setBit(tire, 1, value);
}
