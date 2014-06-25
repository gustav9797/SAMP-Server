#include <cmath>
#include <string>

#include <sampgdk/a_objects.h>

class PlayerObject {
public:
	PlayerObject(int playerid, int objectid)
		: playerid_(playerid),
		objectid_(objectid)
	{}

	int GetPlayerId() const { return playerid_; }
	int GetObjectId() const { return objectid_; }

	static PlayerObject Create(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0f) {
		return PlayerObject(playerid, CreatePlayerObject(playerid, modelid, x, y, z, rX, rY, rZ, DrawDistance));
	}

	bool AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return AttachPlayerObjectToPlayer(playerid_, objectid_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return AttachPlayerObjectToVehicle(playerid_, objectid_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool SetPos(float x, float y, float z) const
	{
		return SetPlayerObjectPos(playerid_, objectid_, x, y, z);
	}
	bool GetPos(float *x, float *y, float *z) const
	{
		return GetPlayerObjectPos(playerid_, objectid_, x, y, z);
	}
	bool GetPos(float &x, float &y, float &z) const
	{
		return GetPlayerObjectPos(playerid_, objectid_, &x, &y, &z);
	}
	bool SetRot(float rotX, float rotY, float rotZ) const
	{
		return SetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ);
	}
	bool GetRot(float *rotX, float *rotY, float *rotZ) const
	{
		return GetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ);
	}
	bool GetRot(float &rotX, float &rotY, float &rotZ) const
	{
		return GetPlayerObjectRot(playerid_, objectid_, &rotX, &rotY, &rotZ);
	}
	bool IsValid() const
	{
		return IsValidPlayerObject(playerid_, objectid_);
	}
	bool Destroy() const
	{
		return DestroyPlayerObject(playerid_, objectid_);
	}
	int Move(float X, float Y, float Z, float Speed, float RotX = -1000.0f, float RotY = -1000.0f, float RotZ = -1000.0f) const
	{
		return MovePlayerObject(playerid_, objectid_, X, Y, Z, Speed, RotX, RotY, RotZ);
	}
	bool Stop() const
	{
		return StopPlayerObject(playerid_, objectid_);
	}
	bool IsMoving() const
	{
		return IsPlayerObjectMoving(playerid_, objectid_);
	}
	bool SetMaterial(int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor = 0)
	{
		return SetPlayerObjectMaterial(playerid_, objectid_, materialindex, modelid, txdname, texturename, materialcolor);
	}
	bool SetMaterialText(const char *text, int materialindex = 0, int materialsize = OBJECT_MATERIAL_SIZE_256x128, const char *fontface = "Arial", int fontsize = 24, bool bold = true, int fontcolor = 0xFFFFFFFF, int backcolor = 0, int textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT)
	{
		return SetPlayerObjectMaterialText(playerid_, objectid_, text, materialindex, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
	}

private:
	const int playerid_;
	const int objectid_;
};