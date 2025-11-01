#include "DriversList.hpp"

#pragma once
#include <vector>
#include <iostream>
#include "Driver.hpp"

    void DriverList::AddDriver(const Driver& driver) {
        drivers.push_back(driver);
        std::cout << "[DriverList] Водитель " << driver.GetFullName() << " добавлен в список\n";
    }

    // Поиск водителя
    Driver* DriverList::FindDriverByName(const std::string& fullName) {
        for (auto& driver : drivers) {
            if (driver.GetFullName() == fullName) {
                return &driver;
            }
        }
        return nullptr;
    }

    // Удаление водителя
    bool DriverList::RemoveDriver(const std::string& fullName) {
        for (size_t i = 0; i < drivers.size(); i++) {
            if (drivers[i].GetFullName() == fullName) {
                std::cout << "[DriverList] Водитель " << fullName << " удален\n";
                drivers.erase(drivers.begin() + i);
                return true;
            }
        }
        return false;
    }

    //Отображение списка водителей
    void DriverList::DisplayAllDrivers() {
        std::cout << "=== Список водителей ===\n";
        for (const auto& driver : drivers) {
            driver.PrintInfo();
            std::cout << "Текущий рейс" << driver.GetDriverCurrentTrip() << "Статус: " << (driver.GetAvailability() ? "Доступен" : "Занят") << "\n";
        }
        std::cout << "========================\n";
    }
