#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "CSV.h"
#include "Colors.h"
#include "DataBase.h"

using namespace std;

DataBase db;

CSV::CSV() {}
CSV::~CSV() {}

string CSV::GetSqlCreateTable(const string p, const string n) {
	string sqlCreate = ("CREATE TABLE '" + n.substr(0, n.rfind(".")) + "' (");
	pn = p + n;
	sqlInsert = ("INSERT INTO '" + n.substr(0, n.rfind(".")) + "' (");

	ifstream file(pn.c_str());
	if (file.is_open()) {
		getline(file, line); // Получение имен полей 
		stringstream lineStream(line);
		while (getline(lineStream, cell, ',')) {
			sqlCreate += "'" + cell + "' TEXT, ";
			sqlInsert += "'" + cell + "', ";
		}
		file.close();
		sqlInsert = sqlInsert.substr(0, sqlInsert.length() - 2) + ") VALUES (";
		return sqlCreate = sqlCreate.substr(0, sqlCreate.length() - 2) + ");";
	}
	else {
		cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << "failed to open file" << ANSI_RESET << endl;
		db.Disconnection();
		file.close();
	}
}

string CSV::GetSqlInsertTable() {
	string sql = sqlInsert;
	ifstream file(pn.c_str());
	if (file.is_open()) {
		getline(file, line); // Пропускаем первую строку файла с именами полей
		while (getline(file, line)) {
			stringstream lineStream(line);
			// Получение значений полей
			while (getline(lineStream, cell, ',')) {
				sql += "'" + cell + "', ";
			}
			sql = sql.substr(0, sql.length() - 2) + "), (";
		}
		sql = sql.substr(0, sql.length() - 3);
		return sql;
	}
	else {
		cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << "failed to open file" << ANSI_RESET << endl;
		db.Disconnection();
		file.close();
		return "";
	}
}