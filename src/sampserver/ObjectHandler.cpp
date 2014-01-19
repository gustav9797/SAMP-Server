#include "ObjectHandler.h"
#include "MyObject.h"


ObjectHandler::ObjectHandler(void)
{
	objects = new std::map<int, MyObject*>();
}


ObjectHandler::~ObjectHandler(void)
{
}

bool ObjectHandler::OnCommand(MyPlayer *player, std::string cmd, std::vector<std::string> args, GameUtility *gameUtility)
{
	return false;
}

void ObjectHandler::CheckForHacks()
{
}

void ObjectHandler::Load(GameUtility* gameUtility)
{
}

MyObject *ObjectHandler::CreateObject(int model, float x, float y, float z, float rx, float ry, float rz, float drawDistance)
{
	//MyObj
		/*sql::PreparedStatement *statement = MySQLFunctions::con->prepareStatement("INSERT INTO objects(licenseplate, owner, virtualworld, interior, model, x, y, z, rotation, color1, color2, respawndelay) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
	statement->setInt(1, virtualWorld);
	statement->setDouble(2, x);
	statement->setDouble(3, y);
	statement->setDouble(4, z);
	statement->setDouble(5, x);
	statement->setDouble(6, y);
	statement->setDouble(7, z);
	statement->setDouble(8, rotation);
	MySQLFunctions::ExecutePreparedQuery(statement);*/
	return nullptr;
}

void ObjectHandler::RemoveObject(int id)
{
}

std::vector<MyObject*> *ObjectHandler::getCloseObjects(float x, float y, float z, float maxDistance)
{
	return nullptr;
}
