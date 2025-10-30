#include "Bus.h"
#include <iostream>

void Bus::Print_Bus_info() {
	std::cout << "=== Данные автобуса ===\n";
	std::cout << "Марка: " << Brand << "\n";
	std::cout << "Модель: " << Model << "\n";
	std::cout << "Количество мест: " << Place_count << "\n";
	std::cout << "Код автобуса: " << Code_bus << "\n";
	std::cout << "Техническое состояние: " << Tech_sost << "\n";
	std::cout << "Последнее ТО: " << Last_check_TO << "\n";
	std::cout << "Статус: " << (Bus_availability ? "Доступен" : "Не доступен") << "\n";
	std::cout << "=======================\n";
}

bool Bus::Check_avail_bus(){
	return Bus_availability;
}

void Bus::Change_avail_bus(bool state) {
	Bus_availability = state;
	if (state) { std::cout << "Автобус теперь доступен\n"; }
	else { std::cout << "Автобус теперь недоступен\n"; }
}

void Bus::Set_trip_bus() {
	if (Bus_availability)
		std::cout << "Bus " << Code_bus << " assigned to a trip.\n";
	else
		std::cout << "Bus " << Code_bus << " is not available for a trip.\n";
}

void Bus::Go_to_TO(std::string& date) {
	Last_check_TO = date;
	Tech_sost = "In maintenance";
	Bus_availability = false;
	std::cout << "Bus " << Code_bus << " sent to maintenance on " << date << ".\n";
}

void Bus::Change_sost(std::string& newState) {
	Tech_sost = newState;
	std::cout << "Bus " << Code_bus << " technical condition updated to: " << newState << "\n";
}
