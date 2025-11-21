#include "Driver.hpp"
#include <iostream>
#include <stdexcept>

bool Driver::CheckNeedMed(const std::string& current_date) {
    try {
        if (current_date.empty()) {
            throw std::invalid_argument("Дата проверки не может быть пустой!");
        }

        if (LastMed != current_date) {
            std::cout << "Медосмотр требуется. Последний: " << LastMed
                << ", текущая дата: " << current_date << "\n";
            return true;
        }
        std::cout << "Медосмотр не требуется.\n";
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка проверки медосмотра: " << e.what() << "\n";
        throw;
    }
}

void Driver::SetTrip(const std::string& trip) {
    try {
        if (trip.empty()) {
            throw std::invalid_argument("Название рейса не может быть пустым!");
        }

        CurrentDriverTrip = trip;
        change_work_avail(false);  // Делаем водителя занятым
        std::cout << "Водителю " << GetFullName() << " установлен рейс: " << trip << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка установки рейса: " << e.what() << "\n";
        throw;
    }
}

void Driver::PrintDriverInfo() const {
    std::cout << "=== Информация о водителе ===\n";
    std::cout << "ФИО: " << GetFullName() << "\n";
    std::cout << "Права: " << DriverLicense << "\n";
    std::cout << "Последний медосмотр: " << LastMed << "\n";
    std::cout << "Текущий рейс: " << CurrentDriverTrip << "\n";
    std::cout << "Статус: " << (GetAvailability() ? "Доступен" : "Занят") << "\n";
    std::cout << "=============================\n";
}

// перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Driver& driver) {
    os << "Водитель: " << driver.GetFullName()
        << " (" << driver.DriverLicense << ") - "
        << (driver.GetAvailability() ? "Свободен" : "Занят в рейсе");

    if (!driver.CurrentDriverTrip.empty()) {
        os << " [" << driver.CurrentDriverTrip << "]";
    }

    return os;
}