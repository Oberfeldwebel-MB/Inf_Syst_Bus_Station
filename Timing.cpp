#include "Timing.h"
#include <iostream>
#include "Trip.h"

void Timing::Add_trip(const Trip& trip) {
    tripList.push_back(trip);
    std::cout << "Поездка добавлена в расписание: "
        << trip.GetRoute() << "\n";
}

void Timing::Display_all_trips() const {
    std::cout << "=== Все поездки (" << tripList.size() << ") ===\n";
    if (tripList.empty()) {
        std::cout << "Расписание пусто\n";
    }
    else {
        for (const auto& trip : tripList) {
            std::cout << "• " << trip.GetRoute()
                << " - " << trip.GetStatus()
                << " (" << trip.GetPrice() << " руб.)\n";
        }
    }
    std::cout << "==========================\n";
}

void Timing::Display_active_trips() const {
    std::cout << "=== Активные поездки ===\n";
    int count = 0;
    for (const auto& trip : tripList) {
        if (trip.GetStatus() == "Запланирована" || trip.GetStatus() == "В пути") {
            std::cout << "- " << trip.GetRoute()
                << " - " << trip.GetStatus() << "\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "Нет активных поездок\n";
    }
    std::cout << "==========================\n";
}

void Timing::Display_completed_trips() const {
    std::cout << "=== Завершенные поездки ===\n";
    int count = 0;
    for (const auto& trip : tripList) {
        if (trip.GetStatus() == "Завершена") {
            std::cout << "- " << trip.GetRoute()
                << " - " << trip.GetPrice() << " руб.\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "Нет завершенных поездок\n";
    }
    std::cout << "==========================\n";
}

void Timing::Display_planned_trips() const {
    std::cout << "=== Запланированные поездки ===\n";
    int count = 0;
    for (const auto& trip : tripList) {
        if (trip.GetStatus() == "Запланирована") {
            std::cout << "• " << trip.GetRoute()
                << " - " << trip.GetPrice() << " руб.\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "Нет запланированных поездок\n";
    }
    std::cout << "==========================\n";
}


Trip* Timing::Chose_trip() {
    Display_active_trips();  

    if (tripList.empty()) {
        std::cout << "Нет доступных поездок!\n";
        return nullptr;
    }

    std::string selectedRoute;
    std::cout << "Введите маршрут поездки: ";
    std::cin.ignore();
    std::getline(std::cin, selectedRoute);

    
    for (auto& trip : tripList) {
        if (trip.GetRoute() == selectedRoute &&
            (trip.GetStatus() == "Запланирована" || trip.GetStatus() == "В пути")) {
            std::cout << " Выбрана поездка: " << selectedRoute << "\n";
            return &trip;
        }
    }

    std::cout << "Активная поездка с маршрутом '" << selectedRoute << "' не найдена!\n";
    return nullptr;
}