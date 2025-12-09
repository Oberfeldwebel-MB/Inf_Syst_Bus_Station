#include "Admin.hpp"
#include "BusList.hpp"
#include "DriversList.hpp"
#include "Trip.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <limits>


// Перегрузка оператора присваивания
Admin& Admin::operator=(const Workers& other) {
    if (this != &other) {
        SetSurname(other.GetSurname());
        SetName(other.GetName());
        SetFatName(other.GetFatName());
        SetSalary(other.GetSalary());

        if (const Admin* adminPtr = dynamic_cast<const Admin*>(&other)) {
            for (int i = 0; i < 3; i++) {
                this->adminLogs[i] = adminPtr->adminLogs[i];
            }
            this->currentTiming = adminPtr->currentTiming;
        }
        else {
            for (int i = 0; i < 3; i++) {
                this->adminLogs[i] = "По умолчанию";
            }
        }
    }
    return *this;
}

// переопределение виртуальных функций без вызова базового класса
void Admin::SetAvailable() {
    std::cout << "Администратор " << GetFullName() << " доступен для управления расписанием" << std::endl;
}

void Admin::SetUnavailable(const std::string& reason) {
    std::cout << "Администратор " << GetFullName() << " недоступен";
    if (!reason.empty()) {
        std::cout << " (Причина: " << reason << ")";
    }
    std::cout << std::endl;
}

// Перегрузка метода с вызовом базового класса
void Admin::PrintInfo() const {
    Workers::PrintInfo();
    std::cout << "Должность: Администратор" << std::endl;
    if (currentTiming) {
        std::cout << "Управляет расписанием: Да" << std::endl;
    }
    else {
        std::cout << "Управляет расписанием: Нет" << std::endl;
    }
}

// Перегрузка метода без вызова базового класса
std::string Admin::GetFullInfo() const {
    return "Администратор: " + GetFullName() +
        " | Статус: " + (GetAvailability() ? "Управляет" : "Отсутствует");
}

// Переопределение абстрактного метода
double Admin::CalculateDiscount() const {
    return 0.2;
}

// Виртуальные функции
void Admin::ManageSchedule() {
    std::cout << "Администратор " << GetFullName() << " управляет расписанием рейсов" << std::endl;
    if (currentTiming) {
        std::cout << "Активное расписание: " << currentTiming->GetTripList().size() << " рейсов" << std::endl;
    }
}

// Перегрузка метода с вызовом базового класса
void Admin::SetPersonalData(int data) {
    Workers::SetPersonalData(data);
    std::cout << "Данные администратора защищены" << std::endl;
}

// поверхностное клонирование
People* Admin::Clone() const {
    Admin* newAdmin = new Admin(GetSurname(), GetName(), GetFatName(), GetSalary());

    // Копируем текущее расписание (shared_ptr сам управляет копированием)
    newAdmin->currentTiming = this->currentTiming;

    // Копируем логи (std::array копируется полностью)
    newAdmin->adminLogs = this->adminLogs;

    return newAdmin;  // Возвращаем People* (Admin* автоматически преобразуется)
}

// Оригинальные методы класса Admin
void Admin::ChangeBusTiming(std::shared_ptr<Timing> timing) {
    try {
        if (!timing) {
            throw std::invalid_argument("Расписание не может быть пустым!");
        }

        this->currentTiming = timing;

        std::cout << "=== УПРАВЛЕНИЕ РАСПИСАНИЕМ ===" << std::endl;
        std::cout << "Администратор: " << this->GetFullName() << std::endl;
        std::cout << "1. Показать все поездки" << std::endl;
        std::cout << "2. Добавить поездку" << std::endl;
        std::cout << "3. Удалить поездку" << std::endl;
        std::cout << "0. Выход" << std::endl;
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
            std::cout << "=== ДОБАВЛЕНИЕ ПОЕЗДКИ ===" << std::endl;

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

            auto newTrip = std::make_shared<Trip>(start, finish, price, tripBus, tripDriver);
            timing->AddTrip(newTrip);

            std::cout << "Поездка добавлена!" << std::endl;
            break;
        }

        case 3: {
            std::cout << "=== УДАЛЕНИЕ ПОЕЗДКИ ===" << std::endl;
            timing->DisplayAllTrips();

            if (timing->GetTripList().empty()) {
                std::cout << "Нет поездок для удаления!" << std::endl;
                break;
            }

            std::string route;
            std::cout << "Введите маршрут поездки для удаления: ";
            std::getline(std::cin, route);

            if (route.empty()) {
                std::cout << "Маршрут не может быть пустым!" << std::endl;
            }
            else {
                timing->RemoveTrip(route);
            }
            break;
        }

        case 0:
            std::cout << "Выход из управления расписанием" << std::endl;
            break;

        default:
            std::cout << "Неверный выбор!" << std::endl;
            break;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка выполнения: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
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

        std::shared_ptr<Bus> foundBus = busList.FindBusByCode(SelectedCodeBus);
        if (foundBus) {
            std::cout << "Найден автобус: " << foundBus->GetBrand()
                << " " << foundBus->GetModel() << std::endl;
            return foundBus;
        }
        else {
            throw std::runtime_error("Автобус с кодом '" + SelectedCodeBus + "' не найден!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка выбора автобуса: " << e.what() << std::endl;
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
                << " (Права: " << foundDriver->GetLicense() << ")" << std::endl;
            return foundDriver;
        }
        else {
            throw std::runtime_error("Водитель '" + SelectedDriverName + "' не найден!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка выбора водителя: " << e.what() << std::endl;
        return nullptr;
    }
}