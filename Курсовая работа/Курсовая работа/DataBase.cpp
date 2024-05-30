#include <iostream>
#include <string>
#include <vector>

#include "DataBase.h"
#include "Colors.h"

using namespace std;

DataBase::DataBase() {}

DataBase::~DataBase() {
	sqlite3_close(db);
}

bool DataBase::Connection(const string path) {
	const char* PATH = ("file:\\\\\\" + path).c_str();

	if (sqlite3_open(PATH, &db) != SQLITE_OK) {
		cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << sqlite3_errmsg(db) << ANSI_RESET << endl;
		sqlite3_close(db);
		return false;
	}
	return true;
}

void DataBase::Disconnection() {
	sqlite3_close(db);
}

void DataBase::SelectTables(const string n, const string pointerTable) {
	sqlite3_stmt* statement;
	vector<string> tableNames;
	const char* selectTableNames = "SELECT name FROM sqlite_master WHERE type='table';";

	if (sqlite3_prepare_v2(db, selectTableNames, -1, &statement, nullptr) != SQLITE_OK) {
		cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << sqlite3_errmsg(db) << ANSI_RESET << endl;
		return;
	}
	while (sqlite3_step(statement) == SQLITE_ROW) {
		tableNames.push_back(string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0))));
	}

	cout << ANSI_PURPLE_BG << ANSI_BLACK << n << ANSI_RESET << endl;
	if (tableNames.empty()) {
		cout << ANSI_YELLOW << "The DB has no tables" << ANSI_RESET << endl << endl;
	}
	else {
		for (const auto& name : tableNames) {
			if (name == pointerTable) {
				cout << "|_ " << ANSI_YELLOW_BG << ANSI_BLACK << name << ANSI_RESET << endl;
			}
			else {
				cout << "|_ " << name << endl;
			}
		}
		cout << endl;
	}
	sqlite3_finalize(statement);
	tableNames.clear();

	if (pointerTable != "") {
		const string selectTableContent = ("SELECT * FROM " + pointerTable + ";");

		if (sqlite3_prepare_v2(db, selectTableContent.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
			cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << sqlite3_errmsg(db) << ANSI_RESET << endl;
			sqlite3_finalize(statement);
			return;
		}

		int column = sqlite3_column_count(statement);
		for (int i = 0; i < column; i++) {
			cout << sqlite3_column_name(statement, i) << "\t";
		}
		cout << endl;

		while (sqlite3_step(statement) == SQLITE_ROW) {
			for (int i = 0; i < column; i++) {
				cout << sqlite3_column_text(statement, i) << "\t";
			}
			cout << endl;
		}
		cout << endl;
		sqlite3_finalize(statement);
		return;
	}
}

void DataBase::CreateTable(string query) {
	char* errMsg = nullptr;
	const char* sql = query.c_str();
	int resultQuery = sqlite3_exec(db, sql, 0, 0, &errMsg);

	if (resultQuery != SQLITE_OK) {
		cout << query << endl;
		cout << ANSI_RED << "SQL ERROR: " << ANSI_YELLOW << sqlite3_errmsg(db) << ANSI_RESET << endl;
		sqlite3_free(errMsg);
		return;
	}
	cout << ANSI_GREEN << "Successful table creation" << ANSI_RESET << endl;
	return;
}

void DataBase::DeleteTable(const string pointerTable) {
	char* errMsg = nullptr;
	const string sql = ("DROP TABLE IF EXISTS " + pointerTable + ";");

	int resultQuery = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
	if (resultQuery != SQLITE_OK) {
		cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << sqlite3_errmsg(db) << ANSI_RESET << endl;
		sqlite3_free(errMsg);
		return;
	}
	cout << ANSI_GREEN << "Tables deleted" << ANSI_RESET << endl;
	
}

void DataBase::RequestTable(const string query) {
	char* errMsg = nullptr;
	const char* sql = query.c_str();

	int resultRequests = sqlite3_exec(db, sql, 0, 0, &errMsg);
	if (resultRequests != SQLITE_OK) {
		cout << query << endl;
		cout << ANSI_RED << "ERROR: " << sqlite3_errmsg(db) << ANSI_RESET << endl;
		sqlite3_free(errMsg);
		return;
	}
	cout << ANSI_GREEN << "Requests completed successfyly" << ANSI_RESET << endl;
	return;
}