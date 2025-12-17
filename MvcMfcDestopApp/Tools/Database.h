#pragma once
//include the below additional libraries
#include <string>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <vector>
#include "../Model/EmployeeModel.h"

//use the std namespace
using namespace std;

class Database
{
public:
	Database();
	~Database();
	bool connect(const string& dsn, const string& user, const string& password);
	void disconnect();

	std::vector<std::unique_ptr<IModel>> getEmployees(int companyId);

private:
	bool executeQuery(const string& query);
	void fetchResults();
	std::string SQLCHARToString(SQLCHAR* sqlChar, SQLSMALLINT length);
	SQLSMALLINT SQLCHARLength(SQLCHAR* sqlChar) const;

private:
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;
	bool isConnected;
};
