#pragma once
#define DIALOG_REGISTER 1
#define DIALOG_LOGIN 2
#define DIALOG_SUCCESS_1 3
#define DIALOG_SUCCESS_2 4
#define COL_WHITE "{FFFFFF}"
#define COL_RED "{F81414}"
#define COL_GREEN "{00FF22}"
#define COL_LIGHTBLUE "{00CED1}"

#include <map>
#include "handler.h"

class RegisterLoginHandler :
	public Handler
{
private:
	std::map<int, int> *loginAttempts;
public:
	RegisterLoginHandler(void);
	~RegisterLoginHandler(void);
	virtual bool OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility);
	virtual void CheckForHacks();
	virtual void Load(GameUtility* gameUtility);
	bool AccountExists(std::string name);
	bool OnPlayerConnect(int playerid);
	bool OnDialogResponse(int playerid, int dialogid, int response, int listitem, char* inputtext, GameUtility *gameUtility);
};

