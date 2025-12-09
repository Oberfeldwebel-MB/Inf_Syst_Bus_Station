#include "Driver.hpp"
#include <iostream>
#include <stdexcept>

// Перегрузка оператора присваивания(требование 8)
Driver& Driver::operator=(const Driver& other) {
    if (this != &other) {
        Workers::operator=(other); // Контролируемое копирование
        DriverLicense = other.DriverLicense; // Безопасно
        LastMed = other.LastMed; // Безопасно  
        CurrentDriverTrip = other.CurrentDriverTrip; // Безопасно

        // ГЛУБОКОЕ копирование массива - под нашим контролем!
        for (int i = 0; i < 5; i++) {
            drivenRoutes[i] = other.drivenRoutes[i];
        }
    }
    return *this;
}

// ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ ФУНКЦИЙ с вызовом базового класса
void Driver::SetAvailable() {
    Workers::SetAvailable(); // Вызов базовой реализации
    std::cout << "Водитель " << GetFullName() << " готов к рейсам" << std::endl;
    std::cout << "Права категории: " << DriverLicense << std::endl;
}

void Driver::SetUnavailable(const std::string& reason) {
    Workers::SetUnavailable(reason); // Вызов базовой реализации
    std::cout << "Водительские права: " << DriverLicense << std::endl;
    if (reason == "На рейсе" && !CurrentDriverTrip.empty()) {
        std::cout << "Текущий рейс: " << CurrentDriverTrip << std::endl;
    }
}

// Перегрузка метода с вызовом базового класса
void Driver::PrintInfo() const {
    Workers::PrintInfo(); // Вызов метода базового класса
    std::cout << "Категория прав: " << DriverLicense << std::endl;
    std::cout << "Последний медосмотр: " << LastMed << std::endl;
    if (!CurrentDriverTrip.empty()) {
        std::cout << "Текущий рейс: " << CurrentDriverTrip << std::endl;
    }
}

// Перегрузка метода без вызова базового класса
std::string Driver::GetFullInfo() const {
    return "Водитель: " + GetFullName() +
        " | Права: " + DriverLicense +
        " | Рейс: " + (CurrentDriverTrip.empty() ? "Нет" : CurrentDriverTrip);
}

// Переопределение абстрактного метода
double Driver::CalculateDiscount() const {
    return 0.15; // 15% скидка для водителей
}

// Виртуальные функции
void Driver::DriveBus() {
    std::cout << "Водитель " << GetFullName() << " управляет автобусом" << std::endl;
    if (!CurrentDriverTrip.empty()) {
        std::cout << "На маршруте: " << CurrentDriverTrip << std::endl;
    }
}

void Driver::PerformMaintenance() {
    std::cout << "Водитель " << GetFullName() << " проверяет техническое состояние автобуса" << std::endl;
}

// Перегрузка метода без вызова базового класса
void Driver::SetPersonalData(int data) {
    std::cout << "Установлены специальные данные водителя: " << data << std::endl;
    // Не вызываем базовый метод - демонстрация перегрузки без вызова
}

// Глубокое клонирование
People* Driver::Clone() const {
    std::cout << "Создание глубокой копии водителя: " << GetFullName() << std::endl;
    return new Driver(*this);
}

// Оригинальные методы класса Driver
bool Driver::CheckNeedMed(const std::string& current_date) {
    try {
        if (current_date.empty()) {
            throw std::invalid_argument("Дата проверки не может быть пустой!");
        }

        if (LastMed != current_date) {
            std::cout << "Медосмотр требуется. Последний: " << LastMed
                << ", текущая дата: " << current_date << "\n";
            return true;
        }
        std::cout << "Медосмотр не требуется.\n";
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка проверки медосмотра: " << e.what() << "\n";
        throw;
    }
}

void Driver::SetTrip(const std::string& trip) {
    try {
        if (trip.empty()) {
            throw std::invalid_argument("Название рейса не может быть пустым!");
        }

        CurrentDriverTrip = trip;
        ChangeWorkAvailability(false, "На рейсе");  // Используем новую систему
        std::cout << "Водителю " << GetFullName() << " установлен рейс: " << trip << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка установки рейса: " << e.what() << "\n";
        throw;
    }
}

void Driver::PrintDriverInfo() const {
    std::cout << "=== Информация о водителе ===\n";
    std::cout << "ФИО: " << GetFullName() << "\n";
    std::cout << "Права: " << DriverLicense << "\n";
    std::cout << "Последний медосмотр: " << LastMed << "\n";
    std::cout << "Текущий рейс: " << CurrentDriverTrip << "\n";
    std::cout << "Статус: " << (GetAvailability() ? "Доступен" : "Занят") << "\n";
    std::cout << "=============================\n";
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Driver& driver) {
    os << "Водитель: " << driver.GetFullName()
        << " (" << driver.DriverLicense << ") - "
        << (driver.GetAvailability() ? "Свободен" : "Занят в рейсе");

    if (!driver.CurrentDriverTrip.empty()) {
        os << " [" << driver.CurrentDriverTrip << "]";
    }

    return os;
}