#include "DriversList.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

void DriverList::AddDriver(std::shared_ptr<Driver> driver) {
    try {
        if (!driver) {
            throw std::invalid_argument("Нельзя добавить пустой указатель на водителя!");
        }

        auto allDrivers = container.getAll();

        // Проверяем, нет ли уже водителя с таким ФИО
        std::string newDriverName = driver->GetFullName();
        for (const auto& existingDriver : allDrivers) {  
            if (existingDriver->GetFullName() == newDriverName) {
                throw std::runtime_error("Водитель '" + newDriverName + "' уже существует в списке!");
            }
        }

        container.add(driver);
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

        return container.findByText(fullName);
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

        // Находим водителя по имени
        auto driver = FindDriverByName(fullName);
        if (driver) {
            // Удаляем по ID через container
            return container.remove(driver->getId());
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
    std::cout << "=== Список водителей (" << container.size() << ") ===\n";

    auto allDrivers = container.getAll();

    if (allDrivers.empty()) {
        std::cout << "Список водителей пуст\n";
    }
    else {
        for (const auto& driver : allDrivers) {
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
    auto allDrivers = driverList.container.getAll();

    os << "DriverList содержит " << allDrivers.size() << " водителей:\n";
    for (const auto& driver : allDrivers) {
        os << "  - " << driver->GetFullName()
            << " (Права: " << driver->GetLicense() << ")\n";
    }
    return os;
}

// Дружественная функция для поиска доступных водителей
std::vector<std::shared_ptr<Driver>> FindAvailableDrivers(const DriverList& list) {
    std::vector<std::shared_ptr<Driver>> availableDrivers;

    auto allDrivers = list.container.getAll();

    for (const auto& driver : allDrivers) {
        if (driver->GetAvailability()) {
            availableDrivers.push_back(driver);
        }
    }

    return availableDrivers;
}