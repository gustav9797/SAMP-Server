#pragma once
#include <sampgdk/a_vehicles.h>
#include <cmath>
#include <string>
class VehicleDamageStatus;
class PositionObject;
class Vehicle
{
public:
	Vehicle(int model, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, std::string licensePlate);
	~Vehicle();

	int getId() { return id_; };
	PositionObject getPosition();
	int getSampInterior();
	int getVirtualWorld();
	int getColor1() { return color1_; };
	int getColor2() { return color2_; };
	float getRotation();
	std::string getLicensePlate() { return licensePlate_; };
	void setDamage(float health, int panels, int doors, int lights, int tires);
	void setHealth(float health);
	void setVirtualWorld(int virtualWorld);
	void LinkToInterior(int interior);
	void Delete();
	void Repair();
	VehicleDamageStatus *damageStatus_;
private:
	int id_;
	int model_;
	int color1_;
	int color2_;
	int respawnDelay_;
	int sampInterior_ = -1;
	std::string licensePlate_;
#pragma region Wrapper
	static int samp_Create(int type, float x, float y, float z, float rotation, int color1, int color2, int respawn_delay)
	{
		return CreateVehicle(type, x, y, z, rotation, color1, color2, respawn_delay);
	}

	bool samp_IsValid() const
	{
		return IsValidVehicle(id_);
	}

	float samp_GetDistanceFromPoint(float x, float y, float z) const
	{
		return GetVehicleDistanceFromPoint(id_, x, y, z);
	}

	bool samp_Destroy() const
	{
		return DestroyVehicle(id_);
	}

	bool samp_IsStreamedInFor(int playerid) const
	{
		return IsVehicleStreamedIn(id_, playerid);
	}

	bool samp_GetPos(float *x, float *y, float *z) const
	{
		return GetVehiclePos(id_, x, y, z);
	}

	bool samp_GetPos(float &x, float &y, float &z) const
	{
		return GetVehiclePos(id_, &x, &y, &z);
	}

	bool samp_SetPos(float x, float y, float z) const
	{
		return SetVehiclePos(id_, x, y, z);
	}

	bool samp_GetZAngle(float *z_angle) const
	{
		return GetVehicleZAngle(id_, z_angle);
	}

	bool samp_GetZAngle(float &z_angle) const
	{
		return GetVehicleZAngle(id_, &z_angle);
	}

	float samp_GetZAngle() const
	{
		float z_angle;
		GetVehicleZAngle(id_, &z_angle);
		return z_angle;
	}

	bool samp_GetRotationQuat(float *w, float *x, float *y, float *z) const
	{
		return GetVehicleRotationQuat(id_, w, x, y, z);
	}

	bool samp_SetZAngle(float z_angle) const
	{
		return SetVehicleZAngle(id_, z_angle);
	}

	bool samp_GetRotationQuat(float &w, float &x, float &y, float &z) const
	{
		return GetVehicleRotationQuat(id_, &w, &x, &y, &z);
	}

	bool samp_SetParamsForPlayer(int playerid, bool objective, bool doorslocked) const
	{
		return SetVehicleParamsForPlayer(id_, playerid, objective, doorslocked);
	}

	bool samp_SetParamsEx(bool engine, bool lights, bool alarm, bool doors, bool bonnet, bool boot, bool objective) const
	{
		return SetVehicleParamsEx(id_, engine, lights, alarm, doors, bonnet, boot, objective);
	}

	bool samp_GetParamsEx(bool *engine, bool *lights, bool *alarm, bool *doors, bool *bonnet, bool *boot, bool *objective) const
	{
		return GetVehicleParamsEx(id_, engine, lights, alarm, doors, bonnet, boot, objective);
	}

	bool samp_GetParamsEx(bool &engine, bool &lights, bool &alarm, bool &doors, bool &bonnet, bool &boot, bool &objective) const
	{
		return GetVehicleParamsEx(id_, &engine, &lights, &alarm, &doors, &bonnet, &boot, &objective);
	}

	bool samp_SetToRespawn() const
	{
		return SetVehicleToRespawn(id_);
	}

	bool samp_LinkToInterior(int interiorid) const
	{
		return LinkVehicleToInterior(id_, interiorid);
	}

	bool samp_AddComponent(int componentid) const
	{
		return AddVehicleComponent(id_, componentid);
	}

	bool samp_RemoveComponent(int componentid) const
	{
		return RemoveVehicleComponent(id_, componentid);
	}

	bool samp_ChangeColor(int color1, int color2) const
	{
		return ChangeVehicleColor(id_, color1, color2);
	}

	bool samp_ChangePaintjob(int paintjobid) const
	{
		return ChangeVehiclePaintjob(id_, paintjobid);
	}

	bool samp_SetHealth(float health) const
	{
		return SetVehicleHealth(id_, health);
	}

	bool samp_GetHealth(float *health) const
	{
		return GetVehicleHealth(id_, health);
	}

	bool samp_GetHealth(float &health) const
	{
		return GetVehicleHealth(id_, &health);
	}

	float samp_GetHealth() const
	{
		float health;
		GetVehicleHealth(id_, &health);
		return health;
	}

	bool samp_AttachTrailer(int trailerid) const
	{
		return AttachTrailerToVehicle(trailerid, id_);
	}

	bool samp_DetachTrailer() const
	{
		return DetachTrailerFromVehicle(id_);
	}

	bool samp_IsTrailerAttached() const
	{
		return IsTrailerAttachedToVehicle(id_);
	}

	int samp_GetTrailer() const
	{
		return GetVehicleTrailer(id_);
	}

	bool samp_SetNumberPlate(const char *numberplate) const
	{
		return SetVehicleNumberPlate(id_, numberplate);
	}

	int samp_GetModel() const
	{
		return GetVehicleModel(id_);
	}

	int samp_GetComponentInSlot(int slot) const
	{
		return GetVehicleComponentInSlot(id_, slot);
	}

	bool samp_Repair() const
	{
		return RepairVehicle(id_);
	}

	bool samp_GetVelocity(float *X, float *Y, float *Z) const
	{
		return GetVehicleVelocity(id_, X, Y, Z);
	}

	bool samp_GetVelocity(float &X, float &Y, float &Z) const
	{
		return GetVehicleVelocity(id_, &X, &Y, &Z);
	}

	float samp_GetSpeed() const
	{
		float velX, velY, velZ;
		samp_GetVelocity(velX, velY, velZ);
		return std::sqrt(velX*velX + velY*velY + velZ*velZ);
	}

	bool samp_samp_SetVelocity(float X, float Y, float Z) const
	{
		return SetVehicleVelocity(id_, X, Y, Z);
	}

	bool samp_SetAngularVelocity(float X, float Y, float Z) const
	{
		return SetVehicleAngularVelocity(id_, X, Y, Z);
	}

	bool samp_GetDamageStatus(int *panels, int *doors, int *lights, int *tires) const
	{
		return GetVehicleDamageStatus(id_, panels, doors, lights, tires);
	}

	bool samp_GetDamageStatus(int &panels, int &doors, int &lights, int &tires) const
	{
		return GetVehicleDamageStatus(id_, &panels, &doors, &lights, &tires);
	}

	bool samp_UpdateDamageStatus(int panels, int doors, int lights, int tires) const
	{
		return UpdateVehicleDamageStatus(id_, panels, doors, lights, tires);
	}

	bool samp_SetVirtualWorld(int worldid) const
	{
		return SetVehicleVirtualWorld(id_, worldid);
	}

	int samp_GetVirtualWorld() const
	{
		return GetVehicleVirtualWorld(id_);
	}
#pragma endregion

};

