#include "Passenger.hpp"
#include <iostream>

void Passenger::PrintPassengerInfo() const {
    std::cout << "=== Информация о пассажире ===\n";
    std::cout << "ФИО: " << GetFullName() << "\n";
    std::cout << "Паспорт: " << PsprtSer << " " << PsprtNum << "\n";
    std::cout << "Email: " << Email << "\n";
    std::cout << "==============================\n";
}