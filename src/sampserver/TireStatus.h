#pragma once
#include "DamageStatus.h"

class TireStatus : public DamageStatus
{
private:
	char frontLeft_;
	char rearLeft_;
	char frontRight_;
	char rearRight_;
	virtual bool getBit(int tire, int bit);
	virtual void setBit(int tire, int bit, bool value);
public:
	TireStatus(int tires);
	~TireStatus(void);
	bool getTireDamaged(int tire);
	void setTireDamaged(int tire, bool value);
	virtual int Encode();
	virtual void Decode(int raw);
};

enum Tires
{
	FrontLeftTire=0,
	RearLeftTire,
	FrontRightTire,
	RearRightTire,
};

