// Bus.cpp
#include "Bus.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

// Конструктор (добавлен год выпуска)
Bus::Bus(const std::string& brand,
    const std::string& model,
    int placeCount,
    const std::string& code,
    const std::string& techSost,
    const std::string& lastCheck,
    int year)
    : Brand(brand), Model(model), PlaceCount(placeCount),
    CodeBus(code), TechSost(techSost), LastCheckTO(lastCheck),
    yearOfManufacture(year) {
}

// === РЕАЛИЗАЦИЯ ИНТЕРФЕЙСА ISystemObject ===

std::string Bus::getId() const {
    return CodeBus;
}

std::string Bus::getName() const {
    return Brand + " " + Model;
}

std::string Bus::getType() const {
    return "Bus";
}

void Bus::displayInfo() const {
    PrintBusInfo();
}

double Bus::getSortValue() const {
    // Сортируем по вместимости + годности + году выпуска
    double value = PlaceCount * 100.0;  // Основной вес - количество мест

    if (BusAvailability) value += 500.0;  // Доступность важна

    // Техническое состояние влияет на приоритет
    if (TechSost == "Отличное") value += 1000.0;
    else if (TechSost == "Хорошее") value += 500.0;
    else if (TechSost == "Удовлетворительное") value += 200.0;

    // Новые автобусы получают бонус
    if (yearOfManufacture > 2010) value += 300.0;

    return value;
}

bool Bus::containsText(const std::string& text) const {
    // Ищем в марке, модели, коде, состоянии (без учета регистра)
    std::string searchLower = toLower(text);

    std::string brandLower = toLower(Brand);
    std::string modelLower = toLower(Model);
    std::string codeLower = toLower(CodeBus);
    std::string techSostLower = toLower(TechSost);

    return brandLower.find(searchLower) != std::string::npos ||
        modelLower.find(searchLower) != std::string::npos ||
        codeLower.find(searchLower) != std::string::npos ||
        techSostLower.find(searchLower) != std::string::npos;
}

bool Bus::isMarkedForRemoval() const {
    // Условия для списания автобуса:

    // 1. Аварийное состояние - сразу на списание
    if (TechSost == "Аварийное") {
        return true;
    }

    // 2. Не было техобслуживания более 3 лет
    // (предполагаем формат даты "YYYY-MM-DD")
    if (!LastCheckTO.empty()) {
        // Упрощенная проверка: если дата ТО раньше 2021 года
        if (LastCheckTO.substr(0, 4) < "2021") {
            return true;
        }
    }

    // 3. Старше 25 лет И состояние хуже "Удовлетворительное"
    int currentYear = 2024;  // Текущий год
    if ((currentYear - yearOfManufacture) > 25) {
        if (TechSost == "Плохое" || TechSost == "Неудовлетворительное") {
            return true;
        }
    }

    // 4. Автобус недоступен более года (упрощенно)
    // В реальности нужно отслеживать дату последней доступности

    return false;
}

// === СУЩЕСТВУЮЩИЕ МЕТОДЫ Bus ===

void Bus::PrintBusInfo() const {
    std::cout << "=== Данные автобуса ===" << std::endl;
    std::cout << "Марка: " << this->Brand << std::endl;
    std::cout << "Модель: " << this->Model << std::endl;
    std::cout << "Год выпуска: " << this->yearOfManufacture << std::endl;
    std::cout << "Количество мест: " << this->PlaceCount << std::endl;
    std::cout << "Код автобуса: " << this->CodeBus << std::endl;
    std::cout << "Техническое состояние: " << this->TechSost << std::endl;
    std::cout << "Последнее ТО: " << this->LastCheckTO << std::endl;
    std::cout << "Статус: " << (this->BusAvailability ? "Доступен" : "Не доступен") << std::endl;
    std::cout << "=======================" << std::endl;
}

bool Bus::CheckAvailBus() const {
    return this->BusAvailability;
}

void Bus::ChangeAvailBus(bool state) {
    try {
        this->BusAvailability = state;
        if (state) {
            std::cout << "Автобус " << this->CodeBus << " теперь доступен" << std::endl;
        }
        else {
            std::cout << "Автобус " << this->CodeBus << " теперь недоступен" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка изменения статуса автобуса: " << e.what() << std::endl;
        throw;
    }
}

void Bus::SetTripBus() {
    try {
        if (this->BusAvailability) {
            std::cout << "Автобус " << this->CodeBus << " назначен на рейс." << std::endl;
        }
        else {
            throw std::runtime_error("Автобус " + this->CodeBus + " недоступен для рейса!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка назначения автобуса: " << e.what() << std::endl;
        throw;
    }
}

void Bus::GoToTO(const std::string& date) {
    try {
        if (date.empty()) {
            throw std::invalid_argument("Дата ТО не может быть пустой!");
        }

        this->LastCheckTO = date;
        this->TechSost = "На обслуживании";
        this->BusAvailability = false;
        std::cout << "Автобус " << this->CodeBus << " отправлен на ТО: " << date << "." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка отправки на ТО: " << e.what() << std::endl;
        throw;
    }
}

void Bus::Change_sost(const std::string& newState) {
    try {
        if (newState.empty()) {
            throw std::invalid_argument("Техническое состояние не может быть пустым!");
        }

        this->TechSost = newState;
        std::cout << "Автобус " << this->CodeBus << " техническое состояние изменено на: " << newState << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка изменения состояния: " << e.what() << std::endl;
        throw;
    }
}

// Перегрузка оператора сравнения
bool Bus::operator==(const Bus& other) const {
    return (this->Brand == other.Brand &&
        this->Model == other.Model &&
        this->CodeBus == other.CodeBus &&
        this->PlaceCount == other.PlaceCount);
}

// Перегрузка оператора неравенства
bool Bus::operator!=(const Bus& other) const {
    return !(*this == other);
}

// Перегрузка оператора присваивания
Bus& Bus::operator=(const Bus& other) {
    if (this != &other) {
        this->Brand = other.Brand;
        this->Model = other.Model;
        this->PlaceCount = other.PlaceCount;
        this->BusAvailability = other.BusAvailability;
        this->CodeBus = other.CodeBus;
        this->TechSost = other.TechSost;
        this->LastCheckTO = other.LastCheckTO;
        this->yearOfManufacture = other.yearOfManufacture;
    }
    return *this;
}

// Для STL сортировки
bool Bus::operator<(const Bus& other) const {
    // Сортируем по количеству мест (по убыванию)
    return PlaceCount > other.PlaceCount;
}

// Дружественная функция перегрузки оператора вывода
std::ostream& operator<<(std::ostream& os, const Bus& bus) {
    os << "Автобус: " << bus.Brand << " " << bus.Model
        << " [" << bus.CodeBus << "] "
        << "(" << bus.PlaceCount << " мест, "
        << bus.yearOfManufacture << " год, "
        << (bus.BusAvailability ? "Доступен" : "Не доступен") << ")";
    return os;
}

// Дружественная функция для получения полной информации
std::string GetBusFullInfo(const Bus& bus) {
    std::stringstream ss;
    ss << "Полная информация об автобусе:" << std::endl
        << "  Марка: " << bus.Brand << std::endl
        << "  Модель: " << bus.Model << std::endl
        << "  Год выпуска: " << bus.yearOfManufacture << std::endl
        << "  Мест: " << bus.PlaceCount << std::endl
        << "  Код: " << bus.CodeBus << std::endl
        << "  Состояние: " << bus.TechSost << std::endl
        << "  Последнее ТО: " << bus.LastCheckTO << std::endl
        << "  Статус: " << (bus.BusAvailability ? "Доступен" : "Не доступен");
    return ss.str();
}