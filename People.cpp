#include "People.hpp"
#include <iostream>
#include <stdexcept>


// Конструктор
People::People(const std::string& surname,
    const std::string& name,
    const std::string& fatName,
    const std::string& psprtser,
    const std::string& psprtnum,
    const std::string& email)
    : Surname(surname), Name(name), FatName(fatName),
    PsprtSer(psprtser), PsprtNum(psprtnum), Email(email) {
}

// Конструктор копирования
People::People(const People& other)
    : Surname(other.Surname), Name(other.Name), FatName(other.FatName),
    PsprtSer(other.PsprtSer), PsprtNum(other.PsprtNum), Email(other.Email) {
}

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