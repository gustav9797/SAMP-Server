#pragma once
#include <iostream>
#include <bitset>
#include "DamageStatus.h"

class PanelStatus : public DamageStatus
{
private:
	std::bitset<4> frontLeft_;
	std::bitset<4> frontRight_;
	std::bitset<4> rearLeft_;
	std::bitset<4> rearRight_;
	std::bitset<4> windShield_;
	std::bitset<4> frontBumper_;
	std::bitset<4> rearBumper_;
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


