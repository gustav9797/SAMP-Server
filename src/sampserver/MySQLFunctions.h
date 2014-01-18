#pragma once
#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "mysql_driver.h"
#include "mysql_connection.h"


namespace MySQLFunctions
{
	void Initialize();

	extern sql::Driver *driver;
	extern sql::Connection *con;
	extern sql::Statement *stmt;
	extern sql::ResultSet *res;

	sql::ResultSet* ExecuteQuery(std::string query);
	bool ExecutePreparedQuery(sql::PreparedStatement *statement);
}

