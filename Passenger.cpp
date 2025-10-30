#include "Passenger.h"
#include <iostream>

void Passenger::PrintPassengerInfo() const {
    std::cout << "=== Информация о пассажире ===\n";
    std::cout << "ФИО: " << GetFullName() << "\n";
    std::cout << "Паспорт: " << Psprt_ser << " " << Psprt_num << "\n";
    std::cout << "Email: " << Email << "\n";
    std::cout << "==============================\n";
}