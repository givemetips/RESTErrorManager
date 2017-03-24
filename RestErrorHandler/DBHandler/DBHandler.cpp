#include "stdafx.h"
#include "sqlite3.h"
#include "DBHandler.h"

sqlite3* DBHandler::db = nullptr;

std::vector<Error> DBHandler::selectResult{};

DBHandler::DBHandler() { };

void DBHandler::openConnection(const std::string& dbName) {
	const std::string dbFile = dbName + ".db";

	int rc = sqlite3_open(dbFile.c_str(), &db);
	if (rc) {
		std::cerr << "Error while openning DB: " + dbName << std::endl << "Error: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "DB " + dbName + " opened correctly" << std::endl;
	}
}

void DBHandler::closeConnection() {
	sqlite3_close(db);
}

void DBHandler::insertErrors(const std::vector<Error>& vecToInsert, const std::string& tableName) {
	std::string sqlCreateQuerry = "CREATE TABLE IF NOT EXISTS " + tableName + "(name, source, stacktrace, date, correct)";
	char *err = 0;

	int rc = sqlite3_exec(db, sqlCreateQuerry.c_str(), 0, 0, &err);
	if (rc) {
		std::cerr << "Error while creating/openning table: " << tableName << std::endl << "Error: " << err << std::endl;
	}
	else {
		std::cout << tableName << " opened/created successfully" << std::endl;
	}

	std::string sqlInsertQuerry = "INSERT INTO " + tableName + " VALUES ";

	for (size_t i = 0; i < vecToInsert.size(); ++i) {
		std::string appendToInsertQuerry = "('" + vecToInsert[i].getName() + "', '" + vecToInsert[i].getSource() + "', '" + vecToInsert[i].getStackTrace() + "', '" + Date::toString(vecToInsert[i].getRegDate()) + "', '" + std::to_string(vecToInsert[i].getCorrectedStatus()) + "')";
	
		if (i != vecToInsert.size() - 1) appendToInsertQuerry += ", ";

		sqlInsertQuerry += appendToInsertQuerry;
	}

	rc = sqlite3_exec(db, sqlInsertQuerry.c_str(), 0, 0, &err);
	if (rc) {
		std::cerr << "Error while inserting values into " + tableName << std::endl << "Error: " << err << std::endl;
	}
	else {
		std::cout << "Values have been correctly inserted into " + tableName << std::endl;
	}
}

std::vector<Error> DBHandler::selectErrors(const std::string& sqlQuery) {
	selectResult.erase(selectResult.begin(), selectResult.end());
	char *errMsg;

	int rc = sqlite3_exec(db, sqlQuery.c_str(), selectCallBackFunction, 0, &errMsg);
	if (rc) {
		std::cerr << "Error while extracting data from DB" << std::endl << "Error: " << errMsg << std::endl;
	}
	else {
		std::cout << "Data successfully extracted" << std::endl;
	}

	return selectResult;

}

int DBHandler::selectCallBackFunction(void * notUsed, int argc, char** argv, char**colNames) {
	Error resultError;

	for (int i = 0; i < argc; ++i) {
		if (colNames[i] == "name") {
			resultError.setName(argv[i]);
			continue;
		}

		if (colNames[i] == "source") {
			resultError.setSource(argv[i]);
			continue;
		}

		if (colNames[i] == "stacktrace") {
			resultError.setStackTrace(argv[i]);
			continue;
		}

		if (colNames[i] == "date") {
			resultError.setRegDate(Date(argv[i]));
			continue;
		}

		if (colNames[i] == "correct") {
			resultError.setCorrectedStatus(std::stoi(argv[i]));
			continue;
		}
	}

	selectResult.push_back(resultError);
	
	return 0;
}