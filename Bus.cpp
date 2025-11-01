#include "Bus.hpp"
#include <iostream>

void Bus::PrintBusInfo() {
	std::cout << "=== Данные автобуса ===\n";
	std::cout << "Марка: " << Brand << "\n";
	std::cout << "Модель: " << Model << "\n";
	std::cout << "Количество мест: " << PlaceCount << "\n";
	std::cout << "Код автобуса: " << CodeBus << "\n";
	std::cout << "Техническое состояние: " << TechSost << "\n";
	std::cout << "Последнее ТО: " << LastCheckTO << "\n";
	std::cout << "Статус: " << (BusAvailability ? "Доступен" : "Не доступен") << "\n";
	std::cout << "=======================\n";
}

bool Bus::CheckAvailBus(){
	return BusAvailability;
}

void Bus::ChangeAvailBus(bool state) {
	BusAvailability = state;
	if (state) { std::cout << "Автобус теперь доступен\n"; }
	else { std::cout << "Автобус теперь недоступен\n"; }
}

void Bus::SetTripBus() {
	if (BusAvailability)
		std::cout << "Bus " << CodeBus << " assigned to a trip.\n";
	else
		std::cout << "Bus " << CodeBus << " is not available for a trip.\n";
}

void Bus::GoToTO(std::string& date) {
	LastCheckTO = date;
	TechSost = "In maintenance";
	BusAvailability = false;
	std::cout << "Bus " << CodeBus << " sent to maintenance on " << date << ".\n";
}

void Bus::Change_sost(std::string& newState) {
	TechSost = newState;
	std::cout << "Bus " << CodeBus << " technical condition updated to: " << newState << "\n";
}
