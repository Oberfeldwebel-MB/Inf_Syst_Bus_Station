#include "BusList.h"
#include <iostream>

//Добавление автобуса
void BusList::Add_Bus(const Bus& bus) {
    buses.push_back(bus);
    std::cout << "[BusList] Автобус " << bus.GetCode() << " добавлен в список\n";
}

// Удаление автобуса по коду
bool BusList::Remove_Bus(const std::string& code) {
    for (size_t i = 0; i < buses.size(); i++) {
        if (buses[i].GetCode() == code) {
            std::cout << "[BusList] Автобус " << code << " удален\n";
            buses.erase(buses.begin() + i);
            return true;
        }
    }
    std::cout << "[BusList] Автобус с кодом " << code << " не найден\n";
    return false;
}

// Поиск автобуса по коду
Bus* BusList::Find_Bus_By_Code(const std::string& code) {
    for (auto& bus : buses) {
        if (bus.GetCode() == code) {
            return &bus;
        }
    }
    return nullptr;
}

// Отображение всех автобусов
void BusList::Display_All_Buses() {
    std::cout << "=== Список автобусов ===\n";
    if (buses.empty()) {
        std::cout << "Список автобусов пуст\n";
    }
    else {
        for (const auto& bus : buses) {
            std::cout << "[" << bus.GetCode() << "] " << bus.GetBrand()
                << " " << bus.GetModel() << " (" << bus.GetPlaces() << " мест) - "
                << (bus.GetAvailability() ? "Доступен" : "Не доступен") << "\n";
        }
    }
    std::cout << "========================\n";
}
