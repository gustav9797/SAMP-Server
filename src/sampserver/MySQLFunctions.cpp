#pragma once
#include "MySQLFunctions.h"

namespace MySQLFunctions
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	void Initialize()
	{
		driver = get_driver_instance();
		try
		{
			con = driver->connect("127.0.0.1", "root", "1342");
		}
		catch (sql::SQLException &e)
		{
			std::cout << e.what() << std::endl;
			std::cin.get();
		}
		con->setSchema("samp");
	}

	sql::ResultSet* ExecuteQuery(std::string query)
	{
		try
		{
			stmt = con->createStatement();
			res = stmt->executeQuery(query);
			delete stmt;
			return res;
		}
		catch (sql::SQLException &e)
		{
			std::cout << "# ERR: SQLException in " << __FILE__;
			std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
			std::cout << "# ERR: " << e.what();
			std::cout << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		}
		return nullptr;
	}

	bool ExecutePreparedQuery(sql::PreparedStatement *statement)
	{
		try
		{
			bool result = statement->execute();
			delete statement;
			return result;
		}
		catch (sql::SQLException &e)
		{
			std::cout << "# ERR: SQLException in " << __FILE__;
			std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
			std::cout << "# ERR: " << e.what();
			std::cout << " (MySQL error code: " << e.getErrorCode();
			std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
			std::cin.get();
		}
		return false;
	}
}

