#pragma once
#include "stdafx.h"
#include "sqlite3.h"
#include "Error.h"

class DBHandler {

public:
	void openConnection(const std::string& dbName);

	void closeConnection();

	void insertErrors(const std::vector<Error>& vecToInsert, const std::string& tableName);

	std::vector<Error> selectErrors(const std::string& sqlQuery);
	
	static DBHandler getInstance() {
		static DBHandler dbInstance;
		return dbInstance;
	}

private:
	static sqlite3 *db;

	static std::vector<Error> selectResult;

	static int selectCallBackFunction(void* notUsed, int argc, char **argv, char **azColName);

	DBHandler();
};

