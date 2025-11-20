#include "Bus.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

// Конструктор
Bus::Bus(const std::string& brand,
    const std::string& model,
    int placeCount,
    const std::string& code,
    const std::string& techSost,
    const std::string& lastCheck)
    : Brand(brand), Model(model), PlaceCount(placeCount),
    CodeBus(code), TechSost(techSost), LastCheckTO(lastCheck) {
}

// Конструктор копирования
Bus::Bus(const Bus& other)
    : Brand(other.Brand), Model(other.Model), PlaceCount(other.PlaceCount),
    BusAvailability(other.BusAvailability), CodeBus(other.CodeBus),
    TechSost(other.TechSost), LastCheckTO(other.LastCheckTO) {
}

void Bus::PrintBusInfo() const {
    std::cout << "=== Данные автобуса ===\n";
    std::cout << "Марка: " << this->Brand << "\n";
    std::cout << "Модель: " << this->Model << "\n";
    std::cout << "Количество мест: " << this->PlaceCount << "\n";
    std::cout << "Код автобуса: " << this->CodeBus << "\n";
    std::cout << "Техническое состояние: " << this->TechSost << "\n";
    std::cout << "Последнее ТО: " << this->LastCheckTO << "\n";
    std::cout << "Статус: " << (this->BusAvailability ? "Доступен" : "Не доступен") << "\n";
    std::cout << "=======================\n";
}

bool Bus::CheckAvailBus() const {
    return this->BusAvailability;
}

void Bus::ChangeAvailBus(bool state) {
    try {
        this->BusAvailability = state;
        if (state) {
            std::cout << "Автобус " << this->CodeBus << " теперь доступен\n";
        }
        else {
            std::cout << "Автобус " << this->CodeBus << " теперь недоступен\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка изменения статуса автобуса: " << e.what() << "\n";
        throw;
    }
}

void Bus::SetTripBus() {
    try {
        if (this->BusAvailability) {
            std::cout << "Автобус " << this->CodeBus << " назначен на рейс.\n";
        }
        else {
            throw std::runtime_error("Автобус " + this->CodeBus + " недоступен для рейса!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка назначения автобуса: " << e.what() << "\n";
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
        std::cout << "Автобус " << this->CodeBus << " отправлен на ТО: " << date << ".\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка отправки на ТО: " << e.what() << "\n";
        throw;
    }
}

void Bus::Change_sost(const std::string& newState) {
    try {
        if (newState.empty()) {
            throw std::invalid_argument("Техническое состояние не может быть пустым!");
        }

        this->TechSost = newState;
        std::cout << "Автобус " << this->CodeBus << " техническое состояние изменено на: " << newState << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка изменения состояния: " << e.what() << "\n";
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
    }
    return *this;
}

// Дружественная функция перегрузки оператора вывода
std::ostream& operator<<(std::ostream& os, const Bus& bus) {
    os << "Автобус: " << bus.Brand << " " << bus.Model
        << " [" << bus.CodeBus << "] "
        << "(" << bus.PlaceCount << " мест, "
        << (bus.BusAvailability ? "Доступен" : "Не доступен") << ")";
    return os;
}



// Дружественная функция для получения полной информации
std::string GetBusFullInfo(const Bus& bus) {
    std::stringstream ss;
    ss << "Полная информация об автобусе:\n"
        << "  Марка: " << bus.Brand << "\n"
        << "  Модель: " << bus.Model << "\n"
        << "  Мест: " << bus.PlaceCount << "\n"
        << "  Код: " << bus.CodeBus << "\n"
        << "  Состояние: " << bus.TechSost << "\n"
        << "  Последнее ТО: " << bus.LastCheckTO << "\n"
        << "  Статус: " << (bus.BusAvailability ? "Доступен" : "Не доступен");
    return ss.str();
}