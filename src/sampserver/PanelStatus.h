#pragma once
#include <iostream>
class PanelStatus
{
private:
	char frontLeft_;
	char frontRight_;
	char rearLeft_;
	char rearRight_;
	char windShield_;
	char frontBumper_;
	char rearBumper_;
	bool getBit(int panel, int bit);
public:
	PanelStatus(int panels);
	~PanelStatus(void);
	int getRaw() { return Encode(); };
	bool getPanelDamaged(int panel);
	bool getPanelRemoved(int panel);
	int Encode();
	void Decode(int panels);
	std::string ToString();
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


