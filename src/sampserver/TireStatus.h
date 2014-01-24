#pragma once
#include "DamageStatus.h"
#include <bitset>

class TireStatus : public DamageStatus
{
private:
	std::bitset<1> frontLeft_;
	std::bitset<1> rearLeft_;
	std::bitset<1> frontRight_;
	std::bitset<1> rearRight_;
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

