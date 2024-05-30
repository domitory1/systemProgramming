#pragma once

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

class DataBase
{
private:
	sqlite3* db;

public:
	DataBase();
	~DataBase();

	bool Connection(const string path);
	void Disconnection();
	void SelectTables(const string n, const string pointerTable);
	void CreateTable(const string query);
	void DeleteTable(const string pointerTable);
	void RequestTable(const string query);
};