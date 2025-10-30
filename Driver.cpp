#include "Driver.h"
#include <iostream>

bool Driver::Check_need_med(const std::string& current_date) {
	if (Last_med != current_date) {
		std::cout << "Медосмотр требуется. Последний: " << Last_med << ", дата: " << current_date << "\n";
		return true;
	}
	std::cout << "Медосмотр не требуется.\n";
	return false;
}

void Driver::Set_trip(const std::string& trip) {
	Current_trip = trip;
	std::cout << "Водителю установлен рейс: " << trip << "\n";
}



