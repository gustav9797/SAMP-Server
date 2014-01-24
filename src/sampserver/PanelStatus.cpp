#include "PanelStatus.h"
#include <sstream>

PanelStatus::PanelStatus(int panels)
{
	Decode(panels);
}


PanelStatus::~PanelStatus(void)
{
}

int PanelStatus::Encode()
{
	return frontLeft_.to_ulong() | 
		(frontRight_.to_ulong() << 4) | 
		(rearLeft_.to_ulong() << 8) | 
		(rearRight_.to_ulong() << 12) | 
		(windShield_.to_ulong() << 16) | 
		(frontBumper_.to_ulong() << 20) | 
		(rearBumper_.to_ulong() << 24);
}

void PanelStatus::Decode(int panels)
{
	rearBumper_ = panels >> 24;
	frontBumper_ = panels >> 20;
	windShield_ = panels >> 16;
	rearRight_ = panels >> 12;
	rearLeft_ = panels >> 8;
	frontRight_ = panels >> 4;
	frontLeft_ = panels;
}

bool PanelStatus::getBit(int panel, int bit)
{
	switch (panel)
	{
	case Panels::FrontLeft:
		return frontLeft_.at(bit);
		break;
	case Panels::FrontRight:
		return frontRight_.at(bit);
		break;
	case Panels::RearLeft:
		return rearLeft_.at(bit);
		break;
	case Panels::RearRight:
		return rearRight_.at(bit);
		break;
	case Panels::WindShield:
		return windShield_.at(bit);
		break;
	case Panels::FrontBumper:
		return frontBumper_.at(bit);
		break;
	case Panels::RearBumper:
		return rearBumper_.at(bit);
		break;
	}
	return 0;
}

void PanelStatus::setBit(int panel, int bit, bool value)
{
	switch (panel)
	{
	case Panels::FrontLeft:
		frontLeft_.set(bit, value);
		break;
	case Panels::FrontRight:
		frontRight_.set(bit, value);
		break;
	case Panels::RearLeft:
		rearLeft_.set(bit, value);
		break;
	case Panels::RearRight:
		rearRight_.set(bit, value);
		break;
	case Panels::WindShield:
		windShield_.set(bit, value);
		break;
	case Panels::FrontBumper:
		frontBumper_.set(bit, value);
		break;
	case Panels::RearBumper:
		rearBumper_.set(bit, value);
		break;
	}
}

bool PanelStatus::getPanelDamaged(int panel)
{
	return getBit(panel, 0);
}

void PanelStatus::setPanelDamaged(int panel, bool value)
{
	setBit(panel, 0, value);
}

bool PanelStatus::getPanelRemoved(int panel)
{
	return getBit(panel, 1);
}

void PanelStatus::setPanelRemoved(int panel, bool value)
{
	setBit(panel, 1, value);
}