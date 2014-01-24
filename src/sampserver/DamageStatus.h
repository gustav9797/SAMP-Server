#pragma once
class DamageStatus
{
private:
	virtual bool getBit(int what, int bit)=0;
	virtual void setBit(int what, int bit, bool value)=0;
public:
	virtual int Encode()=0;
	virtual int getRaw() { return Encode(); };
	virtual void Decode(int raw)=0;
	virtual void Update(int raw) { Decode(raw); };
};

