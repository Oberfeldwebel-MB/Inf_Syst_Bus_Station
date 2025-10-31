#include "People.hpp"
#include <iostream>

void People::PrintInfo() const {
	std::cout << "[People] ФИО: " << Surname << " " << Name << " " << FatName
		<< "\nПаспорт: " << PsprtSer << " " << PsprtNum
		<< "\nEmail: " << Email << "\n";
}
std::string People::GetFullName() const {
		return Surname + " " + Name + " " + FatName;
}
