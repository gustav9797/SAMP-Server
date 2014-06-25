#include <sampgdk/a_players.h>
#include <cmath>
#include <cstddef>
#include <string>
#include <vector>

class Player {
public:
	Player(int playerid) : id_(playerid) {}

	int GetId() const { return id_; }
	operator int() const { return id_; }

	bool Spawn() const
	{
		return SpawnPlayer(id_);
	}
	bool SetPos(float x, float y, float z) const
	{
		return SetPlayerPos(id_, x, y, z);
	}
	bool SetPosFindZ(float x, float y, float z) const
	{
		return SetPlayerPosFindZ(id_, x, y, z);
	}
	bool GetPos(float *x, float *y, float *z) const
	{
		return GetPlayerPos(id_, x, y, z);
	}
	bool GetPos(float &x, float &y, float &z) const
	{
		return GetPlayerPos(id_, &x, &y, &z);
	}
	bool SetFacingAngle(float angle) const
	{
		return SetPlayerFacingAngle(id_, angle);
	}
	bool GetFacingAngle(float *angle) const
	{
		return GetPlayerFacingAngle(id_, angle);
	}
	bool GetFacingAngle(float &angle) const
	{
		return GetPlayerFacingAngle(id_, &angle);
	}
	bool IsInRangeOfPoint(float range, float x, float y, float z) const
	{
		return IsPlayerInRangeOfPoint(id_, range, x, y, z);
	}
	float GetDistanceFromPoint(float x, float y, float z) const
	{
		return GetPlayerDistanceFromPoint(id_, x, y, z);
	}
	bool IsStreamedInFor(int playerid) const
	{
		return IsPlayerStreamedIn(id_, playerid);
	}
	bool SetInterior(int interiorid) const
	{
		return SetPlayerInterior(id_, interiorid);
	}
	int GetInterior() const
	{
		return GetPlayerInterior(id_);
	}
	bool SetHealth(float health) const
	{
		return SetPlayerHealth(id_, health);
	}
	float GetHealth() const {
		float health;
		GetPlayerHealth(id_, &health);
		return health;
	}
	bool SetArmour(float armour) const
	{
		return SetPlayerArmour(id_, armour);
	}
	float GetArmour() const {
		float armour;
		GetPlayerArmour(id_, &armour);
		return armour;
	}
	bool SetAmmo(int weaponslot, int ammo) const
	{
		return SetPlayerAmmo(id_, weaponslot, ammo);
	}
	int GetAmmo() const
	{
		return GetPlayerAmmo(id_);
	}
	int GetWeaponState() const
	{
		return GetPlayerWeaponState(id_);
	}
	int GetTargetPlayer() const
	{
		return GetPlayerTargetPlayer(id_);
	}
	bool SetTeam(int teamid) const
	{
		return SetPlayerTeam(id_, teamid);
	}
	int GetTeam() const
	{
		return GetPlayerTeam(id_);
	}
	bool SetScore(int score) const
	{
		return SetPlayerScore(id_, score);
	}
	int GetScore() const
	{
		return GetPlayerScore(id_);
	}
	int GetDrunkLevel() const
	{
		return GetPlayerDrunkLevel(id_);
	}
	bool SetDrunkLevel(int level) const
	{
		return SetPlayerDrunkLevel(id_, level);
	}
	bool SetColor(int color) const
	{
		return SetPlayerColor(id_, color);
	}
	int GetColor() const
	{
		return GetPlayerColor(id_);
	}
	bool SetSkin(int skinid) const
	{
		return SetPlayerSkin(id_, skinid);
	}
	int GetSkin() const
	{
		return GetPlayerSkin(id_);
	}
	bool GiveWeapon(int weaponid, int ammo) const
	{
		return GivePlayerWeapon(id_, weaponid, ammo);
	}
	bool ResetWeapons() const
	{
		return ResetPlayerWeapons(id_);
	}
	bool SetArmedWeapon(int weaponid) const
	{
		return SetPlayerArmedWeapon(id_, weaponid);
	}
	bool GetWeaponData(int slot, int *weapon, int *ammo) const
	{
		return GetPlayerWeaponData(id_, slot, weapon, ammo);
	}
	bool GetWeaponData(int slot, int &weapon, int &ammo) const
	{
		return GetPlayerWeaponData(id_, slot, &weapon, &ammo);
	}
	bool GiveMoney(int money) const
	{
		return GivePlayerMoney(id_, money);
	}
	bool ResetMoney() const
	{
		return ResetPlayerMoney(id_);
	}
	bool SetName(const char *name) const
	{
		return SetPlayerName(id_, name) > 0;
	}
	bool SetName(const std::string &name) const
	{
		return SetPlayerName(id_, name.c_str()) > 0;
	}
	int GetMoney() const
	{
		return GetPlayerMoney(id_);
	}
	int GetState() const
	{
		return GetPlayerState(id_);
	}
	bool GetIp(char *ip, int size) const
	{
		return GetPlayerIp(id_, ip, size);
	}
	int GetPing() const
	{
		return GetPlayerPing(id_);
	}
	int GetWeapon() const
	{
		return GetPlayerWeapon(id_);
	}
	bool GetKeys(int *keys, int *updown, int *leftright) const
	{
		return GetPlayerKeys(id_, keys, updown, leftright);
	}
	bool GetKeys(int &keys, int &updown, int &leftright) const
	{
		return GetPlayerKeys(id_, &keys, &updown, &leftright);
	}
	int GetName(char *name, int size) const
	{
		return GetPlayerName(id_, name, size);
	}
	std::string GetName() const {
		std::vector<char> name(MAX_PLAYER_NAME);
		GetPlayerName(id_, &name[0], MAX_PLAYER_NAME);
		return std::string(&name[0]);
	}
	bool SetTime(int hour, int minute) const
	{
		return SetPlayerTime(id_, hour, minute);
	}
	bool GetTime(int *hour, int *minute) const
	{
		return GetPlayerTime(id_, hour, minute);
	}
	bool GetTime(int &hour, int &minute) const
	{
		return GetPlayerTime(id_, &hour, &minute);
	}
	bool ToggleClock(bool toggle) const
	{
		return TogglePlayerClock(id_, toggle);
	}
	bool SetWeather(int weather) const
	{
		return SetPlayerWeather(id_, weather);
	}
	bool SetWantedLevel(int level) const
	{
		return SetPlayerWantedLevel(id_, level);
	}
	int GetWantedLevel() const
	{
		return GetPlayerWantedLevel(id_);
	}
	bool SetFightingStyle(int style) const
	{
		return SetPlayerFightingStyle(id_, style);
	}
	int GetFightingStyle() const
	{
		return GetPlayerFightingStyle(id_);
	}
	bool SetVelocity(float x, float y, float z) const
	{
		return SetPlayerVelocity(id_, x, y, z);
	}
	bool GetVelocity(float *x, float *y, float *z) const
	{
		return GetPlayerVelocity(id_, x, y, z);
	}
	bool GetVelocity(float &x, float &y, float &z) const
	{
		return GetPlayerVelocity(id_, &x, &y, &z);
	}
	float GetSpeed() const {
		float velX, velY, velZ;
		GetVelocity(velX, velY, velZ);
		return std::sqrt(velX*velX + velY*velY + velZ*velZ);
	}
	bool PlayCrimeReport(int suspectid, int crime) const
	{
		return PlayCrimeReportForPlayer(id_, suspectid, crime);
	}
	bool PlayAudioStream(const char *url, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float distance = 50.0f, bool usepos = false) const
	{
		return PlayAudioStreamForPlayer(id_, url, posX, posY, posZ, distance, usepos);
	}
	bool PlayAudioStream(const std::string &url, float posX, float posY, float posZ, float distance, bool usepos) const
	{
		return PlayAudioStreamForPlayer(id_, url.c_str(), posX, posY, posZ, distance, usepos);
	}
	bool StopAudioStream() const
	{
		return StopAudioStreamForPlayer(id_);
	}
	bool SetShopName(const char *shopname) const
	{
		return SetPlayerShopName(id_, shopname);
	}
	bool SetShopName(const std::string &shopname) const
	{
		return SetPlayerShopName(id_, shopname.c_str());
	}
	bool SetSkillLevel(int skill, int level) const
	{
		return SetPlayerSkillLevel(id_, skill, level);
	}
	int GetSurfingVehicleID() const
	{
		return GetPlayerSurfingVehicleID(id_);
	}
	int GetSurfingObjectID() const
	{
		return GetPlayerSurfingObjectID(id_);
	}
	bool RemoveBuilding(int modelid, float fX, float fY, float fZ, float fRadius) const
	{
		return RemoveBuildingForPlayer(id_, modelid, fX, fY, fZ, fRadius);
	}

	bool SetAttachedObject(int index, int modelid, int bone, float fOffsetX = 0.0f, float fOffsetY = 0.0f, float fOffsetZ = 0.0f,
		float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, float fScaleX = 1.0f, float fScaleY = 1.0f, float fScaleZ = 1.0f,
		int materialcolor1 = 0, int materialcolor2 = 0) const
	{
		return SetPlayerAttachedObject(id_, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ,
			fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
	}
	bool RemoveAttachedObject(int index) const
	{
		return RemovePlayerAttachedObject(id_, index);
	}
	bool IsAttachedObjectSlotUsed(int index) const
	{
		return IsPlayerAttachedObjectSlotUsed(id_, index);
	}

	bool SetChatBubble(const char *text, int color, float drawdistance, int expiretime) const
	{
		return SetPlayerChatBubble(id_, text, color, drawdistance, expiretime);
	}
	bool SetChatBubble(const std::string &text, int color, float drawdistance, int expiretime) const
	{
		return SetPlayerChatBubble(id_, text.c_str(), color, drawdistance, expiretime);
	}

	bool PutInVehicle(int vehicleid, int seatid) const
	{
		return PutPlayerInVehicle(id_, vehicleid, seatid);
	}
	int GetVehicleID() const
	{
		return GetPlayerVehicleID(id_);
	}
	int GetVehicleSeat() const
	{
		return GetPlayerVehicleSeat(id_);
	}
	bool RemoveFromVehicle() const
	{
		return RemovePlayerFromVehicle(id_);
	}
	bool ToggleControllable(bool toggle) const
	{
		return TogglePlayerControllable(id_, toggle);
	}
	bool PlaySound(int soundid, float x, float y, float z) const
	{
		return PlayerPlaySound(id_, soundid, x, y, z);
	}
	int GetAnimationIndex() const
	{
		return GetPlayerAnimationIndex(id_);
	}
	int GetSpecialAction() const
	{
		return GetPlayerSpecialAction(id_);
	}
	bool SetSpecialAction(int actionid) const
	{
		return SetPlayerSpecialAction(id_, actionid);
	}

	bool SetCheckpoint(float x, float y, float z, float size) const
	{
		return SetPlayerCheckpoint(id_, x, y, z, size);
	}
	bool DisableCheckpoint() const
	{
		return DisablePlayerCheckpoint(id_);
	}
	bool SetRaceCheckpoint(int type, float x, float y, float z, float nextx, float nexty, float nextz, float size) const
	{
		return SetPlayerRaceCheckpoint(id_, type, x, y, z, nextx, nexty, nextz, size);
	}
	bool DisableRaceCheckpoint() const
	{
		return DisablePlayerRaceCheckpoint(id_);
	}
	bool SetWorldBounds(float x_max, float x_min, float y_max, float y_min) const
	{
		return SetPlayerWorldBounds(id_, x_max, x_min, y_max, y_min);
	}
	bool SerMarkerFor(int playerid, int color) const
	{
		return SetPlayerMarkerForPlayer(playerid, id_, color);
	}
	bool ShowNameTagForPlayer(int playerid, bool show) const
	{
		return ShowPlayerNameTagForPlayer(playerid, id_, show);
	}

	bool SetMapIcon(int iconid, float x, float y, float z, int markertype, int color, int style = MAPICON_LOCAL) const
	{
		return SetPlayerMapIcon(id_, iconid, x, y, z, markertype, color, style);
	}
	bool RemoveMapIcon(int iconid) const
	{
		return RemovePlayerMapIcon(id_, iconid);
	}

	bool AllowTeleport(bool allow) const
	{
		return AllowPlayerTeleport(id_, allow);
	}

	bool SetCameraPos(float x, float y, float z) const
	{
		return SetPlayerCameraPos(id_, x, y, z);
	}
	bool SetCameraLookAt(float x, float y, float z, int cut = CAMERA_CUT) const
	{
		return SetPlayerCameraLookAt(id_, x, y, z, cut);
	}
	bool SetCameraBehind() const
	{
		return SetCameraBehindPlayer(id_);
	}
	bool GetCameraPos(float *x, float *y, float *z) const
	{
		return GetPlayerCameraPos(id_, x, y, z);
	}
	bool GetCameraPos(float &x, float &y, float &z) const
	{
		return GetPlayerCameraPos(id_, &x, &y, &z);
	}
	bool GetCameraFrontVector(float *x, float *y, float *z) const
	{
		return GetPlayerCameraFrontVector(id_, x, y, z);
	}
	bool GetCameraFrontVector(float &x, float &y, float &z) const
	{
		return GetPlayerCameraFrontVector(id_, &x, &y, &z);
	}
	int GetCameraMode() const
	{
		return GetPlayerCameraMode(id_);
	}

	bool IsConnected() const
	{
		return IsPlayerConnected(id_);
	}
	bool IsInVehicle(int vehicleid) const
	{
		return IsPlayerInVehicle(id_, vehicleid);
	}
	bool IsInAnyVehicle() const
	{
		return IsPlayerInAnyVehicle(id_);
	}
	bool IsInCheckpoint() const
	{
		return IsPlayerInCheckpoint(id_);
	}
	bool IsInRaceCheckpoint() const
	{
		return IsPlayerInRaceCheckpoint(id_);
	}

	bool SetVirtualWorld(int worldid) const
	{
		return SetPlayerVirtualWorld(id_, worldid);
	}
	int GetVirtualWorld() const
	{
		return GetPlayerVirtualWorld(id_);
	}

	bool EnableStuntBonus(bool enable) const
	{
		return EnableStuntBonusForPlayer(id_, enable);
	}

	bool ToggleSpectating(bool toggle) const
	{
		return TogglePlayerSpectating(id_, toggle);
	}
	bool SpectatePlayer(int playerid, int mode = SPECTATE_MODE_NORMAL) const
	{
		return PlayerSpectatePlayer(id_, playerid, mode);
	}
	bool SpectateVehicle(int vehicleid, int mode = SPECTATE_MODE_NORMAL) const
	{
		return PlayerSpectateVehicle(id_, vehicleid, mode);
	}

	bool StartRecordingData(int recordtype, const char *recordname) const
	{
		return StartRecordingPlayerData(id_, recordtype, recordname);
	}
	bool StartRecordingData(int recordtype, const std::string &recordname) const
	{
		return StartRecordingPlayerData(id_, recordtype, recordname.c_str());
	}
	bool StopRecordingData() const
	{
		return StopRecordingPlayerData(id_);
	}

	// From samp.h
	bool IsNPC() const
	{
		return IsPlayerNPC(id_);
	}
	bool IsAdmin() const
	{
		return IsPlayerAdmin(id_);
	}
	bool GetNetworkStats(char *retstr, int size) const
	{
		return GetPlayerNetworkStats(id_, retstr, size);
	}
	int GetMenu() const
	{
		return GetPlayerMenu(id_);
	}
	bool SendMessage(int color, const char *message) const
	{
		return SendClientMessage(id_, color, message);
	}
	bool SendMessage(int color, const std::string &message) const
	{
		return SendClientMessage(id_, color, message.c_str());
	}
	bool GameText(const char *text, int time, int style) const
	{
		return GameTextForPlayer(id_, text, time, style);
	}
	bool GameText(const std::string &text, int time, int style) const
	{
		return GameTextForPlayer(id_, text.c_str(), time, style);
	}
	bool GetVersion(char *version, int len) const
	{
		return GetPlayerVersion(id_, version, len);
	}

private:
	const int id_;
};