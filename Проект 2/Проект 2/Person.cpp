#include <string>
#include <Person.h>

Person::Person(string firstName, string secondName, string surName, int age) {
	this->firstName = firstName;
	this->secondName = secondName;
	this->surName = surName;
}

void Person::print() {
	cout << "���" << this->firstName << '\n'
		<< "�������" << this->secondName << '\n'
		<< "��������" << this->surName << '\n'
		<< "���������" << this->age << '\n' << endl;
}