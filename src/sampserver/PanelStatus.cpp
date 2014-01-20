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

bool PanelStatus::getPanelDamaged(int panel)
{
	return getBit(panel, 1);
}

bool PanelStatus::getPanelRemoved(int panel)
{
	return getBit(panel, 2);
}

std::string PanelStatus::ToString()
{
	std::stringstream s;
	s << "DAMAGED: " << "frontbumper:" << getPanelDamaged(Panels::FrontBumper) << " rearbumper:" << getPanelDamaged(Panels::RearBumper);
	s << "\r\n" << "REMOVED: " << "frontbumper:" << getPanelRemoved(Panels::FrontBumper) << " rearbumper:" << getPanelRemoved(Panels::RearBumper);
	return s.str();
}

