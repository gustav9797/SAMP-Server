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
	return frontLeft_ | (frontRight_ << 4) | (rearLeft_ << 8) | (rearRight_ << 12) | (windShield_ << 16) | (frontBumper_ << 20) | (rearBumper_ << 24);
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
		return (frontLeft_ & (1 << bit-1)) != 0;
		break;
	case Panels::FrontRight:
		return (frontRight_ & (1 << bit-1)) != 0;
		break;
	case Panels::RearLeft:
		return (rearLeft_ & (1 << bit-1)) != 0;
		break;
	case Panels::RearRight:
		return (rearRight_ & (1 << bit-1)) != 0;
		break;
	case Panels::WindShield:
		return (windShield_ & (1 << bit-1)) != 0;
		break;
	case Panels::FrontBumper:
		return (frontBumper_ & (1 << bit-1)) != 0;
		break;
	case Panels::RearBumper:
		return (rearBumper_ & (1 << bit-1)) != 0;
		break;
	}
	return 0;
}

void PanelStatus::setBit(int panel, int bit, bool value)
{
	if(value)
	{
		switch (panel)
		{
		case Panels::FrontLeft:
			frontLeft_ |= (1 << bit-1);
			break;
		case Panels::FrontRight:
			frontRight_ |= (1 << bit-1);
			break;
		case Panels::RearLeft:
			rearLeft_ |= (1 << bit-1);
			break;
		case Panels::RearRight:
			rearRight_ |= (1 << bit-1);
			break;
		case Panels::WindShield:
			windShield_ |= (1 << bit-1);
			break;
		case Panels::FrontBumper:
			frontBumper_ |= (1 << bit-1);
			break;
		case Panels::RearBumper:
			rearBumper_ |= (1 << bit-1);
			break;
		}
	}
	else
	{
		switch (panel)
		{
		case Panels::FrontLeft:
			frontLeft_ &= ~(1 << bit-1);
			break;
		case Panels::FrontRight:
			frontRight_ &= ~(1 << bit-1);
			break;
		case Panels::RearLeft:
			rearLeft_ &= ~(1 << bit-1);
			break;
		case Panels::RearRight:
			rearRight_ &= ~(1 << bit-1);
			break;
		case Panels::WindShield:
			windShield_ &= ~(1 << bit-1);
			break;
		case Panels::FrontBumper:
			frontBumper_ &= ~(1 << bit-1);
			break;
		case Panels::RearBumper:
			rearBumper_ &= ~(1 << bit-1);
			break;
		}
	}
}

bool PanelStatus::getPanelDamaged(int panel)
{
	return getBit(panel, 1);
}

void PanelStatus::setPanelDamaged(int panel, bool value)
{
	setBit(panel, 1, value);
}

bool PanelStatus::getPanelRemoved(int panel)
{
	return getBit(panel, 2);
}

void PanelStatus::setPanelRemoved(int panel, bool value)
{
	setBit(panel, 2, value);
}