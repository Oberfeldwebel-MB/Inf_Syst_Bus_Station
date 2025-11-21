#include "Admin.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"
#include "Trip.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <limits>


void Admin::ChangeBusTiming(std::shared_ptr<Timing> timing) {
    try {
        if (!timing) {
            throw std::invalid_argument("Расписание не может быть пустым!");
        }

        this->currentTiming = timing;

        std::cout << "=== УПРАВЛЕНИЕ РАСПИСАНИЕМ ===\n";
        std::cout << "Администратор: " << this->GetFullName() << "\n";
        std::cout << "1. Показать все поездки\n";
        std::cout << "2. Добавить поездку\n";
        std::cout << "3. Удалить поездку\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Неверный ввод! Ожидается число.");
        }

        std::cin.ignore();

        switch (choice) {
        case 1:
            timing->DisplayAllTrips();
            break;

        case 2: {
            std::cout << "=== ДОБАВЛЕНИЕ ПОЕЗДКИ ===\n";

            std::string start, finish;
            int price;

            std::cout << "Введите пункт отправления: ";
            std::getline(std::cin, start);
            if (start.empty()) {
                throw std::invalid_argument("Пункт отправления не может быть пустым!");
            }

            std::cout << "Введите пункт назначения: ";
            std::getline(std::cin, finish);
            if (finish.empty()) {
                throw std::invalid_argument("Пункт назначения не может быть пустым!");
            }

            std::cout << "Введите цену билета: ";
            std::cin >> price;
            if (price <= 0) {
                throw std::invalid_argument("Цена должна быть положительной!");
            }

            auto tripBus = this->ChoseBus();
            auto tripDriver = this->ChoseDriver();

            if (!tripBus || !tripDriver) {
                throw std::runtime_error("Не удалось найти автобус или водителя!");
            }

            // ИСПРАВЛЕННАЯ СТРОКА - передаем умные указатели напрямую
            auto newTrip = std::make_shared<Trip>(start, finish, price, tripBus, tripDriver);
            timing->AddTrip(newTrip);

            std::cout << "Поездка добавлена!\n";
            break;
        }

        case 3: {
            std::cout << "=== УДАЛЕНИЕ ПОЕЗДКИ ===\n";
            timing->DisplayAllTrips();

            if (timing->GetTripList().empty()) {
                std::cout << "Нет поездок для удаления!\n";
                break;
            }

            std::string route;
            std::cout << "Введите маршрут поездки для удаления: ";
            std::getline(std::cin, route);

            if (route.empty()) {
                std::cout << "Маршрут не может быть пустым!\n";
            }
            else {
                timing->RemoveTrip(route);
            }
            break;
        }

        case 0:
            std::cout << "Выход из управления расписанием\n";
            break;

        default:
            std::cout << "Неверный выбор!\n";
            break;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка выполнения: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << "\n";
    }
}

std::shared_ptr<Bus> Admin::ChoseBus() {
    try {
        std::string SelectedCodeBus;
        BusList busList;
        busList.DisplayAllBuses();

        if (busList.GetBuses().empty()) {
            throw std::runtime_error("Список автобусов пуст!");
        }

        std::cout << "Введите код автобуса: ";
        std::cin >> SelectedCodeBus;

        // Теперь используем модернизированный метод
        std::shared_ptr<Bus> foundBus = busList.FindBusByCode(SelectedCodeBus);
        if (foundBus) {
            std::cout << "Найден автобус: " << foundBus->GetBrand()
                << " " << foundBus->GetModel() << "\n";
            return foundBus; // Просто возвращаем умный указатель
        }
        else {
            throw std::runtime_error("Автобус с кодом '" + SelectedCodeBus + "' не найден!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка выбора автобуса: " << e.what() << "\n";
        return nullptr;
    }
}

std::shared_ptr<Driver> Admin::ChoseDriver() {
    try {
        std::string SelectedDriverName;
        DriverList driverList;
        driverList.DisplayAllDrivers();

        if (driverList.GetDrivers().empty()) {
            throw std::runtime_error("Список водителей пуст!");
        }

        std::cout << "Введите ФИО водителя: ";
        std::cin.ignore();
        std::getline(std::cin, SelectedDriverName);

        std::shared_ptr<Driver> foundDriver = driverList.FindDriverByName(SelectedDriverName);
        if (foundDriver) {
            std::cout << "Найден водитель: " << foundDriver->GetFullName()
                << " (Права: " << foundDriver->GetLicense() << ")\n";
            return foundDriver;
        }
        else {
            throw std::runtime_error("Водитель '" + SelectedDriverName + "' не найден!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка выбора водителя: " << e.what() << "\n";
        return nullptr;
    }
