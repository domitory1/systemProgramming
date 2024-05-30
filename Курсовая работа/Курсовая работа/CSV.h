#pragma once

#include <string>

using namespace std;

class CSV
{
private:
	string pn;
	string line;
	string cell;
	string sqlInsert;

public:
	CSV();
	~CSV();

	string GetSqlCreateTable(const string p, const string n);
	string GetSqlInsertTable();
};
