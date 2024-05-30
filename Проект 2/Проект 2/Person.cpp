#include <string>
#include <Person.h>

Person::Person(string firstName, string secondName, string surName, int age) {
	this->firstName = firstName;
	this->secondName = secondName;
	this->surName = surName;
}

void Person::print() {
	cout << "Имя" << this->firstName << '\n'
		<< "Фамилия" << this->secondName << '\n'
		<< "Отчество" << this->surName << '\n'
		<< "Восзвраст" << this->age << '\n' << endl;
}