#pragma once
#include "DamageStatus.h"

class LightStatus : public DamageStatus
{
private:
	char frontLeft_;
	char rearLeft_;
	char frontRight_;
	char rearRight_;
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


