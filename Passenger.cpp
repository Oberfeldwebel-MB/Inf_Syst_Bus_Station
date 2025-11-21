#include "Passenger.hpp"
#include <iostream>

void Passenger::PrintPassengerInfo() const {
    std::cout << "=== Информация о пассажире ===\n";
    std::cout << "ФИО: " << GetFullName() << "\n";
    std::cout << "Паспорт: " << PsprtSer << " " << PsprtNum << "\n";
    std::cout << "Email: " << Email << "\n";
    std::cout << "==============================\n";
}

// перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Passenger& passenger) {
    os << "Пассажир: " << passenger.GetFullName();

    if (!passenger.PsprtSer.empty() && !passenger.PsprtNum.empty()) {
        os << " (паспорт: " << passenger.PsprtSer << " " << passenger.PsprtNum << ")";
    }

    if (!passenger.Email.empty()) {
        os << " <" << passenger.Email << ">";
    }

    return os;
}