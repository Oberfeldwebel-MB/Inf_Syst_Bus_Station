#include "People.hpp"
#include <iostream>
#include <stdexcept>

void People::PrintInfo() const {
    std::cout << "=== Информация о человеке ===\n";
    std::cout << "ФИО: " << Surname << " " << Name << " " << FatName << "\n";
    std::cout << "Паспорт: " << PsprtSer << " " << PsprtNum << "\n";
    std::cout << "Email: " << Email << "\n";
    std::cout << "=============================\n";
}

std::string People::GetFullName() const {
    return Surname + " " + Name + " " + FatName;
}

// перегрузка оператора для вывода
std::ostream& operator<<(std::ostream& os, const People& person) {
    os << person.Surname << " " << person.Name << " " << person.FatName;

    if (!person.PsprtSer.empty() && !person.PsprtNum.empty()) {
        os << " [" << person.PsprtSer << " " << person.PsprtNum << "]";
    }

    return os;
}