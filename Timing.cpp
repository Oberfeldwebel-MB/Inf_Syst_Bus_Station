#include "Timing.hpp"
#include <iostream>
#include <stdexcept>



// Конструктор копирования
Timing::Timing(const Timing& other) {
    for (const auto& trip : other.tripList) {
        // новые копии поездок
        tripList.push_back(std::make_shared<Trip>(*trip));
    }
}

void Timing::AddTrip(std::shared_ptr<Trip> trip) {
    try {
        if (!trip) {
            throw std::invalid_argument("Нельзя добавить пустую поездку!");
        }

        // Проверяем дублирование поездок
        for (const auto& existingTrip : tripList) {
            if (existingTrip->GetRoute() == trip->GetRoute() &&
                existingTrip->GetStatus() != "Завершена") {
                throw std::runtime_error("Поездка с маршрутом '" + trip->GetRoute() + "' уже существует!");
            }
        }

        tripList.push_back(trip);
        std::cout << "Поездка добавлена в расписание: " << trip->GetRoute() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка добавления поездки: " << e.what() << "\n";
        throw;
    }
}

bool Timing::RemoveTrip(const std::string& route) {
    try {
        if (route.empty()) {
            throw std::invalid_argument("Маршрут не может быть пустым!");
        }

        auto it = std::find_if(tripList.begin(), tripList.end(),
            [&route](const std::shared_ptr<Trip>& trip) {
                return trip && trip->GetRoute() == route;
            });

        if (it == tripList.end()) {
            std::cout << "Поездка с маршрутом '" << route << "' не найдена!\n";
            return false;
        }

        // Освобождаем ресурсы
        auto bus = (*it)->GetBus();
        if (bus) {
            bus->ChangeAvailBus(true);
            std::cout << "Автобус " << bus->GetCode() << " освобожден\n";
        }

        auto driver = (*it)->GetDriver();
        if (driver) {
            driver->change_work_avail(true);
            std::cout << "Водитель " << driver->GetFullName() << " освобожден\n";
        }

        // Удаляем поездку
        tripList.erase(it);
        std::cout << "Поездка '" << route << "' успешно удалена!\n";
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка удаления поездки: " << e.what() << "\n";
        return false;
    }
}

void Timing::DisplayAllTrips() const {
    std::cout << "=== Все поездки (" << tripList.size() << ") ===\n";
    if (tripList.empty()) {
        std::cout << "Расписание пусто\n";
    }
    else {
        for (const auto& trip : tripList) {
            std::cout << "• " << trip->GetRoute()
                << " - " << trip->GetStatus()
                << " (" << trip->GetPrice() << " руб.)\n";
        }
    }
    std::cout << "==========================\n";
}

void Timing::DisplayActiveTrips() const {
    std::cout << "=== Активные поездки ===\n";
    int count = 0;
    for (const auto& trip : tripList) {
        if (trip->GetStatus() == "Запланирована" || trip->GetStatus() == "В пути") {
            std::cout << "- " << trip->GetRoute()
                << " - " << trip->GetStatus() << "\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "Нет активных поездок\n";
    }
    std::cout << "==========================\n";
}

void Timing::DisplayCompletedTrips() const {
    std::cout << "=== Завершенные поездки ===\n";
    int count = 0;
    for (const auto& trip : tripList) {
        if (trip->GetStatus() == "Завершена") {
            std::cout << "- " << trip->GetRoute()
                << " - " << trip->GetPrice() << " руб.\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "Нет завершенных поездок\n";
    }
    std::cout << "==========================\n";
}

void Timing::DisplayPlannedTrips() const {
    std::cout << "=== Запланированные поездки ===\n";
    int count = 0;
    for (const auto& trip : tripList) {
        if (trip->GetStatus() == "Запланирована") {
            std::cout << "• " << trip->GetRoute()
                << " - " << trip->GetPrice() << " руб.\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "Нет запланированных поездок\n";
    }
    std::cout << "==========================\n";
}

std::shared_ptr<Trip> Timing::ChoseTrip() {
    try {
        DisplayActiveTrips();

        if (tripList.empty()) {
            throw std::runtime_error("Нет доступных поездок!");
        }

        std::string selectedRoute;
        std::cout << "Введите маршрут поездки: ";
        std::cin.ignore();
        std::getline(std::cin, selectedRoute);

        if (selectedRoute.empty()) {
            throw std::invalid_argument("Маршрут не может быть пустым!");
        }

        for (auto& trip : tripList) {
            if (trip->GetRoute() == selectedRoute &&
                (trip->GetStatus() == "Запланирована" || trip->GetStatus() == "В пути")) {
                std::cout << "Выбрана поездка: " << selectedRoute << "\n";
                return trip;  // Возвращаем умный указатель
            }
        }

        throw std::runtime_error("Активная поездка с маршрутом '" + selectedRoute + "' не найдена!");
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка выбора поездки: " << e.what() << "\n";
        return nullptr;
    }
}