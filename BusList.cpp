#include "BusList.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>




void BusList::AddBus(std::shared_ptr<Bus> bus) {
    try {
        if (!bus) {
            throw std::invalid_argument("Нельзя добавить пустой указатель на автобус!");
        }

        // Проверка нет ли уже автобуса с таким кодом
        for (const auto& existingBus : buses) {
            if (existingBus->GetCode() == bus->GetCode()) {
                throw std::runtime_error("Автобус с кодом '" + bus->GetCode() + "' уже существует!");
            }
        }

        buses.push_back(bus);
        std::cout << "[BusList] Автобус " << bus->GetCode() << " добавлен в список\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка добавления автобуса: " << e.what() << "\n";
        throw;
    }
}

bool BusList::RemoveBus(const std::string& code) {
    try {
        if (code.empty()) {
            throw std::invalid_argument("Код автобуса не может быть пустым!");
        }

        for (auto it = buses.begin(); it != buses.end(); ++it) {
            if ((*it)->GetCode() == code) {
                std::cout << "[BusList] Автобус " << code << " удален\n";
                buses.erase(it);
                return true;
            }
        }

        std::cout << "[BusList] Автобус с кодом " << code << " не найден\n";
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка удаления автобуса: " << e.what() << "\n";
        return false;
    }
}

std::shared_ptr<Bus> BusList::FindBusByCode(const std::string& code) {
    try {
        if (code.empty()) {
            throw std::invalid_argument("Код автобуса не может быть пустым!");
        }

        for (auto& bus : buses) {
            if (bus->GetCode() == code) {
                return bus;
            }
        }
        return nullptr; 
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска автобуса: " << e.what() << "\n";
        return nullptr;
    }
}

void BusList::DisplayAllBuses() const {
    std::cout << "=== Список автобусов (" << buses.size() << ") ===\n";
    if (buses.empty()) {
        std::cout << "Список автобусов пуст\n";
    }
    else {
        for (const auto& bus : buses) {
            std::cout << "[" << bus->GetCode() << "] " << bus->GetBrand()
                << " " << bus->GetModel() << " (" << bus->GetPlaces() << " мест) - "
                << (bus->GetAvailability() ? "Доступен" : "Не доступен") << "\n";
        }
    }
    std::cout << "========================\n";
}


// дружественная функция, перегружающая оператор вывода
std::ostream& operator<<(std::ostream& os, const BusList& busList) {
    os << "BusList содержит " << busList.buses.size() << " автобусов:\n";
    for (const auto& bus : busList.buses) {
        os << "  - " << bus->GetBrand() << " " << bus->GetModel()
            << " [" << bus->GetCode() << "]\n";
    }
    return os;
}