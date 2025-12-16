#include "../pch.h"
#include <iostream>
#include "Database.h"

Database::Database() : hEnv(nullptr), hDbc(nullptr), hStmt(nullptr), isConnected(false)
{
	// Allocate environment handle
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
}

Database::~Database()
{
	disconnect();
	if (hEnv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
		hEnv = nullptr;
	}
}

bool Database::connect(const string& dsn, const string& user, const string& password)
{
	if (isConnected) return true;

	// Allocate connection handle
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	// Connect to the data source
	SQLRETURN ret = SQLConnectA(hDbc,
		(SQLCHAR*)dsn.c_str(), SQL_NTS,
		(SQLCHAR*)user.c_str(), SQL_NTS,
		(SQLCHAR*)password.c_str(), SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		isConnected = true;
		return true;
	}

	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	hDbc = nullptr;
	return false;

}

void Database::disconnect()
{
	if (!isConnected)
		return;

	if (hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		hStmt = nullptr;
	}

	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	hDbc = nullptr;
	isConnected = false;

}

bool Database::executeQuery(const string& query)
{
	if (!isConnected) return false;

	// Allocate statement handle
	SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	// Execute the query
	SQLRETURN ret = SQLExecDirectA(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
	return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

void Database::fetchResults()
{
	if (!isConnected || !hStmt) return;

	SQLINTEGER id;
	SQLCHAR name[256];
	while (SQLFetch(hStmt) == SQL_SUCCESS)
	{
		SQLGetData(hStmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr);
		cout << "Result: " << id << endl;

		SQLGetData(hStmt, 2, SQL_C_CHAR, name, sizeof(name), nullptr);
		cout << "Result: " << name << endl;
	}
}

std::string Database::SQLCHARToString(SQLCHAR* sqlChar, SQLSMALLINT length) {
	return std::string(reinterpret_cast<const char*>(sqlChar), length);
}

SQLSMALLINT Database::SQLCHARLength(SQLCHAR* sqlCharArray) const 
{
	// Assuming the length is known or can be retrieved
	SQLSMALLINT length = static_cast<SQLSMALLINT>(strlen(reinterpret_cast<const char*>(sqlCharArray)));
	return length;
}

bool Database::getEmployees(std::vector<std::unique_ptr<IModel>>& dataset, int companyId) 
{
	bool returnValue = false;

	if (!executeQuery("SELECT Employees.Id, Employees.Name FROM Employees, CompaniesEmployees WHERE CompaniesEmployees.CompanyId = 1 AND Employees.Id = CompaniesEmployees.EmployeeId"))
		return returnValue;

	if (!isConnected || !hStmt) 
		return returnValue;

	dataset.clear();

	SQLINTEGER id{};
	SQLCHAR buffer[256]{};
	while (SQLFetch(hStmt) == SQL_SUCCESS)
	{
		SQLGetData(hStmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr);
		SQLGetData(hStmt, 2, SQL_C_CHAR, buffer, sizeof(buffer), nullptr);


		std::string name = SQLCHARToString( buffer, SQLCHARLength(buffer));
		dataset.emplace_back(std::make_unique<EmployeeModel>(id, companyId, name));
	}

	return true;
}