#pragma once
#include <iostream>
#include <string>

using namespace std;

class GetPthNm
{
private:
	string p;
	string n;

public:
	GetPthNm();
	~GetPthNm();

	string Get(const string typeMove);
	string CreateFile(const string p);
};
