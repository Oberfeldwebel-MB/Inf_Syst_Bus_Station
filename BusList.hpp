#pragma once
#include <vector>
#include <memory>
#include "Bus.hpp"
#include "SystemContainer.hpp"
#include <iostream>

class BusList {
private:
    SystemContainer<Bus> container;

public:
    BusList() = default;
    ~BusList() = default;

    // Конструктор копирования 
    BusList(const BusList& other) : container(other.container) {}

    // Два варианта геттера
    const std::vector<std::shared_ptr<Bus>>& GetBuses() const {
        return container.getAll();
    }

    std::vector<std::shared_ptr<Bus>>& GetBuses() {
        return container.getAllMutable();
    }

    void AddBus(std::shared_ptr<Bus> bus) {
        container.add(bus);
        std::cout << "[BusList] Автобус " << bus->GetCode() << " добавлен в список\n";
    }

    bool RemoveBus(const std::string& code) {
        bool result = container.remove(code);
        if (result) {
            std::cout << "[BusList] Автобус " << code << " удален\n";
        }
        else {
            std::cout << "[BusList] Автобус с кодом " << code << " не найден\n";
        }
        return result;
    }

    std::shared_ptr<Bus> FindBusByCode(const std::string& code) {
        return container.findById(code);
    }

    void DisplayAllBuses() const {
        std::cout << "=== Список автобусов (" << container.size() << ") ===\n";

        auto allBuses = container.getAll();
        if (allBuses.empty()) {
            std::cout << "Список автобусов пуст\n";
        }
        else {
            for (const auto& bus : allBuses) {
                std::cout << "[" << bus->GetCode() << "] " << bus->GetBrand()
                    << " " << bus->GetModel() << " (" << bus->GetPlaces() << " мест) - "
                    << (bus->GetAvailability() ? "Доступен" : "Не доступен") << "\n";
            }
        }
        std::cout << "========================\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const BusList& busList) {
        os << "BusList содержит " << busList.container.size() << " автобусов:\n";
        auto allBuses = busList.container.getAll();
        for (const auto& bus : allBuses) {
            os << "  - " << bus->GetBrand() << " " << bus->GetModel()
                << " [" << bus->GetCode() << "]\n";
        }
        return os;
    }
};