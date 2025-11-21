#include "DriversList.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

void DriverList::AddDriver(std::shared_ptr<Driver> driver) {
    try {
        if (!driver) {
            throw std::invalid_argument("Нельзя добавить пустой указатель на водителя!");
        }

        // Проверяем, нет ли уже водителя с таким ФИО
        std::string newDriverName = driver->GetFullName();
        for (const auto& existingDriver : drivers) {
            if (existingDriver->GetFullName() == newDriverName) {
                throw std::runtime_error("Водитель '" + newDriverName + "' уже существует в списке!");
            }
        }

        drivers.push_back(driver);
        std::cout << "[DriverList] Водитель " << driver->GetFullName() << " добавлен в список\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка добавления водителя: " << e.what() << "\n";
        throw;
    }
}

std::shared_ptr<Driver> DriverList::FindDriverByName(const std::string& fullName) {
    try {
        if (fullName.empty()) {
            throw std::invalid_argument("ФИО водителя не может быть пустым!");
        }

        for (auto& driver : drivers) {
            if (driver->GetFullName() == fullName) {
                return driver; // Просто возвращаем умный указатель
            }
        }
        return nullptr; // Возвращаем пустой умный указатель
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска водителя: " << e.what() << "\n";
        return nullptr;
    }
}

bool DriverList::RemoveDriver(const std::string& fullName) {
    try {
        if (fullName.empty()) {
            throw std::invalid_argument("ФИО водителя не может быть пустым!");
        }

        for (auto it = drivers.begin(); it != drivers.end(); ++it) {
            if ((*it)->GetFullName() == fullName) {
                std::cout << "[DriverList] Водитель " << fullName << " удален\n";
                drivers.erase(it);
                return true;
            }
        }

        std::cout << "[DriverList] Водитель '" << fullName << "' не найден\n";
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка удаления водителя: " << e.what() << "\n";
        return false;
    }
}

void DriverList::DisplayAllDrivers() const {
    std::cout << "=== Список водителей (" << drivers.size() << ") ===\n";
    if (drivers.empty()) {
        std::cout << "Список водителей пуст\n";
    }
    else {
        for (const auto& driver : drivers) {
            driver->PrintInfo();
            std::cout << "Текущий рейс: " << driver->GetDriverCurrentTrip()
                << ", Статус: " << (driver->GetAvailability() ? "Доступен" : "Занят") << "\n";
            std::cout << "----------------------------\n";
        }
    }
    std::cout << "========================\n";
}


// Дружественная функция перегрузки оператора вывода
std::ostream& operator<<(std::ostream& os, const DriverList& driverList) {
    os << "DriverList содержит " << driverList.drivers.size() << " водителей:\n";
    for (const auto& driver : driverList.drivers) {
        os << "  - " << driver->GetFullName()
            << " (Права: " << driver->GetLicense() << ")\n";
    }
    return os;
}

// Дружественная функция для поиска доступных водителей
std::vector<std::shared_ptr<Driver>> FindAvailableDrivers(const DriverList& list) {
    std::vector<std::shared_ptr<Driver>> availableDrivers;

    for (const auto& driver : list.drivers) {
        if (driver->GetAvailability()) {
            availableDrivers.push_back(driver);
        }
    }

    return availableDrivers;
}