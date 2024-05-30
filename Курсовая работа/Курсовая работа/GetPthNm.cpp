#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "GetPthNm.h"
#include "Colors.h"

using namespace std;

GetPthNm::GetPthNm() {};
GetPthNm::~GetPthNm() {};

string GetPthNm::CreateFile(const string p) {
	cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << "dataBase doesn`t exist" << ANSI_RESET << endl;
	cout << "Create new DB ?" << endl;

	while (true) {
		string answer;
		cout << "Input: ";
		getline(cin, answer);

		if (answer == "/exit") {
			return answer;
		}
		else if (answer == "") {
			continue;
		}
		else if (answer == "no") {
			return answer;
		}
		else if (answer == "yes") {
			cout << "Enter the name of DataBase" << endl;

			while (true) {
				cout << "Input: ";
				getline(cin, answer);

				if (answer == "/exit") {
					return answer;
				}
				else if (answer == "") {
					continue;
				}
				if (answer.find('.') == string::npos) {
					answer += ".db";
				}

				string pa = p + answer;
				fstream db(pa.c_str(), ios_base::app);
				if (db.is_open()) {
					db.close();
					return "DB created";
				}
				else {
					db.close();
					return "DB not created";
				}

			}
		}
		else {
			cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << "invalid input. Enter «yes» or «no»" << ANSI_RESET << endl;
		}
	}
}

string GetPthNm::Get(const string typeMove) {
	cout << "Enter the path of file" << endl;

	while (true) {
		cout << "Input: ";
		getline(cin, p);

		if (p == "/exit") {
			return p;
		}
		else if (p == "") {
			continue;
		}
		else if (filesystem::exists(p.c_str())) {
			if (p[p.length() - 1] != '\\') {
				p += "\\";
			}

			cout << "Enter the name of file" << endl;

			if (typeMove == "getDB") {
				while (true) {
					cout << "Input: ";
					getline(cin, n);

					if (n == "/exit") {
						return n;
					}
					else if (n == "") {
						continue;
					}
					else {
						if (n.find('.') == string::npos) {
							n += ".db";
						}
						string pn = p + n;
						if (filesystem::exists(pn)) {
							return p, n;
						}
						else {
							string answer = this->CreateFile(p);
							if (answer == "/exit") {
								return answer;
							}
							else if (answer == "no") {
								cout << "Enter the DB name" << endl;
								continue;
							}
							else if (answer == "DB created") {
								cout << ANSI_GREEN << answer << ANSI_RESET << endl;
								cout << "Enter the DB name" << endl;
								continue;
							}
							else if (answer == "DB not created") {
								cout << ANSI_RED << answer << ANSI_RESET << endl;
								cout << "Enter the DB name" << endl;
								continue;
							}
						}
					}
				}
			}
			else if (typeMove == "getCSV") {
				while (true) {
					cout << "Input: ";
					getline(cin, n);

					if (n == "/back" || n == "/exit") {
						return n;
					}
					else if (n == "") {
						continue;
					}
					else {
						if (n.find('.') == string::npos) {
							n += ".csv";
						}
						string pn = p + n;
						if (filesystem::exists(pn)) {
							return pn;
						}
						else {
							cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << "file doesn`t exists" << ANSI_RESET << endl;
							cout << "Enter the name of file" << endl;
							continue;
						}
					}
				}
			}
		}
		else {
			cout << ANSI_RED << "ERROR: " << ANSI_YELLOW << "path is`n exists" << ANSI_RESET << endl;
			continue;
		}
	}
}