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
	return frontLeft_.to_ulong() | (rearLeft_.to_ulong() << 1) | (frontRight_.to_ulong() << 2) |  (rearRight_.to_ulong() << 3);
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
		return frontLeft_.at(bit);
		break;
	case Tires::RearLeftTire:
		return rearLeft_.at(bit);
		break;
	case Tires::FrontRightTire:
		return frontRight_.at(bit);
		break;
	case Tires::RearRightTire:
		return rearRight_.at(bit);
		break;
	}
	return 0;
}

void TireStatus::setBit(int tire, int bit, bool value)
{
	switch (tire)
	{
	case Tires::FrontLeftTire:
		frontLeft_.set(bit, value);
		break;
	case Tires::RearLeftTire:
		rearLeft_.set(bit, value);
		break;
	case Tires::FrontRightTire:
		frontRight_.set(bit, value);
		break;
	case Tires::RearRightTire:
		rearRight_.set(bit, value);
		break;
	}
}

bool TireStatus::getTireDamaged(int tire)
{
	return getBit(tire, 0);
}

void TireStatus::setTireDamaged(int tire, bool value)
{
	setBit(tire, 0, value);
}
