#pragma once
#include <iostream>
#include "MySQLFunctions.h"

#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>

#define DIALOG_REGISTER 1
#define DIALOG_LOGIN 2
#define DIALOG_SUCCESS_1 3
#define DIALOG_SUCCESS_2 4
#define COL_WHITE "{FFFFFF}"
#define COL_RED "{F81414}"
#define COL_GREEN "{00FF22}"
#define COL_LIGHTBLUE "{00CED1}"

namespace registerlogin
{
	bool AccountExists(std::string name);
	bool OnPlayerConnect(int playerid);
	bool OnDialogResponse(int playerid, int dialogid, int response, int listitem, char* inputtext);
}


