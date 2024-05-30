#include <iostream>
#include <string>
#include <windows.h>

#include "Console.h"
#include "Colors.h"
#include "GetPthNm.h"
#include "DataBase.h"
#include "CSV.h"

using namespace std;

int main()
{
    system("chcp 1251");
    ClearConsole();

    GetPthNm GPN;
    DataBase DB;
	CSV csv;
    string p, n;
    string pointerTable;
	string command;

    while (true) {

        cout << "To exit the programm, enter «/exit»" << endl << endl;

        p, n = GPN.Get("getDB");

        if (p == "/exit" || n == "/exit") {
            cout << "Exit the programm" << endl;
            return 0;
        }

        ClearConsole();
		if (!DB.Connection(p + n)) {
			continue;
		}

        while (true) {
            cout << "To exit the programm, enter «/exit»" << endl;
            cout << "To return to the main menu, enter «/back»" << endl;
            cout << "To create new table, enter «/create_table»" << endl;
            cout << "To go to tablle, enter «/go_TABLENAME»" << endl;
            cout << "To delete table, enter «/delete_TABLENAME»" << endl;
			cout << ANSI_YELLOW_BG << ANSI_BLACK << "To transfer data from a csv file, enter «/transfer_csv»" << ANSI_RESET << endl;
            if (pointerTable != "") {
                cout << "To return to DB, enter «/returnDB»" << endl;
                cout << "To complete reqest, enter «/request»" << endl;
            }
            cout << endl;

			system("chcp 65001");
            DB.SelectTables(n, pointerTable);
			system("chcp 1251");

			cout << "Input: ";
			getline(cin, command);
			if (command == "/back") {
				pointerTable = "";
				DB.Disconnection();
				ClearConsole();
				break;
			}
			else if (command == "/exit") {
				DB.Disconnection();
				cout << "Exit the programm" << endl;
				return 0;
			}
			else if (command == "/create_table") {
				cout << "Enter the request to create table" << endl;

				while (true) {
					cout << "Input: ";
					getline(cin, command);
					if (command == "/back") {
						pointerTable = "";
						DB.Disconnection();
						ClearConsole();
						break;
					}
					else if (command == "/exit") {
						DB.Disconnection();
						cout << "Exit the programm" << endl;
						return 0;
					}
					else if (command == "") {
						continue;
					}
					else {
						ClearConsole();
						cout << "Input: " << command << endl;
						DB.CreateTable(command);
						break;
					}
				}
				continue;
			}
			else if (command.substr(0, 8) == "/delete_") {
				pointerTable = command.substr(8);
				ClearConsole();
				cout << "Input: " << command << endl;
				DB.DeleteTable(pointerTable);
				pointerTable = "";
				continue;

			}
			// Трансфер данный из csv-файла в БД
			else if (command == "/transfer_csv") {
				string pn = GPN.Get("getCSV");

				string pT = pn.substr(0, pn.rfind("\\") + 1);
				string nT = pn.substr(pn.rfind("\\") + 1);

				if (pT == "/back" || nT == "/back") {
					ClearConsole();
					break;
				}
				else if (pT == "/exit" || nT == "/exit") {
					DB.Disconnection();
					cout << "Exit the programm" << endl;
					return 0;
				}

				system("chcp 65001"); // Изменение кодировки для корректного чтения csv-файла, использующий utf-8
				ClearConsole();
				string sql = csv.GetSqlCreateTable(pT, nT);
				DB.CreateTable(sql);
				sql = csv.GetSqlInsertTable();
				if (sql != "") {
					DB.RequestTable(sql);
				}
				system("chcp 1251");
				continue;
			}
			else if (command.substr(0, 4) == "/go_") {
				pointerTable = command.substr(4);
				ClearConsole();
				cout << "Input: " << command << endl;
				continue;
			}
			else if (command == "/returnDB" && pointerTable != "") {
				pointerTable = "";
				ClearConsole();
				continue;
			}
			else if (command.substr(0, 9) == "/request" && pointerTable != "") {

				cout << "Enter the request" << endl;
				while (true) {
					cout << "Input: ";
					getline(cin, command);

					if (command == "/back") {
						pointerTable = "";
						DB.Disconnection();
						ClearConsole();
						break;
					}
					else if (command == "/exit") {
						cout << "Exit the programm" << endl;
						DB.Disconnection();
						return 0;
					}
					else if (command == "") {
						continue;
					}
					else {
						ClearConsole();
						cout << "Input: " << command << endl;
						DB.RequestTable(command);
						break;
					}
				}
				continue;
			}
			else if (command == "") {
				ClearConsole();
				continue;
			}
			else {
				ClearConsole();
				cout << "Input: " << command << endl;
				cout << ANSI_YELLOW << "Unknow command" << ANSI_RESET << endl;
				continue;
			}
        }
    }
}
