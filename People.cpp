#include "People.h"
#include <iostream>

void People::PrintInfo() const {
	std::cout << "[People] ФИО: " << Surname << " " << Name << " " << Fat_name
		<< "\nПаспорт: " << Psprt_ser << " " << Psprt_num
		<< "\nEmail: " << Email << "\n";
}
std::string People::GetFullName() const {
		return Surname + " " + Name + " " + Fat_name;
}
