#pragma once
#include <iostream>
#include "DamageStatus.h"

class PanelStatus : public DamageStatus
{
private:
	char frontLeft_;
	char frontRight_;
	char rearLeft_;
	char rearRight_;
	char windShield_;
	char frontBumper_;
	char rearBumper_;
	virtual bool getBit(int panel, int bit);
	virtual void setBit(int panel, int bit, bool value);
public:
	PanelStatus(int panels);
	~PanelStatus(void);
	bool getPanelDamaged(int panel);
	void setPanelDamaged(int panel, bool value);
	bool getPanelRemoved(int panel);
	void setPanelRemoved(int panel, bool value);
	virtual int Encode();
	virtual void Decode(int panels);
};

enum Panels
{
	FrontLeft=0,
	FrontRight,
	RearLeft,
	RearRight,
	WindShield,
	FrontBumper,
	RearBumper
};


