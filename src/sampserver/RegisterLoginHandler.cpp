#include "RegisterLoginHandler.h"

#include <sampgdk\a_players.h>
#include <sampgdk\a_samp.h>

#include "MySQLFunctions.h"
#include "md5.h"
#include "PlayerHandler.h"

RegisterLoginHandler::RegisterLoginHandler(void)
{
	loginAttempts = new std::map<int, int>();
}


RegisterLoginHandler::~RegisterLoginHandler(void)
{
}

bool RegisterLoginHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	return false;
}

void RegisterLoginHandler::CheckForHacks()
{
}

void RegisterLoginHandler::Load(GameUtility* gameUtility)
{
}

bool RegisterLoginHandler::AccountExists(std::string name)
{
	sql::ResultSet *res = MySQLFunctions::ExecuteQuery("SELECT * FROM players WHERE mainaccountname = '" + name + "'");
	if (res != nullptr && res->rowsCount() == 1)
		return true;
	return false;
}

bool RegisterLoginHandler::OnPlayerConnect(int playerid)
{
	return true;
	char *playerName = new char[32];
	GetPlayerName(playerid, playerName, 32);
	if (AccountExists(playerName))
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, ""COL_WHITE"Login", ""COL_WHITE"Type your password below to login.", "Login", "Quit");
	else
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, ""COL_WHITE"Register", ""COL_WHITE"Type your password below to register a new account.", "Register", "Quit");
	return false;
}

bool RegisterLoginHandler::OnDialogResponse(int playerid, int dialogid, int response, int listitem, char* inputtext, GameUtility *gameUtility)
{
	char *playerName = new char[32];
	GetPlayerName(playerid, playerName, 32);
	switch (dialogid)
	{
	case DIALOG_REGISTER:
		{
			if (!response) return Kick(playerid);
			if (response)
			{
				if (!strlen(inputtext)) 
					return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, ""COL_WHITE"Register", ""COL_RED"You have entered an invalid password.\n"COL_WHITE"Type your password below to register a new account.", "Register", "Quit");

				sql::PreparedStatement *stmt = MySQLFunctions::con->prepareStatement("INSERT INTO players(mainaccountname, password) VALUES(?, ?)");
				stmt->setString(1, playerName);
				stmt->setString(2, md5(inputtext));
				MySQLFunctions::ExecutePreparedQuery(stmt);

				ShowPlayerDialog(playerid, DIALOG_SUCCESS_1, DIALOG_STYLE_MSGBOX, ""COL_WHITE"Register", ""COL_GREEN"Registered! You have been logged in automatically.", "Ok", "");
			}
		}
		break;
	case DIALOG_LOGIN:
		{
			if (!response) return Kick(playerid);
			if (response)
			{
				sql::PreparedStatement *stmt = MySQLFunctions::con->prepareStatement("SELECT * FROM players WHERE mainaccountname = ? LIMIT 1");
				stmt->setString(1, playerName);
				sql::ResultSet *res = stmt->executeQuery();
				res->next();
				if (res != nullptr && res->rowsCount() == 1)
				{
					if(loginAttempts->find(playerid) == loginAttempts->end())
						loginAttempts->emplace(playerid, 0);
					loginAttempts->at(playerid)++;

					std::string password = res->getString("password");
					if (md5(inputtext) == password)
					{
						loginAttempts->erase(playerid);
						sql::PreparedStatement *stmt = MySQLFunctions::con->prepareStatement("SELECT * FROM players WHERE mainaccountname = ? LIMIT 1");
						stmt->setString(1, playerName);
						sql::ResultSet *res = stmt->executeQuery();
						res->next();
						ShowPlayerDialog(playerid, DIALOG_SUCCESS_2, DIALOG_STYLE_MSGBOX, ""COL_WHITE"Login", ""COL_WHITE"You have been successfully logged in!", "Ok", "");
					}
					else if(loginAttempts->at(playerid) < 3)
						ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, ""COL_WHITE"Login", ""COL_RED"You have entered an incorrect password.\n"COL_WHITE"Type your password below to login.", "Login", "Quit");
					else
					{
						return gameUtility->playerHandler->KickPlayer(playerid, "Max login attempts reached.", gameUtility);
					}
				}
				return true;
			}
		}
		break;
	}
	return true;
}
