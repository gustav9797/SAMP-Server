#include <cmath>
#include <string>

#include <sampgdk/a_objects.h>

class Object {
public:
	Object(int objectid) : id_(objectid) {}

	int GetId() const { return id_; }
	operator int() const { return id_; }

	static Object Create(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0f) {
		return CreateObject(modelid, x, y, z, rX, rY, rZ, DrawDistance);
	}

	bool AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return AttachObjectToVehicle(id_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool AttachToObject(int objectid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation = true) const {
		return AttachObjectToObject(id_, objectid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, SyncRotation);
	}
	bool AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return AttachObjectToPlayer(id_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool SetPos(float x, float y, float z) const
	{
		return SetObjectPos(id_, x, y, z);
	}
	bool GetPos(float *x, float *y, float *z) const
	{
		return GetObjectPos(id_, x, y, z);
	}
	bool GetPos(float &x, float &y, float &z) const
	{
		return GetObjectPos(id_, &x, &y, &z);
	}
	bool SetRot(float rotX, float rotY, float rotZ) const
	{
		return SetObjectRot(id_, rotX, rotY, rotZ);
	}
	bool GetRot(float *rotX, float *rotY, float *rotZ) const
	{
		return GetObjectRot(id_, rotX, rotY, rotZ);
	}
	bool GetRot(float &rotX, float &rotY, float &rotZ) const
	{
		return GetObjectRot(id_, &rotX, &rotY, &rotZ);
	}
	bool IsValid() const
	{
		return IsValidObject(id_);
	}
	bool Destroy() const
	{
		return DestroyObject(id_);
	}
	int Move(float X, float Y, float Z, float Speed, float RotX = -1000.0f, float RotY = -1000.0f, float RotZ = -1000.0f) const
	{
		return MoveObject(id_, X, Y, Z, Speed, RotX, RotY, RotZ);
	}
	bool Stop() const
	{
		return StopObject(id_);
	}
	bool IsMoving() const
	{
		return IsObjectMoving(id_);
	}
	bool SetMaterial(int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor = 0)
	{
		return SetObjectMaterial(id_, materialindex, modelid, txdname, texturename, materialcolor);
	}
	bool SetMaterialText(const char *text, int materialindex = 0, int materialsize = OBJECT_MATERIAL_SIZE_256x128, const char *fontface = "Arial", int fontsize = 24, bool bold = true, int fontcolor = 0xFFFFFFFF, int backcolor = 0, int textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT)
	{
		return SetObjectMaterialText(id_, text, materialindex, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
	}

private:
	const int id_;
};