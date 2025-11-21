#include "Workers.hpp"
#include <iostream>
#include <stdexcept>

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