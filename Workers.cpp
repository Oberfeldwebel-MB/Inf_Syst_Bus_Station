#include "Workers.hpp"
#include <iostream>
#include <stdexcept>


// Конструктор
Workers::Workers(const std::string& surname,
    const std::string& name,
    const std::string& fatName,
    int salary,
    bool available)
    : People(surname, name, fatName), Salary(salary), Availability(available) {

    if (salary < 0) {
        throw std::invalid_argument("Зарплата не может быть отрицательной!");
    }
}

// Конструктор копирования
Workers::Workers(const Workers& other)
    : People(other), Salary(other.Salary), Availability(other.Availability) {;
}

void Workers::change_work_avail(bool avail) {
    try {
        Availability = avail;
        std::cout << "[Workers] Доступность изменена на: "
            << (Availability ? "Доступен" : "Не доступен") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка изменения доступности: " << e.what() << std::endl;
        throw;
    }
}

void Workers::MakeSalary(int newSalary) {
    try {
        if (newSalary < 0) {
            throw std::invalid_argument("Зарплата не может быть отрицательной!");
        }

        Salary = newSalary;
        std::cout << "[Workers] Зарплата установлена: " << Salary << " руб." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка установки зарплаты: " << e.what() << std::endl;
        throw;
    }
}

bool Workers::GetAvailability() const {
    return Availability;
}