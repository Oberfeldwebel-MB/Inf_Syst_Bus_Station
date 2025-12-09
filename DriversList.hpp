#pragma once
#include <vector>
#include <memory>
#include "Driver.hpp"
#include "SystemContainer.hpp"  // ДОБАВИЛИ

class DriverList {
private:
    SystemContainer<Driver> container;  // ЗАМЕНИЛИ std::vector на SystemContainer

public:
    DriverList() = default;
    ~DriverList() = default;

    // Конструктор копирования 
    DriverList(const DriverList& other) : container(other.container) {}

    // Константная версия (для чтения)
    const std::vector<std::shared_ptr<Driver>>& GetDrivers() const {
        return container.getAll();
    }

    // Неконстантная версия (для модификации)
    std::vector<std::shared_ptr<Driver>>& GetDrivers() {
        return container.getAllMutable();
    }

    void AddDriver(std::shared_ptr<Driver> driver) {
        container.add(driver);  // Используем SystemContainer
        std::cout << "[DriverList] Водитель " << driver->GetFullName() << " добавлен в список\n";
    }

    std::shared_ptr<Driver> FindDriverByName(const std::string& fullName) {
        // Ищем через SystemContainer.findByText
        return container.findByText(fullName);
    }

    bool RemoveDriver(const std::string& fullName) {
        // Находим водителя по имени
        auto driver = FindDriverByName(fullName);
        if (driver) {
            return container.remove(driver->getId());  // Удаляем по ID
        }
        return false;
    }

    void DisplayAllDrivers() const {
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
    friend std::ostream& operator<<(std::ostream& os, const DriverList& driverList) {
        os << "DriverList содержит " << driverList.container.size() << " водителей:\n";
        auto allDrivers = driverList.container.getAll();
        for (const auto& driver : allDrivers) {
            os << "  - " << driver->GetFullName()
                << " (Права: " << driver->GetLicense() << ")\n";
        }
        return os;
    }

    // Дружественная функция для поиска доступных водителей
    friend std::vector<std::shared_ptr<Driver>> FindAvailableDrivers(const DriverList& list) {
        std::vector<std::shared_ptr<Driver>> availableDrivers;
        auto allDrivers = list.container.getAll();

        for (const auto& driver : allDrivers) {
            if (driver->GetAvailability()) {
                availableDrivers.push_back(driver);
            }
        }
        return availableDrivers;
    }
};