#include "Workers.h"
#include <iostream> 

void Workers::change_work_avail(bool avail) {
	Availability = avail;
	std::cout << "[Workers] Доступность изменена на: " << (Availability ? "Доступен" : "Не доступен") << std::endl;
}

void Workers::Make_Salary(int newSalary) {
	Salary = newSalary;
	std::cout << "[Workers] Зарплата установлена: " << Salary << " руб." << std::endl;
}

bool Workers::GetAvailability() const{
	return Availability;
}
