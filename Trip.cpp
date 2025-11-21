#include "Trip.hpp"
#include <iostream>
#include <stdexcept>


void Trip::Start_trip() {
    try {
        if (!BusData) {
            throw std::runtime_error("Не назначен автобус для поездки!");
        }
        if (!DriverData) {
            throw std::runtime_error("Не назначен водитель для поездки!");
        }

        StatusTrip = "В пути";
        std::cout << "Поездка началась: " << StartPoint << " - " << FinishPoint << "\n";
        std::cout << "Водитель: " << DriverData->GetFullName() << "\n";
        std::cout << "Автобус: " << BusData->GetBrand() << " [" << BusData->GetCode() << "]\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка начала поездки: " << e.what() << "\n";
        throw;
    }
}

void Trip::Complete_trip() {
    try {
        if (StatusTrip != "В пути") {
            throw std::runtime_error("Можно завершить только поездку в пути!");
        }

        StatusTrip = "Завершена";
        std::cout << "Поездка завершена: " << StartPoint << " - " << FinishPoint << "\n";

        // Освобождаем автобус
        if (BusData) {
            BusData->ChangeAvailBus(true);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка завершения поездки: " << e.what() << "\n";
        throw;
    }
}

void Trip::Cancel_trip() {
    try {
        if (StatusTrip == "Завершена") {
            throw std::runtime_error("Нельзя отменить завершенную поездку!");
        }

        StatusTrip = "Отменена";
        std::cout << "Поездка отменена: " << StartPoint << " - " << FinishPoint << "\n";

        // Освобождаем ресурсы
        if (BusData) {
            BusData->ChangeAvailBus(true);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка отмены поездки: " << e.what() << "\n";
        throw;
    }
}

void Trip::Print_trip_info() const {
    std::cout << "=== Информация о поездке ===\n";
    std::cout << "Маршрут: " << StartPoint << " → " << FinishPoint << "\n";
    std::cout << "Статус: " << StatusTrip << "\n";
    std::cout << "Цена билета: " << PriceTicket << " руб.\n";

    if (BusData) {
        std::cout << "Автобус: " << BusData->GetBrand() << " [" << BusData->GetCode() << "]\n";
    }
    else {
        std::cout << "Автобус: не назначен\n";
    }

    if (DriverData) {
        std::cout << "Водитель: " << DriverData->GetFullName() << "\n";
    }
    else {
        std::cout << "Водитель: не назначен\n";
    }
    std::cout << "=============================\n";
}

void Trip::Change_driver(DriverList& driverList) {  // Исправлено название
    try {
        // Список доступных водителей
        std::cout << "=== Доступные водители ===\n";

        bool foundAvailable = false;
        const auto& drivers = driverList.GetDrivers();
        for (const auto& driver : drivers) {
            if (driver->GetAvailability()) {
                std::cout << "• " << driver->GetFullName()
                    << " (Права: " << driver->GetLicense() << ")\n";
                foundAvailable = true;
            }
        }

        if (!foundAvailable) {
            throw std::runtime_error("Нет доступных водителей!");
        }

        std::string selectedName;
        std::cout << "Введите ФИО водителя: ";
        std::getline(std::cin, selectedName);

        if (selectedName.empty()) {
            throw std::invalid_argument("ФИО водителя не может быть пустым!");
        }

        // Поиск и установка водителя
        std::shared_ptr<Driver> foundDriver = driverList.FindDriverByName(selectedName);
        if (foundDriver && foundDriver->GetAvailability()) {

            DriverData = foundDriver;
            std::cout << "Водитель изменен на: " << foundDriver->GetFullName() << "\n";
        }
        else {
            throw std::runtime_error("Водитель не найден или недоступен!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка смены водителя: " << e.what() << "\n";
        throw;
    }
}

void Trip::Change_bus(BusList& busList) {
    try {
        // Список доступных автобусов
        std::cout << "=== Доступные автобусы ===\n";

        bool foundAvailable = false;
        const auto& buses = busList.GetBuses();
        for (const auto& bus : buses) {
            if (bus->GetAvailability()) {
                std::cout << "• [" << bus->GetCode() << "] " << bus->GetBrand()
                    << " " << bus->GetModel() << " (" << bus->GetPlaces() << " мест)\n";
                foundAvailable = true;
            }
        }

        if (!foundAvailable) {
            throw std::runtime_error("Нет доступных автобусов!");
        }

        // Выбор автобуса
        std::string selectedCode;
        std::cout << "Введите код автобуса: ";
        std::cin >> selectedCode;

        if (selectedCode.empty()) {
            throw std::invalid_argument("Код автобуса не может быть пустым!");
        }

        // Поиск и установка автобуса
        std::shared_ptr<Bus> foundBus = busList.FindBusByCode(selectedCode);
        if (foundBus && foundBus->GetAvailability()) {
            // Освобождаем предыдущий автобус
            if (BusData) {
                BusData->ChangeAvailBus(true);
            }

            BusData = foundBus;
            foundBus->ChangeAvailBus(false);  // Занимаем новый автобус
            std::cout << "Автобус изменен на: " << foundBus->GetBrand()
                << " [" << foundBus->GetCode() << "]\n";
        }
        else {
            throw std::runtime_error("Автобус не найден или недоступен!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка смены автобуса: " << e.what() << "\n";
        throw;
    }
}

// перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Trip& trip) {
    os << "Поездка: " << trip.GetRoute();
    os << " [" << trip.GetStatus() << "]"; 
    os << " - " << trip.GetPrice() << " руб."; 

    auto bus = trip.GetBus();
    if (bus) {
        os << " (" << bus->GetBrand() << ")";
    }

    return os;
}