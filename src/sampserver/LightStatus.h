#pragma once
#include "DamageStatus.h"
#include <bitset>

class LightStatus : public DamageStatus
{
private:
	std::bitset<1> frontLeft_;
	std::bitset<1> rearLeft_;
	std::bitset<1> frontRight_;
	std::bitset<1> rearRight_;
	virtual bool getBit(int light, int bit);
	virtual void setBit(int light, int bit, bool value);
public:
	LightStatus(int lights);
	~LightStatus(void);
	bool getLightDamaged(int light);
	void setLightDamaged(int light, bool value);
	virtual int Encode();
	virtual void Decode(int raw);
};

enum Lights
{
	FrontLeftLight=0,
	RearLeftLight,
	FrontRightLight,
	RearRightLight,
};


