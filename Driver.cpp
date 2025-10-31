#include "Driver.hpp"
#include <iostream>

bool Driver::CheckNeedMed(const std::string& current_date) {
	if (LastMed != current_date) {
		std::cout << "Медосмотр требуется. Последний: " << LastMed << ", дата: " << current_date << "\n";
		return true;
	}
	std::cout << "Медосмотр не требуется.\n";
	return false;
}

void Driver::SetTrip(const std::string& trip) {
	CurrentDriverTrip = trip;
	std::cout << "Водителю установлен рейс: " << trip << "\n";
}



