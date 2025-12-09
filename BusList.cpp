#include "BusList.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

void BusList::AddBus(std::shared_ptr<Bus> bus) {
    try {
        if (!bus) {
            throw std::invalid_argument("Нельзя добавить пустой указатель на автобус!");
        }

        auto allBuses = container.getAll(); // Получаем все автобусы из контейнера

        // Проверка нет ли уже автобуса с таким кодом
        for (const auto& existingBus : allBuses) { 
            if (existingBus->GetCode() == bus->GetCode()) {
                throw std::runtime_error("Автобус с кодом '" + bus->GetCode() + "' уже существует!");
            }
        }

        container.add(bus); 
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

        bool result = container.remove(code);

        if (result) {
            std::cout << "[BusList] Автобус " << code << " удален\n";
        }
        else {
            std::cout << "[BusList] Автобус с кодом " << code << " не найден\n";
        }

        return result;
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
        return container.findById(code);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка поиска автобуса: " << e.what() << "\n";
        return nullptr;
    }
}

void BusList::DisplayAllBuses() const {
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

// Дружественная функция перегрузки оператора вывода
std::ostream& operator<<(std::ostream& os, const BusList& busList) {
    auto allBuses = busList.container.getAll();

    os << "BusList содержит " << allBuses.size() << " автобусов:\n";
    for (const auto& bus : allBuses) {
        os << "  - " << bus->GetBrand() << " " << bus->GetModel()
            << " [" << bus->GetCode() << "]\n";
    }
    return os;
}